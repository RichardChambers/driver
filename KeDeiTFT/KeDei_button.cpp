/*
welcome use this file! 
Please visit kedei.taobao.com
qq310953417
vision 1.1 2015/4/21
*/


#include	"KeDei_button.h"
#include    "string.h"

// An example sketch showing how the KeDei TFT library can be used.
//
//    #include <KeDei_TFT.h>
//    #include <KeDei_TP.h>
//    #include "KeDei_font.h"
//    #include "KeDei_button.h"
//    
//    Font    font1;       // used for informational text displayed
//
//    Font    font2;       // used with scanButton below
//    Button  scanButton;  // button to trigger function call
//    
//    void setup() {
//    	//TFT initialization and font initialization
//    	TFTLCD::begin();
//    
//    	//LCD Clear the screen, backcolor
//    	TFTLCD::TftColor bgColor = TFTLCD::RGB_TO_565(0, 200, 0);
//    	
//    	TFTLCD::clear(bgColor);
//    	
//    	// Set the text area for the upper left corner (5, 5), the lower right corner (320,200).
//    	// Set the font color to red, if the color is NULL or R0 G0 B0(black), is also not set text color 
//    	font1.set_txt(5, 5, 320, 200, bgColor);
//    	font1.lcd_string("Scanner Scale");
//    	font1.lcd_string("070177155766 \n  Twinings English Afternoon tea");
//    	
//    	scanButton.drawButton(100, 100, 1, "Button", font2);
//    }
//    
//    void loop() {
//    	//check Touch current state detection
//    	TP::pen_down();
//    
//    	if (TP::flag && TP::y_val && TP::x_val) {
//    		// The touch screen is touched. Check which button was pressed
//    
//    		if (scanButton.penDownFlag == 0 && scanButton.istouch(TP::x, TP::y))
//    		{
//    			handle_command("11");
//    		}
//    	}
//    	else {
//          // no touch event pending so clear the pendown() with a call to penup()
//          // for each of the buttons displayed.
//    		scanButton.penup();
//    	}



/*****************************************
 *The function name ： drawButton
 *Function  ： Draw the button (_x,_y) in the upper-left corner, rounded if _botton_moder is true (1), square otherwise,
The text content of the button is * str;
 *Input  ： Coordinates (_x,_y), button type _botton_moder, button content *str


 *Output   ： none
 *Author   ： KeDei
 *Time   ： 2015/4/21
 ****************************************/
bool ButtonShared::drawButton(unsigned short _x, unsigned short _y, bool _botton_moder, const char *str, Font & myFont)
{
//	the  botton moder 0--cube_button  1--circle_button
	x				= _x;
	y				= _y;
	if (myData == nullptr) {
		return false;
	} else {
		myData->botton_moder	= _botton_moder;
		if(_botton_moder)
		{
			TFTLCD::draw_buttom(x, y, x + myData->x_size, y + myData->y_size, 10, myData->button_color);
			TFTLCD::draw_buttom_edge(x, y, x + myData->x_size, y + myData->y_size, 10, myData->edge_up_color);
		}
		else
		{
			TFTLCD::draw_area(x, y, x + myData->x_size, y + myData->y_size, myData->button_color);
			TFTLCD::draw_edge(x, y, x + myData->x_size, y + myData->y_size, 2, myData->edge_up_color);
		}

		myFont.set_txt(x + myData->x_size / 2 - myFont.size_width(str) / 2, y + myData->y_size / 2 - myFont.size_height() / 2, x + myData->x_size - 2, y + myData->y_size - 2, myData->button_color);

		myFont.set_fontcolor(myData->font_color);
		myFont.lcd_string(str);

		return true;   // always return true to allow use in logical expressions
	}
}

bool ButtonShared::drawButton(TFTLCD::TftPos &p, bool _botton_moder, const char *str, Font & myFont)
{
	return drawButton(p.x, p.y, _botton_moder, str, myFont);
}

/*****************************************
 *The function name ： istouch
 *Function  ： 判断按钮是否被按下,如果按下 返回true，否则false
 *Input  ： 坐标(_x,_y)
 *Output   ： none
 *Author   ： KeDei
 *Time   ： 2015/4/21
 ****************************************/
bool ButtonShared::istouch(unsigned short _x, unsigned short _y)
{
	return (myData != nullptr) && TFTLCD::touch_area(x, y, x + myData->x_size, y + myData->y_size, _x, _y) && pendown();
}

bool ButtonShared::istouch(void)
{
	return istouch(TP::x, TP::y);
}

bool ButtonShared::isTouchState(void)
{
	return (penDownFlag == 0 && istouch(TP::x, TP::y));
}

/*****************************************
 *The function name ： pendown
 *Function  ： 使能按钮按下
 *Input  ： none
 *Output   ： none
 *Author   ： KeDei
 *Time   ： 2015/4/21
 ****************************************/
bool ButtonShared::pendown()
{
	if (myData == nullptr) {
		return false;
	}
	else {
		penDownFlag = 1;
		if(myData->botton_moder)
		{
			TFTLCD::draw_buttom_edge(x, y, x + myData->x_size, y + myData->y_size, 10, myData->edge_down_color);
		}
		else
		{
			TFTLCD::draw_edge(x, y, x + myData->x_size, y + myData->y_size, 2, myData->edge_down_color);
		}

		return true;   // always return true to allow use in logical expressions
	}
}

/*****************************************
 *The function name ： pendown
 *Function  ： 使能按钮弹起
 *Input  ： none
 *Output   ： none
 *Author   ： KeDei
 *Time   ： 2015/4/21
 ****************************************/
bool ButtonShared::penup()
{
	if (myData == nullptr) {
		return false;
	}
	else {
		penDownFlag = 0;
		if (myData->botton_moder)
		{
			TFTLCD::draw_buttom_edge(x, y, x + myData->x_size, y + myData->y_size, 10, myData->edge_up_color);
		}
		else
		{
			TFTLCD::draw_edge(x, y, x + myData->x_size, y + myData->y_size, 2, myData->edge_up_color);
		}

		return true;   // always return true to allow use in logical expressions
	}
}

/*if you want  to change the button size or the color,you can use  the  follow function to achieve your purpose,
but you  must do it before use the Button() function*/
/*****************************************
 *The function name ： resetsize
 *Function  ： 设定个人按钮的大小，不使用默认大小
 *Input  ： _x_size,_y_size
 *Output   ： none
 *Author   ： KeDei
 *Time   ： 2015/4/21
 ****************************************/
void ButtonShared::resetsize(unsigned char _x_size, unsigned char _y_size)
{
	if (myData != nullptr) {
		myData->x_size = _x_size;
		myData->y_size = _y_size;
	}
}

/*****************************************
 *The function name ： resetsize
 *Function  ： 设定个人按钮的颜色属性，不使用默认颜色
 *Input  ： _edge_up_color, _edge_down_color,_button_color,_font_color
 *Output   ： none
 *Author   ： KeDei
 *Time   ： 2015/4/21
 ****************************************/
void ButtonShared::resetcolor(TFTLCD::TftColor _edge_up_color, TFTLCD::TftColor _edge_down_color, TFTLCD::TftColor _button_color, TFTLCD::TftColor _font_color)
{
	if (myData != nullptr) {
		myData->edge_up_color		= _edge_up_color;
		myData->edge_down_color		= _edge_down_color;
		myData->button_color		= _button_color;
		myData->font_color			= _font_color;
	}
}

