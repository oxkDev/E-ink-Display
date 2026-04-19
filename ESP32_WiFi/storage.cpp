/*
  ******************************************************************************
  * @file    storage.cpp
  * @author  oxkDev
  * @version V0.1
  * @date    April 2026
  * @brief   This file provides SD card image functions.
  ******************************************************************************
*/

#ifndef __STORAGE_CPP
#define __STORAGE_CPP

#include "storage.h"

SPIClass sdSpi(FSPI);
SPISettings sdSpiSettings(20000000, MSBFIRST, SPI_MODE0);

bool sdInserted = false;

bool SD_init() {
  if (!(sdInserted = SD.begin(SD_CS))) {
    Serial.println("Card Mount Failed");
    return false;
  }

  uint8_t cardType = SD.cardType();

  if (sdInserted = (cardType == CARD_NONE)) {
    Serial.println("[SD] No SD card attached");
    return false;
  }

  Serial.println("[SD] Card mounted successfully");
  Serial.print("[SD] Card Type:   ");
  if (cardType == CARD_MMC)
    Serial.println("MMC");
  else if (cardType == CARD_SD)
    Serial.println("SDSC");
  else if (cardType == CARD_SDHC)
    Serial.println("SDHC");
  else
    Serial.println("UNKNOWN");

  Serial.printf("[SD] Card Size:   %llu MB\n", SD.cardSize() / (1024 * 1024));
  Serial.printf("[SD] Total space: %llu MB\n", SD.totalBytes() / (1024 * 1024));
  Serial.printf("[SD] Used space:  %llu MB\n", SD.usedBytes() / (1024 * 1024));

  return true;
}

bool SD_LoadFile(const char *filename, uint8_t *epdIndex_out) {
  String path = String(filename);
  if (!path.startsWith("/")) path = "/" + path;

  Serial.printf("[SD] Loading from storage: %s\n", path);

  File file = SD.open(path, FILE_READ);
  if (!file) {
    Serial.println("[SD] Failed to open file.");
    return false;
  }

  // 1. Read and validate the Header
  EPD_FileHeader header;
  if (file.read((uint8_t *)&header, sizeof(EPD_FileHeader)) != sizeof(EPD_FileHeader)) {
    Serial.println("[SD] Invalid file size: header missing.");
    file.close();
    return false;
  }

  if (strncmp(header.magic, SD_imgHeader, 6) != 0) {
    Serial.println("[SD] Invalid Magic String! Not an EPD image file.");
    file.close();
    return false;
  }

  // 2. Allocate PSRAM for the incoming payload
  *epdIndex_out = header.epdIndex;
  Buff_newImage(header.dataSize);

  // 3. Read the payload into PSRAM / upload in chunks

  if (!Buff_usePsram) {
    Serial.println("[SD] PSRAM allocation failed, aborting.");
    return false;
  }
  
  // size_t bytesRead = 0;
  // const size_t chunkSize = 8192;
  // while (bytesRead < header.dataSize && file.available()) {
  //   size_t toRead = min(chunkSize, header.dataSize - bytesRead);
  //   file.read(*Buff_image.data + bytesRead, toRead);
  //   bytesRead += toRead;
  //   yield();
  // }

  file.read(*Buff_image.data, header.dataSize);
  
  file.close();
  Serial.printf("[SD] Loaded successfully (Type: %d, Size: %u bytes).\n", header.epdIndex, bytesRead);
  return true;
}

bool SD_SaveFile(const char* filename, uint8_t epdIndex, byte* psramData, uint32_t size) {
  if (psramData == nullptr || size == 0) return false;

  // Format the file path
  String path = String(filename);
  if (!path.startsWith("/")) path = "/" + path;
  if (!path.endsWith(".dat")) path += ".dat";

  Serial.printf("[SD] Saving %s...\n", path.c_str());

  File file = SD.open(path.c_str(), FILE_WRITE);
  if (!file) {
    Serial.println("[SD] Failed to open file for writing.");
    return false;
  }

  // 1. Construct and write the File Header
  EPD_FileHeader header;
  memcpy(header.magic, SD_imgHeader, 6);
  header.version = 0x01;
  header.epdIndex = epdIndex;
  header.dataSize = size;

  file.write((const uint8_t*)&header, sizeof(EPD_FileHeader));

  // 2. Write the binary payload in chunks to prevent Watchdog timeout
  size_t bytesWritten = 0;
  const size_t chunkSize = 8192; // 8KB chunks

  while (bytesWritten < size) {
    size_t toWrite = min(chunkSize, size - bytesWritten);
    file.write(psramData + bytesWritten, toWrite);
    bytesWritten += toWrite;
    yield(); // Feed the FreeRTOS watchdog
  }

  file.close();
  Serial.printf("[SD] File saved successfully (%u bytes payload).\n", size);
  return true;
}

void listDir(fs::FS &fs, const char *dirname, uint8_t levels) {
  Serial.printf("Listing directory: %s\n", dirname);

  File root = fs.open(dirname);
  if (!root) {
    Serial.println("Failed to open directory");
    return;
  }
  if (!root.isDirectory()) {
    Serial.println("Not a directory");
    return;
  }

  File file = root.openNextFile();
  while (file) {
    if (file.isDirectory()) {
      Serial.print("  DIR : ");
      Serial.println(file.name());
      if (levels) {
        listDir(fs, file.name(), levels - 1);
      }
    } else {
      Serial.print("  FILE: ");
      Serial.print(file.name());
      Serial.print("  SIZE: ");
      Serial.println(file.size());
    }
    file = root.openNextFile();
  }
}

void createDir(fs::FS &fs, const char *path) {
  Serial.printf("Creating Dir: %s\n", path);
  if (fs.mkdir(path)) {
    Serial.println("Dir created");
  } else {
    Serial.println("mkdir failed");
  }
}

void removeDir(fs::FS &fs, const char *path) {
  Serial.printf("Removing Dir: %s\n", path);
  if (fs.rmdir(path)) {
    Serial.println("Dir removed");
  } else {
    Serial.println("rmdir failed");
  }
}

bool readFile(fs::FS &fs, const char *path) {
  Serial.printf("Reading file: %s\n", path);

  File file = fs.open(path);
  if (!file) {
    Serial.println("Failed to open file for reading");
    return false;
  }

  Serial.print("Read from file: ");
  while (file.available()) {
    Serial.write(file.read());
  }
  file.close();

  return true;
}

void writeFile(fs::FS &fs, const char *path, const char *message) {
  Serial.printf("Writing file: %s\n", path);

  File file = fs.open(path, FILE_WRITE);
  if (!file) {
    Serial.println("Failed to open file for writing");
    return;
  }
  if (file.print(message)) {
    Serial.println("File written");
  } else {
    Serial.println("Write failed");
  }
  file.close();
}

void appendFile(fs::FS &fs, const char *path, const char *message) {
  Serial.printf("Appending to file: %s\n", path);

  File file = fs.open(path, FILE_APPEND);
  if (!file) {
    Serial.println("Failed to open file for appending");
    return;
  }
  if (file.print(message)) {
    Serial.println("Message appended");
  } else {
    Serial.println("Append failed");
  }
  file.close();
}

void renameFile(fs::FS &fs, const char *path1, const char *path2) {
  Serial.printf("Renaming file %s to %s\n", path1, path2);
  if (fs.rename(path1, path2)) {
    Serial.println("File renamed");
  } else {
    Serial.println("Rename failed");
  }
}

void deleteFile(fs::FS &fs, const char *path) {
  Serial.printf("Deleting file: %s\n", path);
  if (fs.remove(path)) {
    Serial.println("File deleted");
  } else {
    Serial.println("Delete failed");
  }
}

void testFileIO(fs::FS &fs, const char *path) {
  File file = fs.open(path);
  static uint8_t buf[512];
  size_t len = 0;
  uint32_t start = millis();
  uint32_t end = start;
  if (file) {
    len = file.size();
    size_t flen = len;
    start = millis();
    while (len) {
      size_t toRead = len;
      if (toRead > 512) {
        toRead = 512;
      }
      file.read(buf, toRead);
      len -= toRead;
    }
    end = millis() - start;
    Serial.printf("%u bytes read for %lu ms\n", flen, end);
    file.close();
  } else {
    Serial.println("Failed to open file for reading");
  }


  file = fs.open(path, FILE_WRITE);
  if (!file) {
    Serial.println("Failed to open file for writing");
    return;
  }

  size_t i;
  start = millis();
  for (i = 0; i < 2048; i++) {
    file.write(buf, 512);
  }
  end = millis() - start;
  Serial.printf("%u bytes written for %lu ms\n", 2048 * 512, end);
  file.close();
}

#endif