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

