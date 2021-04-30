#include <KeDei_TFT.h>
#include <KeDei_TP.h>
#include "KeDei_font.h"
#include "KeDei_button.h"

// Debug prints enabled with following define
#define SERIAL_DEBUG


#define backcolor 0xf800

//Font class object is font
Font  font;
Font  font2;
Button  clearButton;      // button to trigger clear the screen.


class TouchPen{
public:
  long   x;
  long   y;
  bool  flag;
  bool  x_val;
  bool  y_val;
  
  long  rxpiVal;
  long  rypiVal;
  void  pen_down(void);
  
  long  tp_max_x;
  long  tp_min_x;
  long  tp_max_y;
  long  tp_min_y;
  long  tp_x;
  long  tp_y;
  long  temp_x;
  long  temp_y;
  void  get_xy(void);

};

/*****************************************
 *The function name £º get_xy
 *Function  £º »ñÈ¡´¥ÃþµÄ×ø±ê
 *Input  £º none
 *Output   £º none
 *Author   £º KeDei
 *Time   £º2015/4/21
 ****************************************/
void TouchPen::get_xy(void)
{
  tp_x  = 0;
  tp_y  = 0;
  y_val = 1;
  x_val = 1;

#ifdef  __AVR_ATmega328P__
  DDRC|=2;
  PORTC|=2;
  DDRD|=0X20;
  PORTB&=0XDF;
  DDRD&=0XBF;
  DDRC&=0XFB;

#else
#endif

  delay(100);
  
  tp_max_x = analogRead(YP);
  tp_min_x = tp_max_x;
  for(char tp_i = 0; tp_i < 12; tp_i++)
  {
    temp_x = analogRead(YP);
    if(temp_x > tp_max_x) tp_max_x = temp_x;
    if(temp_x < tp_min_x) tp_min_x = temp_x;
    tp_x += temp_x;
    
  }
  if((tp_max_x - tp_min_x) >= 50L) 
    x_val = 0;

  tp_x = (tp_x-tp_max_x - tp_min_x) / 10L;
  if(TFTLCD::MODULE == _MODULE_1_)
  {
  #ifdef  ROTATE_0
    x = (tp_x - 104L) * 24L / 73L;
  #endif
  }
  else
  {
    x = (tp_x - 109L) * 32L / 74L;
  }

  

#ifdef  __AVR_ATmega328P__  
  DDRC|=4;
  PORTC|=4;
  DDRD|=0X40;
  PORTD&=0XBF;
  DDRD&=0XDF;
  DDRC&=0XFD;

#else
#endif
  
  tp_max_y = analogRead(XP);
  tp_min_y = tp_max_y;
  for(char tp_i = 0;tp_i < 12;tp_i++)
  {
    temp_y = analogRead(XP);
    if(temp_y > tp_max_y) tp_max_y = temp_y;
    if(temp_y < tp_min_y) tp_min_y = temp_y;
    tp_y += temp_y; 
  }
  if((tp_max_y - tp_min_y) >= 50L) 
    y_val = 0L;
  

  tp_y = (tp_y - tp_max_y - tp_min_y) / 10L;
  if(TFTLCD::MODULE == _MODULE_1_)
  {
  #ifdef  ROTATE_0
    y = (tp_y - 70L) * 32L / 75L;
  #endif
  }
  else
  {
    y = (tp_y - 73L) * 48L / 78L;
  }

#if defined(SERIAL_DEBUG)
    Serial.print("debug ");
    Serial.print(tp_x);
    Serial.print("  ");
    Serial.print(x);
    Serial.print(" - ");
    Serial.print(tp_y);
    Serial.print("  ");
    Serial.print(y);
    Serial.print(" == ");
    Serial.print(x_val);
    Serial.print("  ");
    Serial.print(y_val);
    Serial.print(" == ");
    Serial.print(tp_max_x);
    Serial.print("  ");
    Serial.print(tp_max_y);
    Serial.print("  ");
    Serial.print(flag);
    Serial.print("  \n");
#endif
}


/*****************************************
 *The function name £º pen_down
 *Function  £º ¼ì²âµ±Ç°´¥ÃþµÄ×´Ì¬
 *Input  £º none
 *Output   £º none
 *Author   £º KeDei
 *Time   £º2015/4/21
 ****************************************/
void TouchPen::pen_down()
{
  pinMode(XP,INPUT_PULLUP);
  pinMode(XM,INPUT_PULLUP);
//  DDRB&=0XFE;

  pinMode(YP,INPUT_PULLUP);
//  DDRC&=0XFD;
  pinMode(YM,OUTPUT);
//  DDRB|=2;

  delay(100);

  digitalWrite(YM,LOW);
  digitalWrite(YP,LOW);
//  PORTB&=0XFD;
//  delay(1);

  delay(100);

   flag = 0;

  rxpiVal = analogRead(XP);  
  rypiVal = analogRead(YP);  
  if(500 > rxpiVal)
  {
    flag = 1;
    get_xy();
  }
//  else flag = 0;
//  DDRB|=3;
//  DDRC|=6;
#if 0
  // original code.
  pinMode(XP,OUTPUT);
  pinMode(XM,OUTPUT);
  pinMode(YP,OUTPUT);
#else
    // new code to perform cleanup after touch screen operations
  pinMode(XM, OUTPUT);
  digitalWrite(XM, LOW);
  pinMode(YP, OUTPUT);
  digitalWrite(YP, HIGH);
  pinMode(YM, OUTPUT);
  digitalWrite(YM, LOW);
  pinMode(XP, OUTPUT);
  digitalWrite(XP, HIGH);
#endif
}

void refreshScreen ()
{
   //LCD Clear the screen, backcolor
   TFTLCD::clear(backcolor);
      
   //Displays a string
   font.lcd_string("KeDeiTFT ");
   font.lcd_string("Please draw by yourself");
   clearButton.drawButton(240, 0, 1, "Clear", font2);

}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600); // Turn the serial protocol ON

  delay (1000);

  //TFT initialization
   TFTLCD::begin();
   //LCD Clear the screen, backcolor
   TFTLCD::clear(backcolor);
   
   //Set the text area for the upper left corner (10, 10), the lower right corner (240,200), the color red, if the color is NULL or R0 G0 B0(black), is also not set text color 
   font.set_txt(10,10,240,32,TFTLCD::RGB_TO_565(255,0,0));
   
   //Set the text font color
   font.set_fontcolor(TFTLCD::RGB_TO_565(0,0,255));
   
   //Displays a string
   font.lcd_string("KeDeiTFT ");
   font.lcd_string("Please draw by yourself");
   clearButton.drawButton(240, 0, 1, "Clear", font2);
   
  // find the TFT display
  //  uint16_t identifier = TFT.readRegister(0x0);
  Serial.print(" Module = ");
  Serial.println(TFTLCD::MODULE);
  
}

void loop() {
     //check Touch current state detection
      TP::pen_down();
      
      //The touch screen is touch
      if(TP::flag && TP::y_val && TP::x_val) {
#if 0
        Serial.print ("iVal in pen_down() = ");
        Serial.print("  x = ");
        Serial.print(tp2.x);
        Serial.print("  y = ");
        Serial.print(tp2.y);
        Serial.print("  rxpiVal = ");
        Serial.print(tp2.rxpiVal);
        Serial.print("  rypiVal = ");
        Serial.print(tp2.rypiVal);
        Serial.print("  tp_x = ");
        Serial.print(tp2.tp_x);
        Serial.print("  tp_y = ");
        Serial.println(tp2.tp_y);
#endif
        if (clearButton.istouch(TP::x,TP::y)) {
          if (clearButton.penDownFlag != 0) {
            refreshScreen ();
            // no touch event pending so clear the pendown() with a call to penup()
            // for each of the buttons displayed.
            clearButton.penup();
          }
        } else {
           //draw  pixel
           TFTLCD::set_pixl(TP::x,TP::y,TFTLCD::RGB_TO_565(255,255,255));
        }
      }
}
