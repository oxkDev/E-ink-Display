/*
  ******************************************************************************
  * @file    storage.h
  * @author  oxkDev
  * @version V0.1
  * @date    April 2026
  * @brief   This file provides SD card image functions.
  ******************************************************************************
*/

#ifndef __STORAGE_H
#define __STORAGE_H

#include <Arduino.h>
#include <SD.h>
#include <SPI.h>
#include "buff.h"

#define SD_CS 10
#define SD_SCK 11
#define SD_MOSI 12
#define SD_MISO 13

extern SPIClass sdSpi;
extern SPISettings sdSpiSettings;

extern bool sdInserted;

extern const String SD_imgHeader = "EPDIMG";

struct __attribute__((packed)) EPD_FileHeader {
  char magic[6];      // Magic Identifier: "EPDIMG"
  uint8_t version;    // File version: 0x01
  uint8_t epdIndex;   // The target display type (e.g., 50 for 13.3")
  uint32_t dataSize;  // The exact size of the PSRAM binary payload
};

void SD_init(void);
void listDir(fs::FS &fs, const char *dirname, uint8_t levels);
void createDir(fs::FS &fs, const char *path);
void removeDir(fs::FS &fs, const char *path);
void readFile(fs::FS &fs, const char *path);
void writeFile(fs::FS &fs, const char *path, const char *message);
void appendFile(fs::FS &fs, const char *path, const char *message);
void renameFile(fs::FS &fs, const char *path1, const char *path2);
void deleteFile(fs::FS &fs, const char *path);
void testFileIO(fs::FS &fs, const char *path);

#endif