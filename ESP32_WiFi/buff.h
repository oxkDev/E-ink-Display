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

/* Size, current position index and byte array of the buffer -----------------*/
#define BUFF_MAX_CHUNK_SIZE 1024

extern int Buff_msgIndex;
extern char Buff_message[];

/* Reads a word from the buffer at specified position ------------------------*/
int Buff_getByte(int index);

/* Reads a byte from the buffer at specified position ------------------------*/
int Buff_getWord(int index);

/* Checks if the buffer's data ends with specified string --------------------*/
int Buff_checkCommand(int startIndex, char *str);

#endif