#include "KeDei_TFT.h"
#include <KeDei_SD.h>

#define backcolor 0xf800

File bmpFile;
KeDei_SD::BMP_Header bmpHeader;

#define backcolor 0xf800
#define SD_CS 10

void setup() {
   Serial.begin(9600);
   TFTLCD::begin();
  // TFT.clear(backcolor);   
   pinMode(10, OUTPUT);
   if (!SD.begin(10)) {
    Serial.println("failed!");
    return;
   }
   Serial.println("SD OK!");

   // there are several sample bitmap files on the SD card.
   //  - pic1.bmp a 320x480 bitmap of depth 24
   //  - pic1_1.bmp a 320x480 bitmap of depth 1
   //  - pic1_16.bmp a 320x480 bitmap of depth 4
   //  - pic1_256.bmp a 320x480 bitmap of depth 8
   //
   bmpFile = SD.open("pic1.bmp");
   if (! bmpFile) {
    Serial.println("didnt find image");
    while (1);
  }
  
  if (! KeDei_SD::bmpReadHeader(bmpFile, bmpHeader)) { 
     Serial.println("bad bmp or unsupported size.");
     return;
  }    
    
  Serial.print("image size "); 
  Serial.print(bmpHeader.bmpWidth, DEC);
  Serial.print(", ");
  Serial.print(bmpHeader.bmpHeight, DEC);
  Serial.print("  Depth = ");
  Serial.print(bmpHeader.bmpDepth);
  Serial.print("  No. colors ");
  Serial.println(bmpHeader.bmpPaletteCount);
  TFTLCD::clear(TFTLCD::RGB_TO_565(100,0,100));
  KeDei_SD::bmpdraw(bmpFile, bmpHeader, 0,0,200,200);
  delay(1000);
  bmpFile.close();
  
}

void loop() {
     
}
