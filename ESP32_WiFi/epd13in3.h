/*
  ******************************************************************************
  * @file    edp13in3.h
  * @author  Waveshare Team
  * @version V1.0.0
  * @date    2023-09-26
  * @brief   This file describes initialisation of 13.3k e-Papers
  *
  ******************************************************************************
*/

#ifndef __EPD13IN3_H
#define __EPD13IN3_H

#include "epd.h"

#define UBYTE uint8_t

#define EPD_13in3E_BLACK 0x0
#define EPD_13in3E_WHITE 0x1
#define EPD_13in3E_YELLOW 0x2
#define EPD_13in3E_RED 0x3
#define EPD_13in3E_BLUE 0x5
#define EPD_13in3E_GREEN 0x6

int EPD_13in3k_init(void);
bool EPD_13in3k_Show(void);

/**********************************************************************/

int EPD_13in3b_init(void);
bool EPD_13in3b_Show(void);

/*************************13.3E6**********************************/

void EPD_CS_ALL(UBYTE Value);
int EPD_13in3E_init(void);
bool EPD_13in3E_Show(void);
void EPD_13in3E_Clear(uint8_t colourCode);

#endif