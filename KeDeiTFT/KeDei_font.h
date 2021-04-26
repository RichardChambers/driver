#ifndef   _KeDei_FONT_H_
#define   _KeDei_FONT_H_
#include "KeDei_TFT.h"

// Following definition will allow for the use of
// the standard sized font table or a smaller version
// of the font table which eliminates the lower case
// alphabetic letters which save a lot of memory.
// This can be turned on with the Arduino Uno in order
// to have more memory available.
//
// We also have found a smaller bitmap font table that
// is about half the size of the original bitmap font table.
// See https://github.com/dhepper/font8x8

#define SMALLER_FONT_TABLE
#define USE_FONT_8_B

class Font{
public:
	void	begin(void);
	void	set_txt(unsigned short x0,unsigned short y0,unsigned short x1,unsigned short y1,unsigned short txt_b_color);
	void    clear_txt(void);
	void 	clear_txt(unsigned short color);
	void	lcd_char(char _data);
	void	set_fontcolor(unsigned short f_color);
	void	lcd_string(char str[]);
	void	lcd_int(int value);

private:
	unsigned short	font_color;
	unsigned short	txt_backcolor;
	unsigned short	font_size;        // font height in pixels.
	unsigned short  font_leading;     // interval between rows in pixels.
	unsigned short	font_interval;    // interval between characters in pixels. kerning.
	unsigned short	txt_x0;
	unsigned short	txt_y0;
	unsigned short	txt_x1;
	unsigned short	txt_y1;
	unsigned short	now_x;
	unsigned short	now_y;
	char			buff[16];
};

extern  Font  font;
#endif