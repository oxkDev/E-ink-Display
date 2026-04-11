/*
 ******************************************************************************
 * @file    edp4in2.h
 * @author  Waveshare Team
 * @version V1.0.0
 * @date    23-January-2018
 * @brief   This file describes initialisation of 4.2 and 4.2b e-Papers
 *
 ******************************************************************************
 */

#ifndef __EPD4IN2_H
#define __EPD4IN2_H

#include "epd.h"

extern unsigned char lut_dc_4in2[];
extern unsigned char lut_ww_4in2[]; // R21H
extern unsigned char lut_bw_4in2[]; // R22H    r
extern unsigned char lut_bb_4in2[]; // R24H    b
extern unsigned char lut_wb_4in2[]; // R23H    w

extern char flag;

int EPD_Init_4in2(void);
int EPD_Init_4in2_V2(void);
bool EPD_4IN2_V2_Show(void);

extern unsigned char lut_dc_4in2b[];
extern unsigned char lut_ww_4in2b[]; // R21H
extern unsigned char lut_bw_4in2b[]; // R22H    r
extern unsigned char lut_bb_4in2b[]; // R24H    b
extern unsigned char lut_wb_4in2b[]; // R23H    w

int EPD_Init_4in2b(void);
int EPD_Init_4in2b_V2(void);
void EPD_4IN2B_V2_load(void);
bool EPD_4IN2B_V2_Show(void);

#endif