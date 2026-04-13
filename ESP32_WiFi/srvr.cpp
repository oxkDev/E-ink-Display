/*
  ******************************************************************************
  * @file    srvr.h
  * @author  Waveshare Team
  * @version V1.0.0
  * @date    23-January-2018
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
uint32_t lastCurClientReq = 0;
uint32_t reqIndex = 0;

/* Webserver -----------------------------------------------------------------*/
void wsSendCur(const String msg) {
  if (curClientId != 0 && ws.hasClient(curClientId))
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
    Serial.printf("[WS] Client (%d) connected\n", client->id());
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
    Serial.printf("[WS] Client (%d) disconnected\n", client->id());
    clientsList.erase(std::remove(clientsList.begin(), clientsList.end(), client->id()), clientsList.end());

    // if (curClientId == client->id())
    //   curClientId = 0;

    return;
  }

  if (type == WS_EVT_DATA) {
    AwsFrameInfo *info = (AwsFrameInfo *)arg;

    // Ensure we are processing a complete text frame
    if (info->final && info->index == 0 && info->len == len && info->opcode == WS_TEXT) {
      if (len > BUFF_MAX_CHUNK_SIZE) {
        Serial.println("[ERROR] Incoming chunk exceeds buffer size!");
        client->text("ERROR_BUFFER_OVERFLOW");
        return;  // Abort processing
      }

      String msg = String((char *)data, len);

      if (msg.startsWith("RECON_")) {
        uint32_t reconnectId = msg.substring(6).toInt();
        if (reconnectId == curClientId) {
          curClientId = client->id();
          lastCurClientReq = millis();
          client->text("RECON_" + String(curClientId));
          Serial.printf("[WS] Reconnected client (%d -> %d)\n", reconnectId, client->id());
          if (EPD_Status == READY)
            client->text("ACK_" + String(reqIndex));
          else
            client->text("RUNNING_" + String(curClientId));
        } else {
          client->text("ERROR_UNKOWN_CLIENT_ID");
          Serial.printf("[WS] Unknown Reconnect Request (%d -> %d)\n", reconnectId, client->id());
        }
        return;
      }

      if (EPD_Status != READY) {
        if (curClientId == client->id()) {
          client->text("RUNNING_" + String(curClientId));
          Serial.printf("[WS] Rejected current client (%d).\n", client->id());
        } else {
          client->text("BUSY");
          Serial.printf("[WS] Rejected client (%d).\n", client->id());
        }
        return;
      }

      if (curClientId != 0 && curClientId != client->id()) {
        client->text("BUSY");
        Serial.printf("[WS] Rejected client (%d).\n", client->id());
        return;
      }

      if (curClientId == client->id())
        lastCurClientReq = millis();

      if (msg.startsWith("INIT_")) {
        lastCurClientReq = millis();
        reqIndex = 0;
        curClientId = client->id();
        client->text("RUNNING_" + String(curClientId));
        wsSendAll("BUSY");
        // Getting of e-Paper's type
        EPD_dispIndex = msg.substring(5).toInt();
        EPD_Status = INIT;

        Serial.printf("[WS] Init EPD %d: %s\n", EPD_dispIndex, EPD_dispMass[EPD_dispIndex].title);
        return;
      }

      if (msg.startsWith("LOAD_")) {
        client->text("RUNNING_" + String(curClientId));
        reqIndex++;
        Serial.printf("[WS] LOAD (%d)", reqIndex);
        String dataStr = msg.substring(5);
        // // Boundary check
        // if (dataStr.length() > BUFF_MAX_CHUNK_SIZE) {
        //   Serial.println("[ERROR] Incoming chunk exceeds buffer size!");
        //   client->text("ERROR_BUFFER_OVERFLOW");
        //   return;  // Abort processing
        // }

        Buff_msgIndex = dataStr.length();
        dataStr.toCharArray(Buff_message, Buff_msgIndex + 1);
        EPD_Status = LOAD;
        return;
      }

      if (msg == "NEXT") {
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
    }

    Serial.printf("[WS] Unknown request (%d%d%d): %s", info->final, info->index == 0, info->len == len, info->opcode == WS_TEXT, (char *)data);
    client->text("ERROR_UNKNOWN_REQUEST");
  }
}

void EPDHandler() {
  const uint32_t t = millis();
  if (curClientId != 0 && t - lastCurClientReq > 30000 && t > lastCurClientReq) {
    Serial.printf("[ERROR] Current Client Timeout: %u - %u\n", t, lastCurClientReq);
    curClientId = 0;
    reqIndex = 0;
    EPD_Status = EXIT;
    EPD_Exit();
    EPD_Status = READY;
    wsSendAll("READY");
  }

  if (EPD_Status == INIT) {
    // Initialization
    bool success = EPD_dispInit();
    delay(500);
    EPD_Status = READY;
    if (success)
      wsSendCur("ACK_" + String(reqIndex));
    else {
      // Zero power consumption
      wsSendCur("ERROR_INIT_FAILED");
      EPD_Exit();
      curClientId = 0;
      EPD_Status = READY;
    }
    return;
  }

  if (EPD_Status == LOAD) {
    // Load data into the e-Paper
    if (EPD_dispLoad != 0) {
      EPD_dispLoad();
      EPD_Status = READY;
      Serial.println(" - Done");
      wsSendCur("ACK_" + String(reqIndex));
    } else {
      wsSendCur("ERROR_UNKNOWN_DISPLAY");
      EPD_Exit();
      curClientId = 0;
      EPD_Status = READY;
    }
    return;
  }

  if (EPD_Status == NEXT) {
    int nextCode = EPD_dispMass[EPD_dispIndex].next;

    // Instruction code for for writting data into e-paper's memory
    if (EPD_dispIndex == 34) {
      if (flag == 0)
        nextCode = 0x26;
      else
        nextCode = 0x13;
    } else if (EPD_dispIndex == 50) {
      EPD_CS_ALL(1);
      digitalWrite(PIN_SPI_CS_S, 0);
      EPD_SendCommand_13in3E6(0x10);
    }

    if (nextCode != -1) {  // Skip normal send command with -1.
      EPD_SendCommand(nextCode);
      delay(2);
    }

    EPD_dispLoad = EPD_dispMass[EPD_dispIndex].loadRed;
    EPD_Status = READY;
    wsSendCur("ACK_" + String(reqIndex));
    return;
  }

  if (EPD_Status == CLEAR) {
    // Load clear iamge into the e-Paper
    if (EPD_dispIndex == 50) {
      EPD_13in3E_Clear(EPD_13in3E_WHITE);
    } else {
      // Zero power consumption
      wsSendCur("ERROR_CLEAR_UNSUPPORTED");
      EPD_Exit();
      curClientId = 0;
      EPD_Status = READY;
    }

    EPD_Status = READY;
    wsSendCur("ACK_" + String(reqIndex));
    return;
  }

  if (EPD_Status == SHOW) {
    if (!WiFi.setTxPower(WIFI_LOW_PWR))
      Serial.println("[WARN] Failed to set wifi transmission power to 8.5dBm.");

    delay(2000);
#if !ACCESS_POINT
    Serial.printf("[WiFi] Low Power RSSI: %d\n", WiFi.RSSI());
#endif
    bool success = EPD_dispMass[EPD_dispIndex].show();
    delay(1000);

    // Zero power consumption
    EPD_Exit();
    delay(1000);
    if (!WiFi.setTxPower(WIFI_NORM_PWR))
      Serial.println("[WARN] Failed to set wifi transmission power to 19dBm.");

    delay(1000);
#if !ACCESS_POINT
    Serial.printf("[WiFi] Normal Power RSSI: %d\n", WiFi.RSSI());
#endif

    if (success) {
      wsSendCur("DONE");
      wsSendAll("READY");
    } else
      wsSendCur("ERROR_DRF_FAILED");

    EPD_Status = READY;
    curClientId = 0;
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

  // server.on()

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
