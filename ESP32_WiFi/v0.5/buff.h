/*
  ******************************************************************************
  * @file    buff.h
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

#ifndef __BUFF_H
#define __BUFF_H

#include <Arduino.h>
#include <vector>

/* Size, current position index and byte array of the buffer -----------------*/
#define BUFF_MAX_CHUNK_SIZE 1024 + 100

extern byte Buff_message[];
extern uint32_t Buff_msgLength;
extern bool Buff_hasPsram;
extern bool Buff_usePsram;

struct Buff_imgStruct {
  byte* data;
  uint32_t size;
};

extern Buff_imgStruct Buff_image;
extern std::vector<Buff_imgStruct> Buff_imgList;
extern uint32_t Buff_imgDataIndex;
extern uint8_t Buff_imgIndex;

/* Initialise PSRAM for buff image -------------------------------------------*/
void Buff_init(void);

bool Buff_newImage(uint32_t size);
bool Buff_writeImage(byte data);
bool Buff_selectImage(int8_t imgIndex = 0);
bool Buff_deleteImage(int8_t imgIndex);

/* Reads a word from the buffer at specified position ------------------------*/
byte Buff_getByte(uint32_t index);

/* Reads a byte from the buffer at specified position ------------------------*/
int Buff_getWord(uint32_t index);

/* Checks if the buffer's data ends with specified string --------------------*/
int Buff_checkCommand(uint32_t startIndex, byte* str);

#endif