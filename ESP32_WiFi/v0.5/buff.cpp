/*
  ******************************************************************************
  * @file    buff.cpp
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

#ifndef __BUFF_CPP
#define __BUFF_CPP

#include "buff.h"

/* Size, current position index and byte array of the buffer -----------------*/
byte Buff_message[BUFF_MAX_CHUNK_SIZE];
uint32_t Buff_msgLength;
bool Buff_hasPsram = false;
bool Buff_usePsram = false;
Buff_imgStruct Buff_image;
uint32_t Buff_imgDataIndex = 0;
std::vector<Buff_imgStruct> Buff_imgList;
uint8_t Buff_imgIndex = 0;


/* Initialise memory for buff image ------------------------------------------*/
void Buff_init(void) {
  if (Buff_hasPsram = psramInit()) {
    Serial.println("[BUFF] PSRAM initialised.");
    Serial.printf("[BUFF] Heap:  %d / %d bytes free\n", ESP.getFreeHeap(), ESP.getHeapSize());
    Serial.printf("[BUFF] Psram: %d / %d bytes free\n", ESP.getFreePsram(), ESP.getPsramSize());
  } else
    Serial.println("[BUFF] PSRAM not available.");
}

/* Allocate PSRAM for buff image ---------------------------------------------*/
bool Buff_newImage(uint32_t size) {
  if (!Buff_hasPsram)
    return false;

  if (size > ESP.getFreePsram()) {
    Serial.printf("[BUFF] PSRAM insufficient space: %d / %d required\n", size, ESP.getFreePsram());
    // return Buff_usePsram = false;

    Serial.println("[BUFF] Deleting last image.");
    Buff_deleteImage(Buff_imgList.size() - 1);
  }

  Buff_image.data = (byte*)ps_malloc(size);

  if (Buff_image.data == NULL) {
    Serial.println("[BUFF] PSRAM allocation error.");
    return Buff_usePsram = false;
  }
  Buff_imgDataIndex = 0;
  Buff_imgIndex = 0;
  Buff_image.size = size;
  Buff_imgList.insert(Buff_imgList.begin(), Buff_image);
  Serial.printf("[BUFF] PSRAM Free space: %d bytes left\n", ESP.getFreePsram());

  return Buff_usePsram = true;
}

/* Write byte to PSRAM -------------------------------------------------------*/
bool Buff_writeImage(byte data) {
  if (!Buff_hasPsram || !Buff_usePsram || Buff_imgList.size() == 0)
    return false;

  if (Buff_imgDataIndex >= Buff_image.size)
    return false;

  Buff_image.data[Buff_imgDataIndex++] = data;

  return true;
}

bool Buff_selectImage(int8_t imgIndex) {
  if (!Buff_hasPsram || Buff_imgList.size() == 0)
    return Buff_usePsram = false;

  if (imgIndex < 0) {
    Serial.println("[BUFF] Image index overflow to max");
    imgIndex = Buff_imgList.size() - 1;
  } else if (imgIndex >= (int8_t)Buff_imgList.size()) {
    Serial.println("[BUFF] Image index overflow to 0");
    imgIndex = 0;
  }

  Buff_imgIndex = imgIndex;
  Buff_image = Buff_imgList[imgIndex];

  Serial.printf("[BUFF] Loaded Image %d\n", Buff_imgIndex);

  return Buff_usePsram = true;
}

/* Free PSRAM memory ---------------------------------------------------------*/
bool Buff_deleteImage(int8_t imgIndex) {
  Buff_imgDataIndex = 0;

  if (imgIndex >= Buff_imgList.size() || imgIndex < 0)
    return false;

  Buff_imgStruct img = Buff_imgList[imgIndex];
  free(img.data);
  Buff_imgList.erase(Buff_imgList.begin() + imgIndex);

  return true;
}

/* Reads a word from the buffer at specified position ------------------------*/
byte Buff_getByte(uint32_t index) {
  // The first and second characters of the byte stored in the buffer
  // are supposed to be in range, otherwise it isn't a image data's byte
  if (((Buff_message[index] - 1) & 0x88) != 0 || Buff_message[index] == 0) {
    Serial.println("[ERROR] Invalid buff byte.");
    return -1;
  }

  // The character 'a' means 0, the character 'p' means 15 consequently,
  // The 1st character describes 4 low bits if the byte and the 2nd one - 4 high bits
  return Buff_message[index] - 1;
}

/* Reads a byte from the buffer at specified position ------------------------*/
int Buff_getWord(uint32_t index) {
  // Read low byte of the word
  byte a = Buff_getByte(index);

  // If it is not a image data byte, then exit
  if (a == -1)
    return -1;

  // Read high byte of the word
  byte b = Buff_getByte(index + 2);

  // If it is not a image data byte, then exit
  if (b == -1)
    return -1;

  // Return the word's value
  return a + (b << 8);
}

/* Checks if the buffer's data ends with specified string --------------------*/
int Buff_checkCommand(uint32_t startIndex, char* str) {
  // characters of the string to the end of the string
  while (*str != 0) {
    // If the correspondent character in the buffer isn't equal
    // to the string's character, return false
    if (Buff_message[startIndex++] != *str)
      return false;
    str++;
  }

  // Otherwise return true
  return true;
}

#endif