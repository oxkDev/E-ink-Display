/*
 ******************************************************************************
 * @file    edp7in5_HD.h
 * @author  Waveshare Team
 * @version V1.0.0
 * @date    23-January-2018
 * @brief   This file describes initialisation of 7.5 HD and 7.5b HD e-Papers
 *
 ******************************************************************************
 */

#ifndef __EPD7IN5_HD_H
#define __EPD7IN5_HD_H

#include "../epd.h"

bool EPD_7IN5_HD_Readbusy(void);
bool EPD_7IN5_HD_Show(void);
int EPD_7IN5_HD_init(void);
bool EPD_7IN5B_HD_Show(void);
int EPD_7IN5B_HD_init(void);

#endif