/**
  ******************************************************************************
  * @file    ESP32_WiFi.ino
  * @author  oxkDev
  * @version V0.1
  * @date    April 2026
  * @brief   The main file.
  *          This file provides firmware functions:
  *           + Initialization of Serial Port, SPI pins and server
  *           + Main loop
  *
  ******************************************************************************
*/

#include "srvr.h"  // Server functions

bool serverInit = false;

/* Entry point ----------------------------------------------------------------*/
void setup() {
  // Serial port initialization
  Serial.begin(115200);
  delay(10);

  EPD_Status = BOOT;

  // Server initialization
  Serial.print("\n[INIT] Server Init.\n");
  Srvr_setup();
  Serial.print("\n[INIT] Server Init Complete.\n");

  // SPI initialization
  // EPD_Status = CLEAR;
  // wsSendAll("START");
  Serial.print("\n[INIT] SPI and PSRAM Init.\n");
  EPD_initSPI();
  Buff_init();
  
  delay(1000);
  Serial.print("\n[INIT] EPD Clear Image Test.\n");
  bool success = EPD_dispInit();
  delay(1000);
  if (success) {
    EPD_13in3E_Clear(EPD_13in3E_WHITE);

    if (!WiFi.setTxPower(WIFI_LOW_PWR))
      Serial.println("[WARN] Failed to set wifi transmission power to low power mode.");
    delay(2000);
    success &= EPD_13in3E_Show();
  }

  // Initialization is complete
  Serial.printf("\n[INIT] Test Complete: %s\n", (success ? "Success." : "Failed."));
  delay(1000);

  EPD_Exit();
  delay(1000);
  if (!WiFi.setTxPower(WIFI_NORM_PWR))
    Serial.println("[WARN] Failed to set wifi transmission power to 19.5dBm.");

  EPD_Status = READY;
  if (success)
    wsSendAll("READY");
  else
    wsSendAll("ERROR_TEST_FAILED");
}

const byte numChars = 200;
const char endMarker = '\n';

char receivedChars[numChars];
bool newData = false;

/* The main loop -------------------------------------------------------------*/
void loop() {
  // The server state observation
  Srvr_loop();

  recvWithEndMarker();

  if (newData) {
    Serial.print("[input] ");
    if (strcmp(receivedChars, "clear") == 0) {
      EPD_Status = CLEAR;
      Serial.println("Clearing...");
      // EPD_initSPI();
      EPD_dispInit();
      delay(1000);
      EPD_13in3E_Clear(EPD_13in3E_WHITE);
      if (!WiFi.setTxPower(WIFI_LOW_PWR))
        Serial.println("[WARN] Failed to set wifi transmission power to low power mode.");
      delay(2000);
      EPD_13in3E_Show();
      delay(2000);
      EPD_Exit();
      delay(1000);
      if (!WiFi.setTxPower(WIFI_NORM_PWR))
        Serial.println("[WARN] Failed to set wifi transmission power to 19.5dBm.");
      EPD_Status = READY;
    } else {
      Serial.println("Unknown Command.");
    }
    newData = false;
  }
}

void recvWithEndMarker() {
  static uint16_t ndx = 0;
  char rc;

  while (Serial.available() > 0 && newData == false) {
    rc = Serial.read();

    if (rc != endMarker) {
      if (rc == '\\')
        rc = '\n';
      receivedChars[ndx] = rc;
      ndx++;
      if (ndx >= numChars) {
        ndx = numChars - 1;
      }
    } else {
      receivedChars[ndx] = '\0';  // terminate the string
      ndx = 0;
      newData = true;
    }
  }
}