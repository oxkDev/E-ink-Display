/*
  ******************************************************************************
  * @file    srvr.cpp
  * @author  oxkDev
  * @version V0.1
  * @date    April 2026
  * @brief   ESP8266 WiFi server.
  *          This file provides firmware functions:
  *           + Sending web page of the tool to a client's browser
  *           + Uploading images from client part by part
  *
  ******************************************************************************
*/

#ifndef __SRVR_CPP
#define __SRVR_CPP

#include "srvr.h"

/* Hostname, SSID and password of your WiFi net ------------------------------*/
const char *hostname = "E-ink-ESP32";

#if ACCESS_POINT
const char *ssid = "EPD-ESP32";
const char *password = "12345678";
#else
const char *ssid = "mesh-wifi-2";             //"your ssid";
const char *password = "qwerty8558qwerty88";  //"your password";
#endif

const char *baseURL = "espink";

/* Static IP address Settings ------------------------------------------------*/
IPAddress staticIP(192, 168, 88, 150);
IPAddress gateway(192, 168, 88, 1);
IPAddress subnet(255, 255, 255, 0);
IPAddress dns(223, 5, 5, 5);

/* Server and IP address -----------------------------------------------------*/
AsyncWebServer server(80);
AsyncWebSocket ws("/ws");
IPAddress serverIP;  // IP address in your local wifi net

EPDStatus EPD_Status;

std::vector<uint32_t> clientsList;
uint32_t curClientId = 0;
uint32_t curClientTimestamp = 0;
uint32_t cycleTimestamp = 0;
uint32_t cycleInterval = 0;
uint32_t reqIndex = 0;

/* Webserver -----------------------------------------------------------------*/
void wsSendCur(const String msg) {
  if (curClientId == 0) {
    if (ws.count() > 0)
      ws.textAll(msg);
    
    return;
  }

  if (ws.hasClient(curClientId))
    ws.client(curClientId)->text(msg);
  else
    Serial.println("[WARN] Current client disconnected before message sent.");
}

void wsSendAll(const String msg, const bool skipCurClient) {
  if (ws.count() > 0) {
    if (!skipCurClient || curClientId == 0)
      ws.textAll(msg);
    else
      for (uint32_t clientId : clientsList)
        if (clientId != curClientId)
          ws.client(clientId)->text(msg);
  } else
    Serial.println("[WARN] No clients connected to send message.");
}

void wsEvent(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type, void *arg, uint8_t *data, size_t len) {
  if (!client || client == nullptr) {
    Serial.println("[WARN] Websocket event with unknown client.");
    return;  // Prevent Null Dereference if socket closes abruptly
  }

  if (type == WS_EVT_CONNECT) {
    Serial.printf("[WS] Client (%lu) connected\n", client->id());
    clientsList.push_back(client->id());

    if (curClientId == 0 && EPD_Status == READY)
      client->text("READY");
    else if (EPD_Status == BOOT)
      client->text("BOOT");
    else
      client->text("BUSY");
    return;
  }

  if (type == WS_EVT_DISCONNECT) {
    Serial.printf("[WS] Client (%lu) disconnected\n", client->id());
    clientsList.erase(std::remove(clientsList.begin(), clientsList.end(), client->id()), clientsList.end());
    return;
  }

  if (type == WS_EVT_DATA) {
    if (len > BUFF_MAX_CHUNK_SIZE) {
      Serial.printf("[ERROR] Incoming chunk exceeds buffer size: %d > %d\n", len, BUFF_MAX_CHUNK_SIZE);
      client->text("ERROR_BUFFER_OVERFLOW");
      return;  // Abort processing
    }

    AwsFrameInfo *info = (AwsFrameInfo *)arg;

    // Ensure we are processing a complete text frame
    if (info->final && info->index == 0 && info->len == len && info->opcode == WS_TEXT) {
      String msg = String((char *)data, len);

      // Connection Requests

      if (msg.startsWith("RESUME_")) {
        uint32_t resumeId = msg.substring(6).toInt();
        if (resumeId == curClientId) {
          curClientId = client->id();
          curClientTimestamp = millis();
          client->text("RECON_" + String(curClientId));
          Serial.printf("[WS] Reconnected current client (%lu -> %lu)\n", resumeId, client->id());
          if (EPD_Status == READY)
            client->text("ACK_" + String(reqIndex));
          else
            client->text("RUNNING_" + String(curClientId));
        } else {
          client->text("ERROR_UNKNOWN_resume_REQUEST");
          Serial.printf("[WS] Unknown resume request (%lu -> %lu)\n", resumeId, client->id());
        }
        return;
      }

      if (EPD_Status != READY) {
        if (curClientId == client->id()) {
          client->text("RUNNING_" + String(curClientId));
          Serial.printf("[WS] Rejected current client (%lu).\n", client->id());
        } else {
          client->text("BUSY");
          Serial.printf("[WS] Rejected client (%lu).\n", client->id());
        }
        return;
      }

      if (curClientId != 0 && curClientId != client->id()) {
        client->text("BUSY");
        Serial.printf("[WS] Rejected client (%lu).\n", client->id());
        return;
      }

      if (curClientId == client->id())
        curClientTimestamp = millis();

      // EPD Requests

      if (msg.startsWith("INIT")) {
        curClientTimestamp = millis();
        reqIndex = 0;
        curClientId = client->id();
        client->text("RUNNING_" + String(curClientId));
        wsSendAll("BUSY");
        // Getting of e-Paper's type
        EPD_dispIndex = msg.substring(msg.startsWith("INITP_") ? 6 : 5).toInt();

        if (EPD_dispIndex < 0 || EPD_dispIndex > 50) {
          wsSendCur("ERROR_UNKNOWN_DISPLAY");
          curClientId = 0;
          return;
        }

        EPD_Status = msg.startsWith("INITP_") ? PSRAM : INIT;

        Serial.printf("[WS] Set EPD %d: %s\n", EPD_dispIndex, EPD_dispMass[EPD_dispIndex].title);
        return;
      }

      if (msg.startsWith("LOAD_")) {
        client->text("RUNNING_" + String(curClientId));
        reqIndex++;
        Serial.printf("[WS] LOAD (%lu)", reqIndex);
        const String dataStr = msg.substring(5);

        Buff_msgLength = dataStr.length();
        dataStr.getBytes(Buff_message, Buff_msgLength + 1);
        EPD_Status = LOAD;
        return;
      }

      if (msg == "NEXTIC") {
        client->text("RUNNING_" + String(curClientId));
        reqIndex++;
        Serial.println("[WS] NEXT IC");
        EPD_Status = NEXT;
        return;
      }

      if (msg == "CLEAR") {
        client->text("RUNNING_" + String(curClientId));
        reqIndex++;
        Serial.println("[WS] CLEAR");
        EPD_Status = CLEAR;
        return;
      }

      if (msg == "SHOW") {
        client->text("RUNNING_" + String(curClientId));
        reqIndex++;
        Serial.println("[WS] SHOW");
        EPD_Status = SHOW;
        return;
      }

      if (msg.startsWith("PSRAM_")) {
        if (!Buff_hasPsram) {
          client->text("ERROR_NO_PSRAM");
          return;
        }

        const String cmdStr = msg.substring(6);
        bool success = false;
        if (cmdStr == "PREV")
          success = Buff_selectImage((int8_t)Buff_imgIndex + 1);
        else if (cmdStr == "NEXT")
          success = Buff_selectImage((int8_t)Buff_imgIndex - 1);
        else if (cmdStr.toInt() == 0 && cmdStr != "0") {
          client->text("ERROR_UNKNOWN_PSRAM_COMMAND");
          return;
        } else
          success = Buff_selectImage(cmdStr.toInt());

        if (!success) {
          client->text("ERROR_INVALID_IMAGE_INDEX");
          return;
        }

        curClientId = client->id();
        curClientTimestamp = millis();
        client->text("RUNNING_" + String(curClientId));
        wsSendAll("BUSY");
        EPD_Status = SHOW;
        Serial.printf("[WS] PSRAM %d\n", Buff_imgIndex);

        return;
      }

      if (msg.startsWith("CYCLE_")) {
        if (!Buff_hasPsram) {
          client->text("ERROR_NO_PSRAM");
          return;
        }

        const String cmdStr = msg.substring(6);
        const uint32_t cmdInterval = cmdStr.toInt();

        if (cmdStr == "STOP") {
          cycleInterval = 0;
        } else if (cmdInterval == 0 && cmdStr != "0") {
          client->text("ERROR_UNKNOWN_PSRAM_COMMAND");
          return;
        } else if (cmdInterval < CYCLE_INTERVAL_MIN) {
          client->text("ERROR_INSUFFICIENT_INTERVAL_LENGTH");
          return;
        } else
          cycleInterval = cmdInterval;

        if (Buff_imgList.size() < 2 && cycleInterval >= CYCLE_INTERVAL_MIN) {
          client->text("WARN_INSUFFICIENT_IMAGES");
        }

        cycleTimestamp = millis();

        reqIndex = 0;
        EPD_Status = READY;
        client->text("ACK_" + String(reqIndex));

        return;
      }
    }

    Serial.println("[WS] Unknown request:");
    Serial.printf("     %s\n", (char *)data);
    Serial.printf("     Final:      %d\n", info->final);
    Serial.printf("     Index 0:    %d\n", info->index == 0);
    Serial.printf("     Length:     %d (%llu, %u)\n", info->len == len, info->len, len);
    Serial.printf("     opcode txt: %d\n", info->opcode == WS_TEXT);
    client->text("ERROR_UNKNOWN_REQUEST");
  }
}

void EPDHandler() {
  uint32_t t = millis();
  // Timeout Control
  if (curClientId != 0 && t - curClientTimestamp > 30000 && t > curClientTimestamp && EPD_Status != EXIT) {
    Serial.printf("[ERROR] Current Client Timeout: %lu ms\n", t - curClientTimestamp);
    EPD_Status = EXIT;
  }

  // Requests

  if (EPD_Status == PSRAM) {
    if (EPD_dispIndex == 50 && Buff_hasPsram) {
      Buff_newImage(1600 * 1200 / 2);
      Serial.printf("[BUFF] Allocate PSRAM: %s\n", Buff_usePsram ? "Success" : "Failed");
      if (Buff_usePsram) {
        Serial.println("[BUFF] PSRAM Init success, skipping initialisation.");
        EPD_Status = READY;
        wsSendCur("ACK_" + String(reqIndex));
        return;
      } else
        wsSendCur("WARN_ALLOCATE_PSRAM_FAILED");
    } else
      wsSendCur("WARN_NO_PSRAM");
    Serial.println("[BUFF] PSRAM Init failed, defaulting to basic loading.");
    EPD_Status = INIT;
  }

  if (EPD_Status == INIT) {
    // Initialization
    bool success = EPD_dispInit();
    Buff_usePsram = false;
    delay(500);
    EPD_Status = READY;
    if (success)
      wsSendCur("ACK_" + String(reqIndex));
    else {
      // Zero power consumption
      wsSendCur("ERROR_INIT_FAILED");
      EPD_Status = EXIT;
    }
    return;
  }

  if (EPD_Status == LOAD) {
    // Load data into the e-Paper
    if (EPD_dispLoad != 0) {
      EPD_dispLoad();
      EPD_Status = READY;
      wsSendCur("ACK_" + String(reqIndex));
      Serial.println(" - Done");
    } else {
      wsSendCur("ERROR_UNKNOWN_DISPLAY");
      EPD_Status = EXIT;
    }
    return;
  }

  if (EPD_Status == NEXT) {
    if (!Buff_usePsram)
      EPD_dispNext();
    EPD_Status = READY;
    wsSendCur("ACK_" + String(reqIndex));
    return;
  }

  if (EPD_Status == CLEAR) {
    // Load clear iamge into the e-Paper
    if (EPD_dispIndex == 50) {
      EPD_13in3E_Clear(EPD_13in3E_WHITE);

      EPD_Status = READY;
      wsSendCur("ACK_" + String(reqIndex));
    } else {
      // Zero power consumption
      wsSendCur("ERROR_CLEAR_UNSUPPORTED");
      EPD_Status = EXIT;
    }
    return;
  }

  if (EPD_Status == SHOW) {
    if (EPD_dispIndex == 50 && Buff_usePsram) {
      wsSendCur("INIT");
      bool success = !EPD_isOn ? EPD_dispInit() : true;
      delay(500);
      if (success) {
        wsSendCur("PSRAM_LOADING");
        Serial.println("[EPD] Loading image from PSRAM.");
        EPD_load_image_13in3E6();
        wsSendCur("SHOW");
        Serial.println("[EPD] Displaying PSRAM image.");
      } else {
        wsSendCur("ERROR_INIT_FAILED");
        EPD_Status = EXIT;
        return;
      }
    }

    if (!WiFi.setTxPower(WIFI_LOW_PWR))
      Serial.println("[WARN] Failed to set wifi transmission power to 15dBm.");
    delay(2000);
#if !ACCESS_POINT
    Serial.printf("[WiFi] Low Power RSSI: %d\n", WiFi.RSSI());
#endif
    bool success = EPD_dispMass[EPD_dispIndex].show();
    delay(1000);

    if (!WiFi.setTxPower(WIFI_NORM_PWR))
      Serial.println("[WARN] Failed to set wifi transmission power to 2dBm.");
    delay(1000);
#if !ACCESS_POINT
    Serial.printf("[WiFi] Normal Power RSSI: %d\n", WiFi.RSSI());
#endif

    if (success) {
      wsSendCur("DONE");
    } else
      wsSendCur("ERROR_DRF_FAILED");

    EPD_Status = EXIT;
  }

  if (EPD_Status == EXIT) {
    Serial.println("[WS] Exit Sequence.");
    // Zero power consumption
    EPD_Exit();
    // Buff_deleteImage();
    EPD_Status = READY;
    wsSendAll("READY");
    curClientId = 0;
    reqIndex = 0;
    cycleTimestamp = t;
    return;
  }

  t = millis();
  if (curClientId == 0 && Buff_imgList.size() > 1 && cycleInterval >= CYCLE_INTERVAL_MIN && t - cycleTimestamp >= cycleInterval) {
    Serial.printf("[WS] Cycling image %d\n", Buff_imgIndex - 1);
    Buff_selectImage((int8_t)Buff_imgIndex - 1);
    wsSendAll("CYCLE_" + String(Buff_imgIndex));
    EPD_Status = SHOW;
    cycleTimestamp = t;
  }
}

/* Server initialization ------------------------------------------------------*/
#if ACCESS_POINT == false
bool WiFiAttemptConnect() {
  WiFi.begin(ssid, password);

  // Waiting the connection to a router
  uint8_t timeCounter = 0;
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    if (timeCounter == 20) {
      Serial.println("\n[ERROR] Connection Failed, Timeout.");
      return false;
    }
    timeCounter++;
  }
  // Connection is complete
  Serial.println("\n[WiFi] Wi-Fi connected.");
  Serial.printf("[WiFi] RSSI: %d\n", WiFi.RSSI());

  return true;
}
#endif

bool Srvr_setup() {
#if ACCESS_POINT
  Serial.println("\n[AP] Initialising Access Point.");
#else
  Serial.println("\n[WiFi] Initialising Wi-Fi.");
#endif

  bool WiFiSuccess = true;

  // Applying hostname, SSID and password
  if (!WiFi.setHostname(hostname))
    Serial.println("[WARN] Failed to set hostname.");

#if ACCESS_POINT
  WiFi.mode(WIFI_AP);
  WiFiSuccess &= WiFi.softAPConfig(staticIP, gateway, subnet);
  if (!WiFiSuccess)
    Serial.println("[ERROR] AP Config Failed.");

  WiFiSuccess &= WiFi.softAP(ssid, password);
  if (!WiFiSuccess)
    Serial.println("[ERROR] AP Start Failed.");

  if (WiFiSuccess)
    Serial.println("[AP] AP Initialised.");
  else
    Serial.println("[ERROR] Initialise Access Point Failed.");
#else
  WiFi.mode(WIFI_STA);

  Serial.print("[WiFi] Connecting to ");
  Serial.println(ssid);

  WiFiSuccess &= WiFi.config(staticIP, gateway, subnet, dns, dns);
  if (!WiFiSuccess)
    Serial.println("[ERROR] WiFi Config failed.");

  WiFiAttemptConnect();

  if (WiFiSuccess)
    Serial.println("[WiFi] Wi-Fi Initialised.");
  else
    Serial.println("[ERROR] Initialise Wi-Fi Failed.");
#endif


  Serial.println("\n[SERVER] Initialising Server...");

  // Initialize mDNS
  // uint8_t mac[6];
  // WiFi.macAddress(mac);
  // char chipId[7];
  // snprintf(chipId, 7, "%02X%02X%02X", mac[3], mac[4], mac[5]);
  // String fullURL = String(baseURL) + "-" + String(chipId);

  if (!MDNS.begin(baseURL))
    Serial.println("[ERROR] Set MDNS URL Failed.");

  MDNS.addService("http", "tcp", 80);

  // Initialise LittleFS to serve files
  if (!LittleFS.begin(true)) {
    Serial.println("[ERROR] Mounting LittleFS Failed.");
  }

  // bind websocket to Server
  ws.onEvent(wsEvent);
  server.addHandler(&ws);

  // Serve the static files from the /data folder
  server.serveStatic("/", LittleFS, "/").setDefaultFile("/index.html");

  // Start the server
  server.begin();
  Serial.println("[SERVER] Server started.");

  // Show obtained IP address in local Wifi net
#if ACCESS_POINT
  Serial.print("[SERVER] AP IP Address: ");
  Serial.println(serverIP = WiFi.softAPIP());
#else
  Serial.print("[SERVER] IP Address: ");
  Serial.println(serverIP = WiFi.localIP());
#endif
  Serial.printf("[SERVER] URL: http://%s.local\n", baseURL);
  Serial.print("[SERVER] Hostname: ");
  Serial.println(WiFi.getHostname());

  return true;
}

/* The server state observation loop -------------------------------------------*/

unsigned long lastCleanup = 0;

void Srvr_loop() {
  EPDHandler();

  // Only lock the Async thread once every 1000 milliseconds
  if (millis() - lastCleanup > 1000) {
    ws.cleanupClients();
    lastCleanup = millis();
  }

#if !ACCESS_POINT
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("[WiFi] Wi-Fi Disconnected, attempting to reconnect.");
    WiFiAttemptConnect();
  }
#endif
}

#endif
