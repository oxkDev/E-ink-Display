/**
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

/* Size, current position index and byte array of the buffer -----------------*/
#define BUFF_MAX_CHUNK_SIZE 2000
int     Buff_msgIndex;
char    Buff_message[BUFF_MAX_CHUNK_SIZE + 50];

/* Reads a word from the buffer at specified position ------------------------*/
int Buff_getByte(int index)
{
    return Buff_message[index];
}

/* Reads a byte from the buffer at specified position ------------------------*/
int Buff_getWord(int index)
{
    if (index + 1 >= BUFF_MAX_CHUNK_SIZE) return -1;
    return Buff_message[index] + (Buff_message[index + 1] << 8);
}

/* Reads a byte from the buffer at specified position ------------------------*/
int Buff_getN3(int index)
{
    return (index + 3 > BUFF_MAX_CHUNK_SIZE) ? 0 :
        (Buff_message[index    ]      ) + 
        (Buff_message[index + 1] <<  8) + 
        (Buff_message[index + 2] << 16);
}

/* Checks if the buffer's data ends with specified string --------------------*/
int Buff_signature(int index, char*str)
{
    // characters of the string to the end of the string
    while (*str != 0)
    {
        // If the correspondent character in the buffer isn't equal
        // to the string's character, return false    
        if (Buff_message[index++] != *str) return false;
        str++;
    }
    
    // Otherwise return true
    return true;
}
