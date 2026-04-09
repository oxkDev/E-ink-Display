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
#define BUFF_MAX_CHUNK_SIZE 1024
int     Buff_msgIndex;
char    Buff_message[BUFF_MAX_CHUNK_SIZE + 100];

/* Reads a word from the buffer at specified position ------------------------*/
int Buff_getByte(int index)
{
    // The first and second characters of the byte stored in the buffer
    // are supposed to be in range ['a'; 'p'], otherwise it isn't a image data's byte
    if ((Buff_message[index    ] < 'a') || (Buff_message[index    ] > 'p')) return -1;
    if ((Buff_message[index + 1] < 'a') || (Buff_message[index + 1] > 'p')) return -1;

    // The character 'a' means 0, the character 'p' means 15 consequently,
    // The 1st character describes 4 low bits if the byte and the 2nd one - 4 high bits 
    return ((int)Buff_message[index] - 'a') + (((int)Buff_message[index + 1] - 'a') << 4);
}

/* Reads a byte from the buffer at specified position ------------------------*/
int Buff_getWord(int index)
{
    // Read low byte of the word
    int a = Buff_getByte(index); 

    // If it is not a image data byte, then exit
    if (a == -1) return -1;

    // Read high byte of the word
    int b = Buff_getByte(index + 2);

    // If it is not a image data byte, then exit
    if (b == -1) return -1;

    // Return the word's value
    return a + (b << 8);
}

/* Checks if the buffer's data ends with specified string --------------------*/
int Buff_checkCommand(int startIndex, char*str)
{
    // characters of the string to the end of the string
    while (*str != 0)
    {
        // If the correspondent character in the buffer isn't equal
        // to the string's character, return false    
        if (Buff_message[startIndex++] != *str) return false;
        str++;
    }

    // Otherwise return true
    return true;
}
