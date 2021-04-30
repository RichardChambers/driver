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
 *The function name �� drawButton
 *Function  �� Draw the button (_x,_y) in the upper-left corner, rounded if _botton_moder is true (1), square otherwise,
The text content of the button is * str;
 *Input  �� Coordinates (_x,_y), button type _botton_moder, button content *str


 *Output   �� none
 *Author   �� KeDei
 *Time   �� 2015/4/21
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

	myFont.set_txt(x + x_size / 2 - myFont.size_width(str) / 2, y + y_size / 2 - myFont.size_height() / 2, x + x_size - 2, y + y_size - 2, button_color);

	myFont.set_fontcolor(font_color);
	myFont.lcd_string(str);
}

/*****************************************
 *The function name �� istouch
 *Function  �� �жϰ�ť�Ƿ񱻰���,������� ����true������false
 *Input  �� ����(_x,_y)
 *Output   �� none
 *Author   �� KeDei
 *Time   �� 2015/4/21
 ****************************************/
bool Button::istouch(unsigned short _x, unsigned short _y)
{
	return TFTLCD::touch_area(x, y, x + x_size, y + y_size, _x, _y) && pendown();
}

/*****************************************
 *The function name �� pendown
 *Function  �� ʹ�ܰ�ť����
 *Input  �� none
 *Output   �� none
 *Author   �� KeDei
 *Time   �� 2015/4/21
 ****************************************/
bool Button::pendown(void)
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

	return true;   // always return true to allow use in logical expressions
}

/*****************************************
 *The function name �� pendown
 *Function  �� ʹ�ܰ�ť����
 *Input  �� none
 *Output   �� none
 *Author   �� KeDei
 *Time   �� 2015/4/21
 ****************************************/
bool Button::penup(void)
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

	return true;   // always return true to allow use in logical expressions
}

/*if you want  to change the button size or the color,you can use  the  follow function to achieve your purpose,
but you  must do it before use the Button() function*/
/*****************************************
 *The function name �� resetsize
 *Function  �� �趨���˰�ť�Ĵ�С����ʹ��Ĭ�ϴ�С
 *Input  �� _x_size,_y_size
 *Output   �� none
 *Author   �� KeDei
 *Time   �� 2015/4/21
 ****************************************/
void Button::resetsize(unsigned char _x_size, unsigned char _y_size)
{
	x_size = _x_size;
	y_size = _y_size;
}

/*****************************************
 *The function name �� resetsize
 *Function  �� �趨���˰�ť����ɫ���ԣ���ʹ��Ĭ����ɫ
 *Input  �� _edge_up_color, _edge_down_color,_button_color,_font_color
 *Output   �� none
 *Author   �� KeDei
 *Time   �� 2015/4/21
 ****************************************/
void Button::resetcolor(TFTLCD::TftColor _edge_up_color, TFTLCD::TftColor _edge_down_color, TFTLCD::TftColor _button_color, TFTLCD::TftColor _font_color)
{
	edge_up_color		= _edge_up_color;
	edge_down_color		= _edge_down_color;
	button_color		= _button_color;
	font_color			= _font_color;
}

