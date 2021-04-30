/*
welcome use KeDeiTFT
*/
#ifndef         _KeDei_TFT_H_
#define         _KeDei_TFT_H_

#include		"KeDei_config.h"
#include		"Arduino.h"


class TFTLCD {
public:
		typedef unsigned short TftColor;

		static void 	begin(void);
		static void     gpio_init(void);
		static void 	tft_init(void);
		static void 	clear(TftColor color);
		static void	    cmd(unsigned char cmd);
		static void  	w_data(unsigned char data);
		static int	    r_data(void);


		static void 	set_area(unsigned short x0,unsigned short y0,unsigned short x1,unsigned short y1);
		static void 	v_line(unsigned short x,unsigned short y,unsigned short len, TftColor color);
		static void	    h_line(unsigned short x,unsigned short y,unsigned short len, TftColor color);

		static void     draw_area(unsigned short x0,unsigned short y0,unsigned short x1,unsigned short y1, TftColor color);
		static void 	draw_edge(unsigned short x0,unsigned short y0,unsigned short x1,unsigned short y1,unsigned short size, TftColor color);

		static void     draw_glyph(unsigned short x0, unsigned short y0, TftColor fg_color, TftColor bg_color, unsigned char bitMap, unsigned char flags);
		static void 	set_pixl(unsigned short x, unsigned short y, TftColor color);
		static void     draw_buttom_edge(unsigned short x0,unsigned short y0,unsigned short x1,unsigned short y1,unsigned short circular_size, TftColor color);
		static void	    draw_buttom(unsigned short x0,unsigned short y0,unsigned short x1,unsigned short y1,unsigned short circular_size, TftColor color);
		static unsigned short   RGB_TO_565(unsigned char r,unsigned char g,unsigned char b);
		static void     R565_TO_RGB(TftColor color, unsigned char rgb[3]);


		static void	draw_circle(unsigned short x,unsigned short y,unsigned short R, TftColor color);
		static void	draw_ring(unsigned short x,unsigned short y,unsigned short OR,unsigned short IR, TftColor color);
		static void	FillCircle(unsigned short x,unsigned short y,unsigned short R, TftColor color);

		static void    draw_sin(int x,int y,float A,float w,float r, TftColor color);
		static void    draw_pixl(unsigned short x,unsigned short y,unsigned short size, TftColor color);
		static void    Bresenhamline(int x0,int y0,int x1, int y1, TftColor color) ;

		static unsigned short x_all, y_all;

		static unsigned char  MODULE;

private:
	;
};

#endif
