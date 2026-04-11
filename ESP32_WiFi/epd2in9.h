/*
  ******************************************************************************
  * @file    edp2in9.h
  * @author  Waveshare Team
  * @version V1.1
  * @date    23-Oct-2020
  * @brief   This file describes initialisation of 2.9 and 2.9b e-Papers
  *
  ******************************************************************************
*/

#ifndef __EPD2IN9_H
#define __EPD2IN9_H

#include "epd.h"

int EPD_Init_2in9();
int EPD_Init_2in9_V2();
bool EPD_2IN9_V2_Show(void);
int EPD_Init_2in9b();

int EPD_Init_2in9b_V3();
int EPD_Init_2in9b_V4();
bool EPD_2in9b_V4_Show();

/************************************************************************************/
#define UBYTE uint8_t
#define UWORD uint16_t
#define UDOUBLE uint32_t

#define EPD_2IN9D_WIDTH 128
#define EPD_2IN9D_HEIGHT 296

bool EPD_2IN9D_ReadBusy(void);
bool EPD_2IN9D_Show(void);
void EPD_2IN9D_Clear(void);
int EPD_Init_2in9d();

#endif