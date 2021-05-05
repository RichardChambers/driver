/*
welcome use KeDeiTFT
*/
#ifndef 	_KeDei_TP_H_
#define		_KeDei_TP_H_

#include 	"KeDei_TFT.h"
#include	"Arduino.h"

class TP{
public:
	static unsigned short 	x;     // screen row or x coordinate of touch position
	static unsigned short 	y;     // screen column or y coordinate of touch position
	static bool	flag;              // if true then valid touch event with touch position available.
	static bool	x_val;             // if true then the x coordinate of the touch position is probably valid. see get_xy()
	static bool	y_val;             // if true then the y coordinate of the touch position is probably valid. see get_xy()
	
	static bool    pen_down(void);
	static TFTLCD::TftPos pen_point(void) { TFTLCD::TftPos p{ x, y }; return p; }
	
private:
	static void	get_xy(void);

};

#endif