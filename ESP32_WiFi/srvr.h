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

#ifndef __SRVR_H
#define __SRVR_H

/* Includes ------------------------------------------------------------------*/
#include <WiFi.h>
#include <ESPAsyncWebServer.h>  // web server and websocket implementation
#include <ESPmDNS.h>            // custom web server URL
#include <LittleFS.h>           // file system implementation
#include <vector>

// #include "buff.h"  // POST request data accumulator
#include "epd.h"  // e-Paper driver

#define ACCESS_POINT true
#define CYCLE_INTERVAL_MIN 30000

#if ACCESS_POINT
#define WIFI_LOW_PWR WIFI_POWER_2dBm
#else
#define WIFI_LOW_PWR WIFI_POWER_2dBm
#endif

#define WIFI_NORM_PWR WIFI_POWER_15dBm


/* Hostname, SSID and password of your WiFi net ------------------------------*/
extern const char *hostname;
extern const char *ssid;
extern const char *password;
extern const char *baseURL;

/* Static IP address Settings ------------------------------------------------*/
extern IPAddress staticIP;
extern IPAddress gateway;
extern IPAddress subnet;
extern IPAddress dns;

/* Server and IP address -----------------------------------------------------*/
extern AsyncWebServer server;
extern AsyncWebSocket ws;
extern IPAddress serverIP;  // IP address in your local wifi net

/* Handler enums -------------------------------------------------------------*/
typedef enum {
  PSRAM,
  INIT,
  LOAD,
  NEXT,
  SHOW,
  STOP,
  CLEAR,
  READY,
  BOOT,
  EXIT
} EPDStatus;

extern EPDStatus EPD_Status;

extern std::vector<uint32_t> clientsList;
extern uint32_t curClientId;
extern uint32_t lastCurClientReq;
extern uint32_t reqIndex;

/* Webserver -----------------------------------------------------------------*/
void wsSendCur(const String msg);
void wsSendAll(const String msg, const bool skipCurClient = true);
void wsEvent(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type, void *arg, uint8_t *data, size_t len);
void EPDHandler();

/* Server --------------------------------------------------------------------*/
extern unsigned long lastCleanup;

#if ACCESS_POINT == false
bool WiFiAttemptConnect();
#endif

bool Srvr_setup();
void Srvr_loop();

#endif
