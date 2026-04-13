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

#ifndef __BUFF_H
#define __BUFF_H

#include <arduino.h>

/* Size, current position index and byte array of the buffer -----------------*/
#define BUFF_MAX_CHUNK_SIZE 1024

extern int Buff_msgIndex;
extern char Buff_message[];
extern char* Buff_image;
extern bool Buff_hasPsram;
extern bool Buff_usePsram;
extern int Buff_psramSize;

/* Initialise PSRAM for buff image -------------------------------------------*/
void Buff_init(void);

bool Buff_allocPsram(int size);
void Buff_freePsram();

/* Reads a word from the buffer at specified position ------------------------*/
int Buff_getByte(int index);

/* Reads a byte from the buffer at specified position ------------------------*/
int Buff_getWord(int index);

/* Checks if the buffer's data ends with specified string --------------------*/
int Buff_checkCommand(int startIndex, char* str);

#endif