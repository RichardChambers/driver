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

All of these graphics functions create their images by paining individual pixels with various colors.

## Changes made to this fork

### Changed bitmap font table to reduce memory requirements

The first change with the greatest impact was to add to the `Font` class an 8x8 bitmap font in addition
to the already existing 16x16 bitmap font. Preprocessor directives are used to select one or the other.
Allowing the selection of an 8x8 bitmap font significantly reduced the size of the bitmap font table.

An additional Preprocessor directive is used to all for a further reduction in the bitmap font table by
eliminating lower case letters. A change in the function `lcd_char()` performs a lower case to upper case
conversion should the character being displayed be a lower case letter.

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
