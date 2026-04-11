/*
  ******************************************************************************
  * @file    edp5in65.h
  * @author  Waveshare Team
  * @version V1.0.0
  * @date    27-July-2020
  * @brief   This file describes initialisation of 5.65f e-Papers
  *
  ******************************************************************************
*/

#ifndef __EPD5IN65F_H
#define __EPD5IN65F_H

#include "epd.h"

bool EPD_5IN65F_BusyHigh(void); // If BUSYN=0 then waiting
bool EPD_5IN65F_BusyLow(void); // If BUSYN=1 then waiting
bool EPD_5IN65F_Show(void);
int EPD_5IN65F_init();

#endif