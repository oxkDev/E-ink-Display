/*
 ******************************************************************************
 * @file    edp2in7.h
 * @author  Waveshare Team
 * @version V1.0.0
 * @date    23-January-2018
 * @brief   This file describes initialisation of 2.7 and 2.7b e-Papers
 *
 ******************************************************************************
*/

#ifndef __EPD2IN7_H
#define __EPD2IN7_H

#include "epd.h"

extern unsigned char lut_dc_2in7[];
extern unsigned char lut_ww_2in7[]; // R21H
extern unsigned char lut_bw_2in7[]; // R22H    r
extern unsigned char lut_bb_2in7[]; // R24H    b
extern unsigned char lut_wb_2in7[]; // R23H    w

int EPD_Init_2in7();
int EPD_2IN7_V2_Init(void);
bool EPD_2IN7_V2_Show(void);

extern unsigned char lut_dc_2in7b[];
extern unsigned char lut_ww_2in7b[]; // R21H
extern unsigned char lut_bw_2in7b[]; // R22H    r
extern unsigned char lut_bb_2in7b[]; // R23H    w
extern unsigned char lut_wb_2in7b[]; // R24H    b

int EPD_Init_2in7b();
int EPD_Init_2in7b_V2(void);
bool EPD_Show_2in7b_V2(void);

#endif