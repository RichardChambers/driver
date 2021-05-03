
#include "KeDei_TFT.h"
#include "KeDei_SD.h"

// These read data from the SD card file and convert them to big endian 
// (the data is stored in little endian format!)

// LITTLE ENDIAN!
static uint16_t read16(SDFile bmpFile) {
	uint16_t d = 0;
	uint8_t b = 0;
	b = bmpFile.read();
	d = bmpFile.read();
	d <<= 8;
	d |= b;
	return d;
}


// LITTLE ENDIAN!
static uint32_t read32(SDFile bmpFile) {
	uint32_t d = 0;
	uint16_t b = 0;

	b = read16(bmpFile);
	d = read16(bmpFile);
	d <<= 16;
	d |= b;
	return d;
}

static boolean KeDei_SD::bmpReadHeader(SDFile &bmpFile, BMP_Header &bmpHeader) {


	if (read16(bmpFile) != 0x4D42) {
		// magic bytes missing
		return false;
	}

	bmpHeader.bmpColorTableoffset = 54;

	// read file size
	bmpHeader.bmpFileSize = read32(bmpFile);

	// read and ignore creator bytes
	read32(bmpFile);
	bmpHeader.bmpImageoffset = read32(bmpFile);

	// read DIB header
	read32(bmpFile);
	bmpHeader.bmpWidth = read32(bmpFile);
	bmpHeader.bmpHeight = read32(bmpFile);

	bmpHeader.bmpPlanes = read16(bmpFile);
	if (bmpHeader.bmpPlanes != 1)
		return false;

	bmpHeader.bmpDepth = read16(bmpFile);
#if !defined(SUPPORT_8_BIT_DEPTH)
	if (bmpHeader.bmpDepth < 16)
		return false;
#endif

	bmpHeader.bmpCompression = read32(bmpFile);
	if (bmpHeader.bmpCompression != 0) {
		// compression not supported!
		return false;
	}

	read32(bmpFile);    // image size, size of the raw bitmap data
	read32(bmpFile);    // horizontal resolution, pixel per meter
	read32(bmpFile);    // vertical resolution, pixel per meter

	bmpHeader.bmpPaletteCount = read32(bmpFile);

	return true;
}

#if defined(SUPPORT_8_BIT_DEPTH)
//  See http://www.cs.ucc.ie/~gavin/cs1050/the_internet/slides/ch07s01s02.html.htm
static void fetchColorTable(SDFile &bmpFile, uint32_t bmpColorTableoffset, KeDei_SD::ctstruct *ctBuffer, unsigned short size)
{
	KeDei_SD::ctstruct *ctBufferEnd = ctBuffer + size;

	bmpFile.seek(bmpColorTableoffset);
	for (; ctBuffer < ctBufferEnd; ctBuffer++) {
		unsigned char buffer[4];
		bmpFile.read(buffer, 4);
		ctBuffer->blue = buffer[0];     // color table index for the color
		ctBuffer->green = buffer[1];    // color hue value
		ctBuffer->red = buffer[2];      // color intensity value
		// ignore the fourth byte of the set.
	}
}
#endif

static void KeDei_SD::bmpdraw(SDFile &bmpFile, BMP_Header &bmpHeader, unsigned short x0, unsigned short y0, unsigned short x1, unsigned short y1) {
	static const unsigned short BuffPixel = 24;

#if defined(SUPPORT_8_BIT_DEPTH)
	KeDei_SD::ctstruct ctBuffer[256];
	if (bmpHeader.bmpDepth == 8) fetchColorTable(bmpFile, bmpHeader.bmpColorTableoffset, ctBuffer, 256);
#endif

	bmpFile.seek(bmpHeader.bmpImageoffset);

	uint8_t sdbuffer[3 * BuffPixel];  // 3 * pixels to buffer
	uint8_t buffidx = 3 * BuffPixel;

	TFTLCD::set_area(x0, y0, x1, y1);
	for (int i = 0; i < bmpHeader.bmpHeight; i++) {
		for (int j = 0; j < bmpHeader.bmpWidth; j++) {
			unsigned short rgb565 = 0;

			switch (bmpHeader.bmpDepth) {
			case 24:
				// read more pixels
				if (buffidx >= 3 * BuffPixel) {
					bmpFile.read(sdbuffer, 3 * BuffPixel);
					buffidx = 0;
				}
				// convert pixel from RGB 888 to RGB 565
				rgb565 |= sdbuffer[buffidx++] >> 3;          // blue, 5 bits
				rgb565 |= (sdbuffer[buffidx++] >> 2) << 5;   // green, 6 bits
				rgb565 |= (sdbuffer[buffidx++] >> 3) << 11;  // red, 5 bits
				break;
#if defined(SUPPORT_8_BIT_DEPTH)
			case 4:
				// read more pixels
				if (buffidx >= 1 * BuffPixel) {
					bmpFile.read(sdbuffer, 1 * BuffPixel);
					buffidx = 0;
				}

				// look up the color value in the color table
				// convert pixel from RGB 888 to RGB 565
				rgb565 |= ctBuffer[sdbuffer[buffidx]].blue >> 3;
				rgb565 |= (ctBuffer[sdbuffer[buffidx]].green >> 2) << 5;
				rgb565 |= (ctBuffer[sdbuffer[buffidx]].red >> 3) << 11;
				buffidx++;
				break;
			case 8:
				// read more pixels
				if (buffidx >= 1 * BuffPixel) {
					bmpFile.read(sdbuffer, 1 * BuffPixel);
					buffidx = 0;
				}

				// look up the color value in the color table
				// convert pixel from RGB 888 to RGB 565
				rgb565 |= ctBuffer[sdbuffer[buffidx]].blue >> 3;
				rgb565 |= (ctBuffer[sdbuffer[buffidx]].green >> 2) << 5;
				rgb565 |= (ctBuffer[sdbuffer[buffidx]].red >> 3) << 11;
				buffidx++;
				break;
#endif
			}

			// clip the image to the display area specified.
			// the result of a clipped image is a rectangle whose
			// lower left corner is the lower left of the image.
			// this means the top portion and the right portion
			// may not be displayed as it is outside of the
			// clipping region.
			if (y0 + i <= y1 && x0 + j <= x1) {
				// write out the 16 bits of color
				TFTLCD::w_data(rgb565 >> 8);
				TFTLCD::w_data(rgb565);
			}
		}
	}
}