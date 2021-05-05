/*
welcome use KeDeiTFT

*/
#ifndef         _KeDei_button_H_
#define         _KeDei_button_H_

#include	"KeDei_TFT.h"
#include 	"KeDei_TP.h"
#include	"KeDei_font.h"
#include	"Arduino.h"

struct ButtonData {
public:
	ButtonData(unsigned short sizeWidth = 64, unsigned short sizeHigh = 40)
	{
		//the  button size
		x_size = sizeWidth;
		y_size = sizeHigh;
		//the button  abort color
		edge_up_color = 0xffff;    // RGB565 value for white
		edge_down_color = 0x6b4d;
		button_color = 0x4898;
		font_color = 0xffff;    // RGB565 value for white
									   //the  botton moder 0--cube_button  1--circle_button
		botton_moder = 0;
	}

	//the  button size
	unsigned char	x_size;
	unsigned char	y_size;
	//the  button  abort color
	TFTLCD::TftColor	edge_up_color;
	TFTLCD::TftColor	edge_down_color;
	TFTLCD::TftColor	button_color;
	TFTLCD::TftColor	font_color;
	//the  botton moder 0--cube_button , 1--circle_button
	bool			botton_moder;
};


class  ButtonShared
{
public:
	ButtonShared(ButtonData &buttonData) : myData(&buttonData)
	{
	}

	ButtonShared() : myData(nullptr)
	{
	}

	bool setSharedData(ButtonData &buttonData) { myData = &buttonData; return 1; }
	bool drawButton(unsigned short _x, unsigned short _y, bool _botton_moder, const char *str, Font & myFont);
	bool drawButton(TFTLCD::TftPos &p, bool _botton_moder, const char *str, Font & myFont);
	bool istouch(unsigned short _x, unsigned short _y);
	bool istouch(void);
	bool isTouchState(void);
	bool pendown(void);
	bool penup(void);
	/*if you want  to change the butom size or the color,you can use  the  follow function to achieve your purpose,
	but you  must do it before use the drawbutton() function;also  if you  always change the auto value ,you can change the button() function*/
	void resetsize(unsigned char _x_size, unsigned char _y_size);
	void resetcolor(TFTLCD::TftColor _edge_up_color, TFTLCD::TftColor _edge_down_color, TFTLCD::TftColor _button_color, TFTLCD::TftColor _font_color);

private:
	ButtonData *myData;

	// following data is unique to each button and can not be shared
	// between buttons.
	//the  position(x,y);
	unsigned short	x;
	unsigned short	y;
	unsigned char   penDownFlag;      // set by successful istouch() call or when the pendown() function is called. cleared when the penup() function is called.
};

class  Button : public ButtonShared
{
public:
	Button(unsigned short sizeWidth = 64, unsigned short sizeHigh = 40) : localData(sizeWidth, sizeHigh)
	{
		setSharedData(localData);
	}
	
private:
	ButtonData localData;
};


#endif
