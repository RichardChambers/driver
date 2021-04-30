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

//#define USE_FONT_NONE
//#define SMALLER_FONT_TABLE
#define USE_FONT_8_B

class Font {
public:
	struct FontPos {
		unsigned short x;
		unsigned short y;
	};

	struct FontTable {
		static const unsigned char  Flags_UpperOnly = 0x01;    // bitmap font table has upper case letters only
		static const unsigned char  Flags_DoubleHigh = 0x02;   // display the character as twice as high as bitmap font indicates. 8 pixel high becomes 16 pixels high.
		static const unsigned char  Flags_DoubleWide = 0x04;   // display the character as twice as wide as bitmap font indicates. 8 pixel wide becomes 16 pixels wide.
		static const unsigned char  Flags_WrapLine = 0x08;     // wrap text to next line
		unsigned char bFlags;    // above flags to indicate special handling.
		unsigned char nRows;     // number of rows in the bitmap font table of character bitmaps
		unsigned char nCols;     // number of columns in the bitmap font table of character bitmaps. also font height or width in pixels.
		unsigned char *table;    // pointer to a bitmap font table of character bitmaps, static const unsigned char font_table[nRows][nCols];
								 // bitmap font table starts with bitmap for space character, 0x20, not control character 0x00.
	};

	Font() { begin(); }
	void	begin(void);
	void	set_txt(unsigned short x0, unsigned short y0, unsigned short x1, unsigned short y1, unsigned short txt_b_color);
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
	unsigned char setFontFlags(unsigned char xFlags) { unsigned char x = font_flags; font_flags = xFlags; return x; }
	void	lcd_string(const char str[]);

	unsigned short size_width(char *s1);
	unsigned short size_height();

	static void set_fonttable(unsigned short nRows, unsigned short nCols, unsigned char *pTable, unsigned char flags);
	static unsigned char  Font::mod_fonttable(unsigned char flags = 0);

private:
#if !defined(USE_FONT_NONE)
#if defined(USE_FONT_8_B)
#if defined(SMALLER_FONT_TABLE)
	static const unsigned char Font::font_table_local[59][8];
#else
	static const unsigned char Font::font_table_local[96][8];
#endif
#else
#if defined(SMALLER_FONT_TABLE)
	static const unsigned char Font::font_table_local[59][16]; 
#else
	static const unsigned char Font::font_table_local[95][16];
#endif
#endif
#endif
	static const unsigned short  font_leading = 6;     // interval between rows in pixels.
	static const unsigned short	 font_interval = 2;    // interval between characters in pixels. kerning.

	static FontTable font_table;      // configurable bitmap font font table to use for text.

	unsigned short	font_color;       // foreground or font color in RGB565 format
	unsigned short	txt_backcolor;    // background color in RGB565 format
	unsigned char   font_flags;       // font specific flags to override what is in the global font_table.

	unsigned short	txt_x0;           // top left row coordinate for text area
	unsigned short	txt_y0;           // top left column coordinate for text area
	unsigned short	txt_x1;           // bottom right row coordinate for text area
	unsigned short	txt_y1;           // bottom right column coordinate for text area
	unsigned short	now_x;            // top left row coordinate for next character
	unsigned short	now_y;            // top left column coordinate for next character
};

#endif