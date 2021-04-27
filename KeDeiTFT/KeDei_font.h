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

class Font {
public:
	struct FontPos {
		unsigned short x;
		unsigned short y;
	};

	Font() { begin(); }
	void	begin(void);
	void	set_txt(unsigned short x0,unsigned short y0,unsigned short x1,unsigned short y1,unsigned short txt_b_color);
	void    clear_txt(void);
	void 	clear_txt(unsigned short color);
	void	lcd_char(char _data);
	unsigned short	set_fontcolor(unsigned short f_color) { unsigned short t = font_color; font_color = f_color; return t; }
	unsigned short	set_backcolor(unsigned short b_color) { unsigned short t = txt_backcolor; txt_backcolor = b_color; return t; }
	FontPos getFontPos(void) { FontPos p = { now_x, now_y }; return p; }
	FontPos setFontPos(unsigned short x0, unsigned short y0) { FontPos p = { now_x, now_y }; now_x = x0; now_y = y0; return p; }
	FontPos setFontPos(FontPos p0) { FontPos p = { now_x, now_y }; now_x = p0.x; now_y = p0.y; return p; }
	FontPos getTxtPosLeft(void) { FontPos p = { txt_x0, txt_y0 }; return p; }
	FontPos getTxtPosRight(void) { FontPos p = { txt_x1, txt_y1 }; return p; }
	void	lcd_string(const char str[]);

private:
	unsigned short	font_color;       // foreground or font color in RGB565 format
	unsigned short	txt_backcolor;    // background color in RGB565 format
	unsigned short	font_size;        // font height in pixels.
	unsigned short  font_leading;     // interval between rows in pixels.
	unsigned short	font_interval;    // interval between characters in pixels. kerning.
	unsigned short	txt_x0;           // top left row coordinate for text area
	unsigned short	txt_y0;           // top left column coordinate for text area
	unsigned short	txt_x1;           // bottom right row coordinate for text area
	unsigned short	txt_y1;           // bottom right column coordinate for text area
	unsigned short	now_x;            // top left row coordinate for next character
	unsigned short	now_y;            // top left column coordinate for next character
};

extern  Font  font;
#endif