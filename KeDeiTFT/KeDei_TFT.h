/*
welcome use KeDeiTFT
*/
#ifndef         _KeDei_TFT_H_
#define         _KeDei_TFT_H_

#include		"KeDei_config.h"
#include		"Arduino.h"


class TFTLCD {
public:
		typedef unsigned short TftColor;   // color in RGB565 format.

		struct TftPos {
			unsigned short x;    // x or row coordinate
			unsigned short y;    // y or column coordinate
			TftPos  movePos(signed short xDist, signed short yDist) { x += xDist; y += yDist; return *this; }
			TftPos  setPos(unsigned short xP, unsigned short yP) { x = xP; y = yP; return *this; }
		};

		struct TftRect {
			unsigned short xLeft;   // x or row coordinate for top left corner
			unsigned short yLeft;   // y or column coordinate for top left corner
			unsigned short xRight;  // x or row coordinate for bottom right corner
			unsigned short yRight;  // y or columnet coordinate for bottom right corner
			TftRect  setCorners(TftPos &leftTop, TftPos & bottomRight) { xLeft = leftTop.x; yLeft = leftTop.y; xRight = bottomRight.x; yRight = bottomRight.y; return *this; }
			TftRect  movePos(signed short xDist, signed short yDist) { xLeft += xDist; yLeft += yDist;  xRight += xDist; yRight += yDist; return *this; }
			TftRect  setRight(signed short xDist, signed short yDist) { xRight = xLeft + xDist; yRight = yLeft + yDist; return *this; }
			TftRect  setRight(TftPos &pos, signed short xDist, signed short yDist) { xLeft = pos.x; yLeft = pos.y; xRight = xLeft + xDist; yRight = yLeft + yDist; return *this; }
			TftPos   getLeft(void) { TftPos p = { xLeft, yLeft }; return p; }
		};

		static void 	begin(void);
		static void     gpio_init(void);
		static void 	tft_init(void);
		static void 	clear(TftColor color);
		static void	    cmd(unsigned char cmd);
		static void  	w_data(unsigned char data);
		static int	    r_data(void);


		static bool 	set_area(unsigned short x0, unsigned short y0, unsigned short x1, unsigned short y1);
		static bool     set_area(TftRect &rect);
		static bool 	v_line(unsigned short x, unsigned short y, unsigned short len, TftColor color);
		static bool     v_line(TFTLCD::TftPos &p, unsigned short len, TftColor color);
		static bool	    h_line(unsigned short x, unsigned short y, unsigned short len, TftColor color);
		static bool	    h_line(TFTLCD::TftPos &p, unsigned short len, TftColor color);

		static bool     draw_area(unsigned short x0, unsigned short y0, unsigned short x1, unsigned short y1, TftColor color);
		static bool     draw_area(TFTLCD::TftRect &rect, TftColor color);
		static bool     touch_area(unsigned short x0, unsigned short y0, unsigned short x1, unsigned short y1, unsigned short px, unsigned short py);
		static bool     touch_area(TFTLCD::TftRect &rect, TFTLCD::TftPos &p);
		static bool     draw_glyph(unsigned short x0, unsigned short y0, TftColor fg_color, TftColor bg_color, unsigned char bitMap, unsigned char flags);
		static bool     draw_glyph(TFTLCD::TftPos &p, TftColor fg_color, TftColor bg_color, unsigned char bitMap, unsigned char flags);

		static bool 	draw_edge(unsigned short x0, unsigned short y0, unsigned short x1, unsigned short y1, unsigned short size, TftColor color);

		static bool 	set_pixl(unsigned short x, unsigned short y, TftColor color);
		static bool 	set_pixl(TFTLCD::TftPos &p, TftColor color);
		static bool     draw_buttom_edge(unsigned short x0, unsigned short y0, unsigned short x1, unsigned short y1, unsigned short circular_size, TftColor color);
		static bool	    draw_buttom(unsigned short x0, unsigned short y0, unsigned short x1, unsigned short y1, unsigned short circular_size, TftColor color);
		static unsigned short   RGB_TO_565(unsigned char r, unsigned char g, unsigned char b);
		static void     R565_TO_RGB(TftColor color, unsigned char rgb[3]);


		static bool	draw_circle(unsigned short x, unsigned short y, unsigned short R, TftColor color);
		static bool touch_circle(unsigned short x, unsigned short y, unsigned short R, unsigned short px, unsigned short py);
		static bool	draw_ring(unsigned short x, unsigned short y, unsigned short OR, unsigned short IR, TftColor color);
		static bool	FillCircle(unsigned short x, unsigned short y, unsigned short R, TftColor color);
		static bool    draw_pixl(unsigned short x, unsigned short y, unsigned short size, TftColor color);
		static bool    draw_pixl(TFTLCD::TftPos &p, unsigned short size, TftColor color);

		static void    draw_sin(int x, int y, float A, float w, float r, TftColor color);
		static void    Bresenhamline(int x0, int y0, int x1, int y1, TftColor color) ;

		static TftPos  movePos(TftPos &p, signed short xDist, signed short yDist) { p.x += xDist; p.y += yDist; return p; }
		static TftPos  setPos(TftPos &p, unsigned short x, unsigned short y) { p.x = x; p.y = y; return p; }

		static unsigned short x_all, y_all;

		static unsigned char  MODULE;

private:
	;
};

#endif
