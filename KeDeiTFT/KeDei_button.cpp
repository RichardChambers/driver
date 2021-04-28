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
void Button::drawButton(unsigned short _x, unsigned short _y, bool _botton_moder, const char *str, Font & myFont)
{
//	the  botton moder 0--cube_button  1--circle_button
	x				= _x;
	y				= _y;
	botton_moder	= _botton_moder;
	if(_botton_moder)
	{
		TFTLCD::draw_buttom(x, y, x + x_size, y + y_size, 10, button_color);
		TFTLCD::draw_buttom_edge(x, y, x + x_size, y + y_size, 10, edge_up_color);
	}
	else
	{
		TFTLCD::draw_area(x, y, x + x_size, y + y_size, button_color);
		TFTLCD::draw_edge(x, y, x + x_size, y + y_size, 2, edge_up_color);
	}

	unsigned short len = strlen(str);
	myFont.set_txt(x + x_size / 2 - 9 * len / 2, y + y_size / 2 - 8, x + x_size - 2, y + y_size - 2, button_color);

	myFont.set_fontcolor(font_color);
	myFont.lcd_string(str);
}

/*****************************************
 *The function name ： istouch
 *Function  ： 判断按钮是否被按下,如果按下 返回true，否则false
 *Input  ： 坐标(_x,_y)
 *Output   ： none
 *Author   ： KeDei
 *Time   ： 2015/4/21
 ****************************************/
bool Button::istouch(unsigned short _x, unsigned short _y)
{
	if(x < _x && _x < x + x_size)
		if(y < _y && _y < y + y_size)
		{
			pendown();
			return true;
		}
	return false;
}

/*****************************************
 *The function name ： pendown
 *Function  ： 使能按钮按下
 *Input  ： none
 *Output   ： none
 *Author   ： KeDei
 *Time   ： 2015/4/21
 ****************************************/
void Button::pendown(void)
{
	penDownFlag = 1;     // indicate pen down state which is cleared when penup() is called.
	if(botton_moder)
	{
		TFTLCD::draw_buttom_edge(x, y, x + x_size, y + y_size, 10, edge_down_color);
	}
	else
	{
		TFTLCD::draw_edge(x, y, x + x_size, y + y_size, 2, edge_down_color);
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
void Button::penup(void)
{
	penDownFlag = 0;     // indicate pen down state is cleared by a penup(). pen down state is set by pindown().
	if(botton_moder)
	{
		TFTLCD::draw_buttom_edge(x, y, x + x_size, y + y_size, 10, edge_up_color);
	}
	else
	{
		TFTLCD::draw_edge(x, y, x + x_size, y + y_size, 2, edge_up_color);
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
void Button::resetsize(unsigned char _x_size, unsigned char _y_size)
{
	x_size = _x_size;
	y_size = _y_size;
}

/*****************************************
 *The function name ： resetsize
 *Function  ： 设定个人按钮的颜色属性，不使用默认颜色
 *Input  ： _edge_up_color, _edge_down_color,_button_color,_font_color
 *Output   ： none
 *Author   ： KeDei
 *Time   ： 2015/4/21
 ****************************************/
void Button::resetcolor(TFTLCD::TftColor _edge_up_color, TFTLCD::TftColor _edge_down_color, TFTLCD::TftColor _button_color, TFTLCD::TftColor _font_color)
{
	edge_up_color		= _edge_up_color;
	edge_down_color		= _edge_down_color;
	button_color		= _button_color;
	font_color			= _font_color;
}

