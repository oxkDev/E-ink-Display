/*
  ******************************************************************************
  * @file    edp2in13.h
  * @author  Waveshare Team
  * @version V1.0.0
  * @date    23-January-2018
  * @brief   This file describes initialisation of e-Papers:
  *              2.13,
  *              2.13b and 2.13c,
  *              2.13d.
  ******************************************************************************
*/

#ifndef __EPD2IN13_H
#define __EPD2IN13_H

#include "../epd.h"

extern unsigned char lut_full_2in13[];
extern const unsigned char lut_full_2in3v2[];
extern const unsigned char WS_20_30_2IN13_V3[];

extern const unsigned char lut_vcomDC_2in13d[];
extern const unsigned char lut_ww_2in13d[];
extern const unsigned char lut_bw_2in13d[];
extern const unsigned char lut_wb_2in13d[];
extern const unsigned char lut_bb_2in13d[];

int EPD_Init_2in13();
int EPD_Init_2in13_V3();

/* Show image and turn to deep sleep mode ------*/
bool EPD_2IN13_V3_Show();
int EPD_Init_2in13_V4();

/* Show image and turn to deep sleep mode ------*/
bool EPD_2IN13_V4_Show();
int EPD_Init_2in13b();
int EPD_2IN13B_V3_Init();
bool EPD_2IN13B_V3_Show();
int EPD_2IN13B_V4_Init();
bool EPD_2IN13B_V4_Show();

int EPD_Init_2in13d();

#endif