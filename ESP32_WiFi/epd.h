/*
  ******************************************************************************
  * @file    epd.h
  * @author  Waveshare Team
  * @version V1.0.0
  * @date    23-January-2018
  * @brief   This file provides e-Paper driver functions
  ******************************************************************************
*/

#ifndef __EPD_H
#define __EPD_H

#include <arduino.h>
#include <vector>
#include <SPI.h>

#include "buff.h"

/* e-Paper initialization functions ------------------------------------------*/
#include "epd1in54.h"
#include "epd2in13.h"
#include "epd2in9.h"
#include "epd2in7.h"
#include "epd2in66.h"
#include "epd3in7.h"
#include "epd3in52.h"
#include "epd4in01f.h"
#include "epd4in2.h"
#include "epd4in26.h"
#include "epd5in65f.h"
#include "epd5in83.h"
#include "epd7in3.h"
#include "epd7in5.h"
#include "epd7in5_HD.h"
#include "epd13in3.h"

/* Pin level definition ------------------------------------------------------*/
#define LOW 0
#define HIGH 1

#define GPIO_PIN_SET 1
#define GPIO_PIN_RESET 0

/* SPI pin definition --------------------------------------------------------*/

#define ESP32S3 true

#if ESP32S3
// ESP32 S3
#define PIN_SPI_DIN 11
#define PIN_SPI_SCK 12
#define PIN_SPI_CS_M 16
#define PIN_SPI_CS_S 15
#define PIN_SPI_DC 7
#define PIN_SPI_RST 6
#define PIN_SPI_BUSY 5
#define PIN_SPI_PWR 4
#else
// ESP32 C6
#define PIN_SPI_DIN 7
#define PIN_SPI_SCK 6
#define PIN_SPI_CS_M 18
#define PIN_SPI_CS_S 19
#define PIN_SPI_DC 20
#define PIN_SPI_RST 21
#define PIN_SPI_BUSY 22
#define PIN_SPI_PWR 23
#endif

#define PIN_SPI_CS PIN_SPI_CS_M

extern SPIClass fspi;
extern SPISettings spi_settings;

void EPD_initSPI();
void GPIO_Mode(unsigned char GPIO_Pin, unsigned char Mode);

/* Waiting the e-Paper is ready for further instructions ---------------------*/
bool EPD_WaitUntilIdle(uint8_t timeout = 100, uint8_t min = 0);
bool EPD_WaitUntilIdle_high(uint8_t timeout = 100, uint8_t min = 0);

/* Wake EPD from deep sleep mode ---------------------------------------------*/
bool EPD_Reset(void);

/* Exit and Power down EPD ---------------------------------------------------*/
void EPD_Exit(void);

/* The procedure of sending a byte to e-Paper by SPI -------------------------*/
void EPD_SendByte(byte data);
void EPD_SendByteList(std::vector<byte> dataList);
unsigned char DEV_SPI_ReadByte(void);

/* Sending command -----------------------------------------------------------*/
void EPD_SendCommand(byte command);
void EPD_SendCommand_13in3E6(byte command);

/* Sending data --------------------------------------------------------------*/
void EPD_SendData(byte data);
void EPD_SendData_13in3E6(byte data);
void EPD_SendDataList_13in3E6(std::vector<byte> dataList);

/* Send command with arguments -----------------------------------------------*/
void EPD_Send_1(byte c, byte v1);
void EPD_Send_2(byte c, byte v1, byte v2);
void EPD_Send_3(byte c, byte v1, byte v2, byte v3);
void EPD_Send_4(byte c, byte v1, byte v2, byte v3, byte v4);
void EPD_Send_5(byte c, byte v1, byte v2, byte v3, byte v4, byte v5);

/* EPD Model Specific Functions ----------------------------------------------*/
extern bool EPD_invert;             // If true, then image data bits must be inverted
extern int EPD_dispIndex;           // The index of the e-Paper's type
extern int EPD_dispX, EPD_dispY;    // Current pixel's coordinates (for 2.13 only)
extern void (*EPD_dispLoad)(void);  // Pointer on a image data writting function

/* The set of pointers on 'init', 'load' and 'show' functions, title and code */
struct EPD_dispInfo {
  int (*init)(void);      // Initialization
  void (*loadBlk)(void);  // Black channel loading
  int next;               // Change channel code
  void (*loadRed)(void);  // Red channel loading
  bool (*show)(void);     // Show and sleep
  char* title;            // Title of an e-Paper
};

/* Array of sets describing the usage of e-Papers ----------------------------*/
extern EPD_dispInfo EPD_dispMass[];

/* Initialization of an e-Paper ----------------------------------------------*/
bool EPD_dispInit(void);

/* Image Data Loading --------------------------------------------------------*/
void EPD_loadA(void);         // a-type e-Paper
void EPD_loadAFilp(void);     // a-type e-Paper Inverted
void EPD_loadB(void);         // b-type e-Paper
void EPD_loadC(void);         // 2.13 e-Paper
void EPD_loadD(void);         // 7.5 e-Paper
void EPD_loadE(void);         // 7.5b e-Paper
void EPD_loadF(void);         // 5.83b e-Paper
void EPD_loadG(void);         // 5.65f e-Paper
void EPD_load_13in3E6(void);  // 13.3 e-paper

void EPD_load_psram_13in3E6(void);

/* Image Data showing --------------------------------------------------------*/
bool EPD_showA(void);  // Show Sequence (a-type, 4.2 and 2.7 e-Paper)
bool EPD_showB(void);  // Show Sequence (b-type, e-Paper)
bool EPD_showC(void);  // Show Sequence (7.5 and 7.5b e-Paper)
bool EPD_showD(void);

/* Look-up Table Definition --------------------------------------------------*/
extern byte lut_full_mono[];
extern byte lut_partial_mono[];
extern byte lut_vcom0[];
extern byte lut_w[];
extern byte lut_b[];
extern byte lut_g1[];
extern byte lut_g2[];
extern byte lut_vcom1[];
extern byte lut_red0[];
extern byte lut_red1[];

/* Writting lut-data into the e-Paper ----------------------------------------*/
void EPD_lut(byte c, byte l, byte* p);
void EPD_SetLutBw(byte* c20, byte* c21, byte* c22, byte* c23, byte* c24);
void EPD_SetLutRed(byte* c25, byte* c26, byte* c27);

#endif