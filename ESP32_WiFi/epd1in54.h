/*
 ******************************************************************************
 * @file    edp1in54.h
 * @author  Waveshare Team
 * @version V1.0.0
 * @date    23-January-2018
 * @brief   This file describes initialisation of 1.54 and 1.54b e-Papers
 *
 ******************************************************************************
 */

#ifndef __EPD1IN54_H
#define __EPD1IN54_H

#include "epd.h"

int EPD_Init_1in54(void);
bool EPD_1IN54_Show(void);
int EPD_Init_1in54b(void);
int EPD_1IN54B_V2_Init(void);
bool EPD_1IN54B_V2_Show(void);
int EPD_Init_1in54c(void);

#endif