#include "EPD_13in3e.h"
#include "GUI_Paint.h"
#include "fonts.h"
#include "ImageData.h"

UBYTE *Image;
// #if 1
UWORD Imagesize = ((EPD_13IN3E_WIDTH % 2 == 0) ? (EPD_13IN3E_WIDTH / 2) : (EPD_13IN3E_WIDTH / 2 + 1)) * EPD_13IN3E_HEIGHT;
// #else
// UWORD Imagesize = EPD_13IN3E_WIDTH * EPD_13IN3E_HEIGHT;
// #endif

void setup() {
  Debug("EPD_13IN3E_test Demo\r\n");
  DEV_Module_Init();

  Debug("e-Paper Init\r\n");
  EPD_13IN3E_Init();
  // EPD_13IN3E_Clear(EPD_13IN3E_WHITE);
  DEV_Delay_ms(500);

  Debug("NewImage:Image\r\n");
  Paint_NewImage(Image, 200, 200, 0, WHITE);

  if ((Image = (UBYTE *)malloc(20000)) == NULL) {
    Debug("Failed to apply for black memory...\r\n");
    DEV_Module_Exit();
    while (1)
      ;
  }

  //Select Image
  Paint_SelectImage(Image);
  Paint_Clear(WHITE);

  //Create a new image cache named IMAGE_BW and fill it with white
  // UBYTE *Image;
  // UWORD Imagesize = ((EPD_13IN3E_WIDTH % 2 == 0) ? (EPD_13IN3E_WIDTH / 2) : (EPD_13IN3E_WIDTH / 2 + 1)) * EPD_13IN3E_HEIGHT;
  // if ((Image = (UBYTE *)malloc(20000)) == NULL) {
  //   Debug("Failed to apply for black memory...\r\n");
  //   DEV_Module_Exit();
  //   while (1)
  //     ;
  // }
  // Debug("NewImage:Image\r\n");
  // Paint_NewImage(Image, 200, 200, 0, WHITE);

  // //Select Image
  // Paint_SelectImage(Image);
  // Paint_Clear(WHITE);

  // #if 1  // show bmp
  //   printf("show bmp2-----------------\r\n");
  //   // EPD_13IN3E_DisplayPart(BMP_1, 100, 100, 400, 600);
  //   // DEV_Delay_ms(3000);
  //   // EPD_13IN3E_DisplayPart(BMP_1, 100, 900, 400, 600);
  //   // DEV_Delay_ms(3000);
  //   // EPD_13IN3E_DisplayPart(BMP_1, 700, 100, 400, 600);
  //   // DEV_Delay_ms(3000);
  //   // EPD_13IN3E_DisplayPart(BMP_1, 700, 900, 400, 600);
  //   // DEV_Delay_ms(3000);
  //   EPD_13IN3E_DisplayPart(BMP_2, 0, 0, 1200, 1600);
  //   DEV_Delay_ms(3000);
  // #else  // Drawing on the image
  //   Paint_NewImage(Image, 200, 200, 90, EPD_13IN3E_WHITE);
  //   Paint_SetScale(6);
  //   // 1.Select Image
  //   Debug("SelectImage:Image\r\n");
  //   Paint_SelectImage(Image);
  //   Paint_Clear(EPD_13IN3E_WHITE);

  //   // 2.Drawing on the image
  //   Debug("Drawing:Image\r\n");
  //   Paint_DrawPoint(10, 80, EPD_13IN3E_RED, DOT_PIXEL_1X1, DOT_STYLE_DFT);
  //   Paint_DrawPoint(10, 90, EPD_13IN3E_BLUE, DOT_PIXEL_2X2, DOT_STYLE_DFT);
  //   Paint_DrawPoint(10, 100, EPD_13IN3E_GREEN, DOT_PIXEL_3X3, DOT_STYLE_DFT);
  //   Paint_DrawLine(20, 70, 70, 120, EPD_13IN3E_YELLOW, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
  //   Paint_DrawLine(70, 70, 20, 120, EPD_13IN3E_YELLOW, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
  //   Paint_DrawRectangle(20, 70, 70, 120, EPD_13IN3E_BLACK, DOT_PIXEL_1X1, DRAW_FILL_EMPTY);
  //   Paint_DrawRectangle(80, 70, 130, 120, EPD_13IN3E_BLACK, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  //   Paint_DrawCircle(45, 95, 20, EPD_13IN3E_BLACK, DOT_PIXEL_1X1, DRAW_FILL_EMPTY);
  //   Paint_DrawCircle(105, 95, 20, EPD_13IN3E_WHITE, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  //   Paint_DrawLine(85, 95, 125, 95, EPD_13IN3E_YELLOW, DOT_PIXEL_1X1, LINE_STYLE_DOTTED);
  //   Paint_DrawLine(105, 75, 105, 115, EPD_13IN3E_YELLOW, DOT_PIXEL_1X1, LINE_STYLE_DOTTED);
  //   Paint_DrawString_CN(10, 130, "你好abc", &Font12CN, EPD_13IN3E_BLACK, EPD_13IN3E_WHITE);
  //   Paint_DrawString_CN(10, 150, "微雪电子", &Font24CN, EPD_13IN3E_WHITE, EPD_13IN3E_BLACK);
  //   Paint_DrawNum(10, 33, 123456789, &Font12, EPD_13IN3E_BLACK, EPD_13IN3E_WHITE);
  //   Paint_DrawNum(10, 50, 987654321, &Font16, EPD_13IN3E_WHITE, EPD_13IN3E_BLACK);
  //   Paint_DrawString_EN(145, 0, "Waveshare", &Font16, EPD_13IN3E_BLACK, EPD_13IN3E_WHITE);
  //   Paint_DrawString_EN(145, 35, "Waveshare", &Font16, EPD_13IN3E_GREEN, EPD_13IN3E_WHITE);
  //   Paint_DrawString_EN(145, 70, "Waveshare", &Font16, EPD_13IN3E_BLUE, EPD_13IN3E_WHITE);
  //   Paint_DrawString_EN(145, 105, "Waveshare", &Font16, EPD_13IN3E_RED, EPD_13IN3E_WHITE);
  //   Paint_DrawString_EN(145, 140, "Waveshare", &Font16, EPD_13IN3E_YELLOW, EPD_13IN3E_WHITE);

  //   Debug("EPD_Display\r\n");
  //   EPD_13IN3E_DisplayPart(Image, 1000, 0, 200, 200);
  //   DEV_Delay_ms(3000);
  // #endif

  //   Debug("Clear...\r\n");
  //   EPD_13IN3E_Clear(EPD_13IN3E_WHITE);
  //   DEV_Delay_ms(2000);

  Debug("Goto Sleep...\r\n");
  EPD_13IN3E_Sleep();
  // free(Image);
  DEV_Delay_ms(2000);

  // close 5V
  Debug("close 5V, Module enters 0 power consumption ...\r\n");
  DEV_Module_Exit();
}

bool isInit = false;

const uint16_t numChars = 1024;
const char endMarker = '\n';

char receivedChars[numChars];
bool newData = false;

void loop() {
  recvWithEndMarker();

  if (newData) {
    Debug("EPD_13IN3E_test Input\r\n");
    // Init
    // if (!isInit) {
    printf("Initialising...\r\n");
    DEV_Module_Init();

    Debug("e-Paper Init\r\n");
    EPD_13IN3E_Init();

    //   isInit = true;
    // } else
    //   printf("Already initialised: skipping.\r\n");

    Paint_Clear(WHITE);

    if (strcmp(receivedChars, "img") == 0) {
      printf("Displaying BMP_3\r\n");
      EPD_13IN3E_DisplayPart(BMP_3, 0, 0, 1200, 1600);
    } else if (strcmp(receivedChars, "colours") == 0) {
      printf("Displaying colours\r\n");

      Paint_NewImage(Image, 400, 900, 0, EPD_13IN3E_WHITE);
      Paint_SetScale(6);

      Paint_SelectImage(Image);
      Paint_Clear(EPD_13IN3E_WHITE);

      Paint_DrawRectangle(0, 0, 400, 150, EPD_13IN3E_BLACK, DOT_PIXEL_1X1, DRAW_FILL_FULL);
      Paint_DrawRectangle(0, 150, 400, 300, EPD_13IN3E_WHITE, DOT_PIXEL_1X1, DRAW_FILL_FULL);
      Paint_DrawRectangle(0, 300, 400, 450, EPD_13IN3E_YELLOW, DOT_PIXEL_1X1, DRAW_FILL_FULL);
      Paint_DrawRectangle(0, 450, 400, 600, EPD_13IN3E_RED, DOT_PIXEL_1X1, DRAW_FILL_FULL);
      Paint_DrawRectangle(0, 600, 400, 750, EPD_13IN3E_BLUE, DOT_PIXEL_1X1, DRAW_FILL_FULL);
      Paint_DrawRectangle(0, 750, 400, 900, EPD_13IN3E_GREEN, DOT_PIXEL_1X1, DRAW_FILL_FULL);

      EPD_13IN3E_DisplayPart(Image, 400, 350, 400, 900);
    } else if (strcmp(receivedChars, "SG") == 0) {
      printf("Displaying SG pledge\r\n");

      char pledge[] = "We, the citizens of Singapore, pledge ourselves as one    united people, regardless of race, language, or religion, to build a democratic society based on justice and        equality, so as to achieve happiness, prosperity, and     progress for our nation.";
      Paint_NewImage(Image, 360, 1000, 270, EPD_13IN3E_WHITE);
      Paint_SetScale(6);
      // 1.Select Image
      Paint_SelectImage(Image);
      Paint_Clear(EPD_13IN3E_WHITE);

      Paint_DrawRectangle(0, 0, 1000, 180, EPD_13IN3E_RED, DOT_PIXEL_1X1, DRAW_FILL_FULL);
      Paint_DrawRectangle(2, 1, 1000, 358, EPD_13IN3E_BLACK, DOT_PIXEL_1X1, DRAW_FILL_EMPTY);
      Paint_DrawCircle(90, 90, 50, EPD_13IN3E_WHITE, DOT_PIXEL_1X1, DRAW_FILL_FULL);
      Paint_DrawCircle(130, 90, 60, EPD_13IN3E_RED, DOT_PIXEL_1X1, DRAW_FILL_FULL);
      Paint_DrawBitMap_Paste(BMP_star, 100 + 37, 40 + 2, 26, 26, 0, EPD_13IN3E_WHITE);
      Paint_DrawBitMap_Paste(BMP_star, 100 + 4, 40 + 26, 26, 26, 0, EPD_13IN3E_WHITE);
      Paint_DrawBitMap_Paste(BMP_star, 100 + 70, 40 + 26, 26, 26, 0, EPD_13IN3E_WHITE);
      Paint_DrawBitMap_Paste(BMP_star, 100 + 17, 40 + 65, 26, 26, 0, EPD_13IN3E_WHITE);
      Paint_DrawBitMap_Paste(BMP_star, 100 + 57, 40 + 65, 26, 26, 0, EPD_13IN3E_WHITE);
      Paint_DrawString_EN(10, 190, pledge, &Font24, EPD_13IN3E_WHITE, EPD_13IN3E_BLACK);

      EPD_13IN3E_DisplayPart(Image, 420, 300, 360, 1000);
    } else if (strcmp(receivedChars, "clear")) {
      printf("Displaying Text: ");
      printf(receivedChars);
      printf("\r\n");

      Paint_NewImage(Image, 360, 1000, 270, EPD_13IN3E_WHITE);
      Paint_SetScale(6);
      // 1.Select Image
      Paint_SelectImage(Image);
      Paint_Clear(EPD_13IN3E_WHITE);

      Paint_DrawRectangle(2, 1, 1000, 358, EPD_13IN3E_BLACK, DOT_PIXEL_1X1, DRAW_FILL_EMPTY);
      Paint_DrawString_EN(10, 10, receivedChars, &Font24, EPD_13IN3E_WHITE, EPD_13IN3E_BLACK);

      EPD_13IN3E_DisplayPart(Image, 420, 300, 360, 1000);
    } else {
      printf("Clearing...\r\n");
      EPD_13IN3E_Clear(EPD_13IN3E_WHITE);
    }

    DEV_Delay_ms(3000);
    // End
    Debug("Goto Sleep...\r\n");
    EPD_13IN3E_Sleep();
    DEV_Delay_ms(2000);

    // close 5V
    Debug("close 5V, Module enters 0 power consumption ...\r\n");
    DEV_Module_Exit();


    printf("Ready.\r\n");
    newData = false;
  }
}

void recvWithEndMarker() {
  static uint16_t ndx = 0;
  char rc;

  while (Serial.available() > 0 && newData == false) {
    rc = Serial.read();

    if (rc != endMarker) {
      if (rc == '\\')
        rc = '\n';
      receivedChars[ndx] = rc;
      ndx++;
      if (ndx >= numChars) {
        ndx = numChars - 1;
      }
    } else {
      receivedChars[ndx] = '\0';  // terminate the string
      ndx = 0;
      newData = true;
    }
  }
}

/*
Hey Jude, don't make it bad. Take a sad song and make it better.\
Remember to let her into your heart, Then you can start to make it better.\
Hey Jude, don't be afraid. You were made to go out and get her.\
The minute you let her under your skin, Then you begin to make it better.\
And anytime you feel the pain, hey Jude, refrain, Don't carry the world upon your shoulders.\
For well you know that it's a fool who plays it cool By making his world a little colder.\
Hey Jude, don't let me down. You have found her, now go and get her.\
Remember to let her into your heart, Then you can start to make it better.
*/