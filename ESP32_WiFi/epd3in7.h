/*****************************************************************************
* | File      	:   EPD_3IN7.c
* | Author      :   Waveshare team
* | Function    :   3.7inch e-paper
* | Info        :
*----------------
* |	This version:   V1.0
* | Date        :   2020-08-10
* | Info        :
* -----------------------------------------------------------------------------
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documnetation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to  whom the Software is
# furished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS OR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
# THE SOFTWARE.
#
******************************************************************************/

#ifndef __EPD3IN7_H
#define __EPD3IN7_H

#include "epd.h"

#define UBYTE uint8_t

extern const UBYTE lut_1Gray_GC[];

extern bool EPD_3IN7_ReadBusy_HIGH(void);

/* set the look-up tables ---------------------------------------------------*/
extern void EPD_3IN7_Load_LUT(void);

/*  Initialize the e-Paper register -----------------------------------------*/
int EPD_3IN7_1Gray_Init();

/*  Sends the image buffer in RAM to e-Paper and displays -------------------*/
extern bool EPD_3IN7_1Gray_Show(void);

#endif