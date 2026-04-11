/*
 ******************************************************************************
 * @file    edp7in5.h
 * @author  Waveshare Team
 * @version V1.0.0
 * @date    23-January-2018
 * @brief   This file describes initialisation of 7.5 and 7.5b e-Papers
 *
 ******************************************************************************
 */

#ifndef __EPD7IN5_H
#define __EPD7IN5_H

#include "epd.h"

#define UBYTE uint8_t

extern UBYTE Voltage_Frame_7IN5_V2[];
extern UBYTE LUT_VCOM_7IN5_V2[];
extern UBYTE LUT_WW_7IN5_V2[];
extern UBYTE LUT_BW_7IN5_V2[];
extern UBYTE LUT_WB_7IN5_V2[];
extern UBYTE LUT_BB_7IN5_V2[];

int EPD_7in5__init();

/* EPD_7in5_V2 ***************************************************************/
bool EPD_7in5_V2_Readbusy(void);
bool EPD_7IN5_V2_Show(void);
void EPD_7IN5_V2_LUT(UBYTE *lut_vcom, UBYTE *lut_ww, UBYTE *lut_bw,
                     UBYTE *lut_wb, UBYTE *lut_bb);
int EPD_7in5_V2_init(void);

/* EPD_7in5B_V2 **************************************************************/
int EPD_7in5B_V2_Init(void);

#endif