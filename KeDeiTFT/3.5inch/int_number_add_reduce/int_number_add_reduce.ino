#include <KeDei_TFT.h>
#include <KeDei_TP.h>
#include "KeDei_font.h"
#include "KeDei_button.h"

#include <stdlib.h>

static const TFTLCD::TftColor backcolor = TFTLCD::RGB_TO_565(255,100,100);

//Font class object is font
Font  font;
Font  font2;

//Two Button class object is  Button1,Button2
Button  Button1,Button2;
int value =1688;

void lcd_display_int (int iVal, Font &aFont)
{
  char buffer[12];

  aFont.lcd_string(itoa (iVal, buffer, 10));
}

void setup() {
  //TFT initialization
   TFTLCD::begin();
   //LCD Clear the screen, backcolor
   TFTLCD::clear(backcolor);
   
   font.begin();
   //Set the text area for the upper left corner (30, 10), the lower right corner (320,200), the color red, if the color is NULL or R0 G0 B0(black), is also not set text color 
   font.set_txt(5,5,320,200,backcolor);
   
   //Set the text font color
   font.set_fontcolor(TFTLCD::RGB_TO_565(0,0,255));
   //Displays the title and instructions
   font.lcd_string("KeDeiTFT");
   font.lcd_string("show int number add and reduce");
   
   //Draw the first round button1
   Button1.drawButton(100,100,1,"-",font2);
   //Draw the second round button
   Button2.drawButton(100,250,0,"+",font2);

   font.set_txt(100,180,140,197,backcolor);
   font.set_fontcolor(TFTLCD::RGB_TO_565(0,0,255));
   font.mod_fonttable(Font::FontTable::Flags_DoubleHigh);
   lcd_display_int(value,font);
}

void loop() {
    //check Touch current state detection
    TP::pen_down();
    
    //Is there a pending touch with valid y and x coordinates?
    if(TP::flag && TP::y_val && TP::x_val) {
      //Check whether the x,y coordinates are in the area of
      // one of our buttons and the  button has not yet been pressed.
      // the istouch() function will set the penDownFlag if the
      // coordinates are in the button area indicating a button press.

      // check Button1. must do the penDownFlag check before the istouch()
      // is called since istouch() will modify penDownFlag. this logic will
      // ensure only a single button press event per cycle of pendown and penup.
      if(Button1.isTouchState())
      {
           //value add by 9
           value -= 9;
           //Displays new value
           lcd_display_int(value,font);
      }

      if(Button2.isTouchState())
      {
           //value increase by 9
           value += 9;
           lcd_display_int(value,font);
      }

    } else {
      // none of our buttons are pressed so lets ensure that
      // all buttons are showing the not pressed style.
      // penup() also clears the penDownFlag so that the next
      // successful istouch() will set it again.
      Button1.penup();
      Button2.penup();        
    }
}
