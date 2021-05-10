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
#define SMALLER_FONT_TABLE
#define USE_FONT_5_B
//#define USE_FONT_6_B
//#define USE_FONT_7_B
//#define USE_FONT_8_B
//#define USE_FONT_13_B
//#define USE_FONT_16_B

class Font {
public:

	struct FontTable {
		static const unsigned short  Flags_DoubleHigh = 0x001;   // display the character as twice as high as bitmap font indicates. 8 pixel high becomes 16 pixels high.
		static const unsigned short  Flags_DoubleWide = 0x002;   // display the character as twice as wide as bitmap font indicates. 8 pixel wide becomes 16 pixels wide.
		static const unsigned short  Flags_TripleHigh = 0x004;   // display the character as three as high as bitmap font indicates. 8 pixel high becomes 16 pixels high.
		static const unsigned short  Flags_TripleWide = 0x008;   // display the character as three as wide as bitmap font indicates. 8 pixel wide becomes 16 pixels wide.
		static const unsigned short  Flags_UpperOnly  = 0x010;    // bitmap font table has upper case letters only
		static const unsigned short  Flags_InvertBitOrder = 0x020; // the bitmap table entries for each character are in reverse order
		static const unsigned short  Flags_RotateBits = 0x040;     // the bitmap table entries need to be rotated 90 degrees left to display properly
		static const unsigned short  Flags_NoLineFeed = 0x080;     // no line feed added to end of a text string automatically.
		static const unsigned short  Flags_WrapLine = 0x100;       // wrap text to next line
		unsigned short bFlags;    // above flags to indicate special handling.
		unsigned char nRows;     // number of rows in the bitmap font table of character bitmaps
		unsigned char nCols;     // number of columns in the bitmap font table of character bitmaps. also font height or width in pixels.
		unsigned char *table;    // pointer to a bitmap font table of character bitmaps, static const unsigned char font_table[nRows][nCols];
								 // bitmap font table starts with bitmap for space character, 0x20, not control character 0x00.
	};

	Font() { begin(); }
	void	begin(void);
	void	set_txt(unsigned short x0, unsigned short y0, unsigned short x1, unsigned short y1, TFTLCD::TftColor txt_b_color);
	void	set_txt(TFTLCD::TftRect &rect, TFTLCD::TftColor txt_b_color);
	void    clear_txt(void);
	void 	clear_txt(TFTLCD::TftColor);
	void	lcd_char(char _data);
	TFTLCD::TftColor	set_fontcolor(TFTLCD::TftColor f_color) { TFTLCD::TftColor t = font_color; font_color = f_color; return t; }
	TFTLCD::TftColor	set_backcolor(TFTLCD::TftColor b_color) { TFTLCD::TftColor t = txt_backcolor; txt_backcolor = b_color; return t; }
	inline TFTLCD::TftColor	get_fontcolor(void) { return font_color; }
	inline TFTLCD::TftColor	get_backcolor(void) { return txt_backcolor; }
	TFTLCD::TftPos getFontPos(void) { TFTLCD::TftPos p = { now_x, now_y }; return p; }
	TFTLCD::TftPos setFontPos(unsigned short x0, unsigned short y0) { TFTLCD::TftPos p = { now_x, now_y }; now_x = x0; now_y = y0; return p; }
	TFTLCD::TftPos setFontPos(TFTLCD::TftPos p0) { TFTLCD::TftPos p = { now_x, now_y }; now_x = p0.x; now_y = p0.y; return p; }
	TFTLCD::TftPos getTxtPosLeft(void) { TFTLCD::TftPos p = { txt_x0, txt_y0 }; return p; }
	TFTLCD::TftPos getTxtPosRight(void) { TFTLCD::TftPos p = { txt_x1, txt_y1 }; return p; }
	unsigned char setFontFlags(unsigned char xFlags) { unsigned char x = font_flags; font_flags = xFlags | (font_table.bFlags & (Font::FontTable::Flags_UpperOnly | Font::FontTable::Flags_InvertBitOrder | Font::FontTable::Flags_RotateBits)); return x; }
	void	lcd_string(const char str[]);

	unsigned short size_width(char *s1);
	unsigned short size_height();

	static void set_fonttable(unsigned short nRows, unsigned short nCols, unsigned char *pTable, unsigned char flags);
	static unsigned char  Font::mod_fonttable(unsigned char flags = 0);
	static FontTable font_table;      // configurable bitmap font font table to use for text.


private:
#if !defined(USE_FONT_NONE)
#if defined(USE_FONT_5_B)
#if defined(SMALLER_FONT_TABLE)
	static const unsigned char Font::font_table_local[59][5];
#else
	static const unsigned char Font::font_table_local[96][5];
#endif
#elif defined(USE_FONT_6_B)
#if defined(SMALLER_FONT_TABLE)
	static const unsigned char Font::font_table_local[59][6];
#else
	static const unsigned char Font::font_table_local[96][6];
#endif
#elif defined(USE_FONT_7_B)
#if defined(SMALLER_FONT_TABLE)
	static const unsigned char Font::font_table_local[59][7];
#else
	static const unsigned char Font::font_table_local[96][7];
#endif
#elif defined(USE_FONT_8_B)
#if defined(SMALLER_FONT_TABLE)
	static const unsigned char Font::font_table_local[59][8];
#else
	static const unsigned char Font::font_table_local[96][8];
#endif
#elif defined(USE_FONT_13_B)
#if defined(SMALLER_FONT_TABLE)
	static const unsigned char Font::font_table_local[59][13];
#else
	static const unsigned char Font::font_table_local[95][13];
#endif
#elif defined(USE_FONT_16_B)
#if defined(SMALLER_FONT_TABLE)
	static const unsigned char Font::font_table_local[59][16]; 
#else
	static const unsigned char Font::font_table_local[95][16];
#endif
#endif
#endif
	static const unsigned short  font_leading = 6;     // interval between rows in pixels.
	static const unsigned short	 font_interval = 2;    // interval between characters in pixels. kerning.

	TFTLCD::TftColor  font_color;       // foreground or font color in RGB565 format
	TFTLCD::TftColor  txt_backcolor;    // background color in RGB565 format
	unsigned char     font_flags;       // font specific flags to override what is in the global font_table.

	unsigned short	  txt_x0;           // top left row coordinate for text area
	unsigned short	  txt_y0;           // top left column coordinate for text area
	unsigned short	  txt_x1;           // bottom right row coordinate for text area
	unsigned short	  txt_y1;           // bottom right column coordinate for text area
	unsigned short	  now_x;            // top left row coordinate for next character
	unsigned short	  now_y;            // top left column coordinate for next character
};

#endif