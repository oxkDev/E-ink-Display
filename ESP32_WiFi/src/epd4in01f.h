/*
  ******************************************************************************
  * @file    edp4in01f.h
  * @author  Waveshare Team
  * @version V1.0.0
  * @date    29-Dec-2020
  * @brief   This file describes initialisation of 4.01f e-Papers
  *
  ******************************************************************************
*/

/*****************************************************************************
                      EPD_4IN01F
******************************************************************************/

#ifndef __EPD4IN01F_H
#define __EPD4IN01F_H

#include "../epd.h"

// If BUSYN=0 then waiting
bool EPD_4IN01F_BusyHigh(void);

// If BUSYN=1 then waiting
bool EPD_4IN01F_BusyLow(void);
bool EPD_4IN01F_Show(void);
int EPD_4IN01F_init(void);

#endif