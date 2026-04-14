/*
 ******************************************************************************
 * @file    buff.h
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

#ifndef __BUFF_CPP
#define __BUFF_CPP

#include "buff.h"

/* Size, current position index and byte array of the buffer -----------------*/
int Buff_msgIndex;
char Buff_message[BUFF_MAX_CHUNK_SIZE];
byte* Buff_image = nullptr;
bool Buff_hasPsram = false;
bool Buff_usePsram = false;
int Buff_psramIndex = 0;
uint32_t Buff_psramSize;

/* Initialise memory for buff image ------------------------------------------*/
void Buff_init(void) {
  if (Buff_hasPsram = psramInit()) {
    Serial.println("[BUFF] PSRAM initialised.");
    Serial.printf("[BUFF] Heap:  %d / %d bytes free\n", ESP.getFreeHeap(), ESP.getHeapSize());
    Serial.printf("[BUFF] Psram: %d / %d bytes free\n", ESP.getFreePsram(), Buff_psramSize = ESP.getPsramSize());
  } else
    Serial.println("[BUFF] PSRAM not available.");
}

/* Allocate PSRAM for buff image ---------------------------------------------*/
bool Buff_allocPsram(uint32_t size) {
  if (!Buff_hasPsram || size > Buff_psramSize) {
    Serial.printf("[BUFF] PSRAM Allocation too big: %d / %d required\n", size, Buff_psramSize);
    return Buff_usePsram = false;
  }

  Buff_psramIndex = 0;
  Buff_image = (byte*)ps_malloc(size);

  return Buff_usePsram = Buff_image != NULL;
}

/* Write byte to PSRAM -------------------------------------------------------*/
bool Buff_writePsram(byte data) {
  if (!Buff_hasPsram || !Buff_usePsram)
    return false;

  if (Buff_psramIndex >= Buff_psramSize)
    return false;

  Buff_image[Buff_psramIndex++] = data;

  return true;
}

/* Free PSRAM memory ---------------------------------------------------------*/
void Buff_freePsram() {
  Buff_psramIndex = 0;
  free(Buff_image);
}

/* Reads a word from the buffer at specified position ------------------------*/
byte Buff_getByte(int index) {
  // The first and second characters of the byte stored in the buffer
  // are supposed to be in range ['a'; 'p'], otherwise it isn't a image data's byte
  if ((Buff_message[index] < 'a') || (Buff_message[index] > 'p'))
    return -1;
  if ((Buff_message[index + 1] < 'a') || (Buff_message[index + 1] > 'p'))
    return -1;

  // The character 'a' means 0, the character 'p' means 15 consequently,
  // The 1st character describes 4 low bits if the byte and the 2nd one - 4 high bits
  return (byte)((int)Buff_message[index] - 'a') + (((int)Buff_message[index + 1] - 'a') << 4);
}

/* Reads a byte from the buffer at specified position ------------------------*/
int Buff_getWord(int index) {
  // Read low byte of the word
  int a = Buff_getByte(index);

  // If it is not a image data byte, then exit
  if (a == -1)
    return -1;

  // Read high byte of the word
  int b = Buff_getByte(index + 2);

  // If it is not a image data byte, then exit
  if (b == -1)
    return -1;

  // Return the word's value
  return a + (b << 8);
}

/* Checks if the buffer's data ends with specified string --------------------*/
int Buff_checkCommand(int startIndex, char* str) {
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