## KeDeiTFT Library

The KeDeiTFT library is used with the 3.5" TFT Touchscreen Display sold by Osoyoo and others. The display
is a shield that can be used with either an Arduino Uno or an ATmega 2360 microcontroller.

The source code appears to be used with several different TFT Touchscreen displays of various sizes and
resolutions. The 3.5" TFT display has a resolution of 480 by 320 pixels.

The library is composed of several components:
 - the hardware layer component providing a set of drawing functions
 - the font component for displaying text
 - the touch component for detecting touch events and capturing touch coordinates

### Hardware layer

The hardware layer offers a couple of low level functions that interact with the display hardware
to turn pixels on and off. This is done by sending a series of commands with arguments to specify
an area of the display to be changed followed by a series of writes, one for each pixel, to paint
each pixel a particular color.

The display uses RGB565 color specification rather than RGB. The difference is in the size of the
color data. The RGB565 color data is an unsigned short of 16 bits with the Red, Green, Blue values
packed and with fewer bits. Red is a 5 bit value, Green is a 6 bit value, and Blue is a 5 bit value
hence the name RGB565.

The most common use of RGB color data is three bytes with each byte specifing a value between 0 and 255 for each
of the colors Red, Green, and Blue. However this does depend on the color range of the graphics unit and
the display as there are also RGB color specifications with each color value being sized larger than a
byte allowing more subtle colors made up of color data with each color component specified by a 16 bit
or a 32 bit value rather than an 8 bit byte value.

### Drawing primitives

The TFTLCD class in the files KeDei_TFT.cpp and KeDei_TFT.h contain the hardware layer along with a set
of drawing primitives that use the basic hardware layer to draw various kinds of geometrical graphics
such as lines, circles, rectangles, and curves both filled and unfilled.

All of these graphics functions create their images by painting individual pixels with various colors. The
available primitives, excluding a couple of utility functions for drawing buttons, are:
 - TFTLCD::v_line(unsigned short x, unsigned short y, unsigned short len, TftColor color)
 - TFTLCD::h_line(unsigned short x, unsigned short y, unsigned short len, TftColor color)
 - TFTLCD::draw_area(unsigned short x0, unsigned short y0, unsigned short x1, unsigned short y1, TftColor color)
 - TFTLCD::draw_circle(unsigned short x, unsigned short y, unsigned short R, TftColor color)
 - TFTLCD::draw_ring(unsigned short x, unsigned short y, unsigned short OR, unsigned short IR, TftColor color)
 - TFTLCD::FillCircle(unsigned short x, unsigned short y, unsigned short R, TftColor color)
 - TFTLCD::draw_sin(int x, int y, float A, float w, float r, TftColor color)
 - TFTLCD::Bresenhamline(int x0, int y0, int x1, int y1, TftColor color)

In addition there are two functions for converting between RGB color values and RGB565 color values. Converting
an RGB color value to an RGB565 value does result in the loss of a couple of the least significant bits of each of
the RGB color values. This means that a particular color value expressed in RGB may not be the same color value if
it is converted to RGB565 and then converted back. The conversion functions are:
 - unsigned short TFTLCD::RGB_TO_565(unsigned char r, unsigned char g, unsigned char b)
 - void TFTLCD::R565_TO_RGB(TftColor color, unsigned char rgb[3])

## Changes made to this fork

### Changed bitmap font table to reduce memory requirements

The first change with the greatest impact was to add to the `Font` class an 8x8 bitmap font in addition
to the already existing 16x16 bitmap font. Preprocessor directives are used to select one or the other.
Allowing the selection of an 8x8 bitmap font significantly reduced the size of the bitmap font table.

An additional Preprocessor directive is used to allow for a further reduction in the bitmap font table by
eliminating lower case letters. A change in the function `lcd_char()` performs a lower case to upper case
conversion should the character being displayed be a lower case letter.

See the defined constants in the header file KeDei_font.h:
 - `SMALLER_FONT_TABLE` removes the lower case letters and translates lower case to upper case
 - `USE_FONT_8_B` changes from the 16x16 font to an 8x8 font

The 8x8 bitmap font displays text that is smaller than the 16x16 font however it is readable. Using the
smaller font reduces the memory required for the bitmap font table and also allows for more text to be
displayed.

### Added additional bitmap font tables

As part of working to reduce the amount of memory required for bitmap font tables, we have found a couple of
different variations of bitmap fonts. One of these is 8x5 meaning each row of the bitmap table is 5 columns.
Howver we have also found that the orientation of the text character represented by a row of bitmaps in the
font table can be different than what our previous two bitmap fonts, the original 8x16 and the added 8x8 bitmap
fonts, encode. See [differences in bitmap or rasterized font bitmaps and text display on 3.5" TFT LCD](https://stackoverflow.com/questions/67465098/differences-in-bitmap-or-rasterized-font-bitmaps-and-text-display-on-3-5-tft-lc)

We have added character bitmap transformations to allow the use of these other bitmap font representations.

We now have bitmap font tables for the ASCII characters from space (0x20) to close curly brace (0x7d) which
can be configured to eliminate lower case letters to save memory.
 - 8x5 with each row being 5 columns wide
 - 8x13 with each row being 13 columns wide

These new tables are in addition to the existing tables of an 8x16, each row 16 columns wide, and 8x8, each
row 8 columns wide. See the file `KeDei_font.h` and the defines `USE_FONT_5_B` and `USE_FONT_13_B`.

### Reformated source code and added comments

The first large change has been to reformat the source code in places to make it more readable and to
add and update comments to better explain the source code especially those parts in the `TFTLCD` class
which interact with the ILI9486 TFT LCD Display Driver Chip. I'm using the following datasheet for my
information: Document No: ILI9486_SPEC_V001.pdf from ILI TECHNOLOGY CORP.

### Made `TFTLCD` and `TP` classes static

The next large change has involved making the class `TFTLCD` composed of `static` components and methods
so that an object of type `TFTLCD` does not need to be created. The same approach has been used with the
`TP` class for processing the touch screen events.

The `Font` class and the `Button` class both still require instantiating objects of those classes since a UI
may have multiple font areas and multiple buttons. The other two classes, `TFTLCD` and `TP` were really just
singleton objects anyway.

### Refactor source code to improve coupling and cohesion

There has been some refactoring of code in order to reduce coupling between components and improve the cohesion
of the classes. For example the drawing of the text in the `Font` class method `lcd_char()` was using the
`w_data()` function of the `TFTLCD` class to directly write into the frame buffer of the display. We have
introduced a new method in the `TFTLCD` class, `TFTLCD::draw_glyph()` to write a row of pixels using the
bitmap font for that character.

This new function also handles overwriting of an area on the screen properly
by using the font color of the character to place a pixel of the displayed character or the text back ground
color to place a pixel that is not part of the character glyph. The result is that when text is overwritten
the new text completely replaces the old rather than the pixels from the older text showing through.

### Allow user of library to provide their own bitmap font table easily

The `Font` class now has a new function, `set_fonttable()` which allows the user of the library to specify
their own bitmap font table easily.

Another useful addition are the text drawing flags which allow the user of the library to specify special
treatment to the text as it is drawn. These flags are bit constants which can be combined with the bitwise
logic operators. The flags are:
 -	Flags_UpperOnly - the bitmap font table has upper case letters only
 -	Flags_DoubleHigh - display the text as twice as high as bitmap font indicates. 8 pixel high becomes 16 pixels high.
 -	Flags_DoubleWide - display the text as twice as wide as bitmap font indicates. 8 pixel wide becomes 16 pixels wide.
 -	Flags_TrippleHigh - display the text as three times as high as bitmap font indicates. 8 pixel high becomes 24 pixels high.
 -	Flags_TrippleWide - display the text as three times as wide as bitmap font indicates. 8 pixel wide becomes 24 pixels wide.
 -	Flags_NoLineFeed - display a string and do not automatically add a new line to move to the next line in the text region
 -	Flags_WrapLine - display a string and if it is too long for the width of a region wrap to next line rather than clip it
 -	Flags_InvertBitOrder - used with bitmap font tables that require a right to left order of processing bits rather than left to right.
 -	Flags_RotateBits - used with a bitmap font table whose character map is rotated 90 degrees clockwise.

The user of the library can use these flags to vary the look of the text displayed allowing a greater variety in the
user interface.

The last two flags, Flags_InvertBitOrder and Flags_RotateBits, are used with unusual bitmap font tables which require that the
bitmap be modified by a transformation before using it to set the pixels of a character.

## Stack Overflow posts

https://stackoverflow.com/questions/67465098/differences-in-bitmap-or-rasterized-font-bitmaps-and-text-display-on-3-5-tft-lc

https://stackoverflow.com/questions/67259938/reducing-memory-required-for-kedei-tft-library-used-with-3-5-tft-display-with-a
