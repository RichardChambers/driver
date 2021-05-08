
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

	bmpHeader.bmpColorTableoffset = 14 + 40;  // file header size + DIB bitmap header size.

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

	// perform a check on the bit depth of the file
	// to make sure it is compatible with our settings.
	// if the bit depth is less than 16 we must have
	// a color table which is only compiled into the
	// library if 8, 4, or 1 bit depth is specified.
	// since the size of the color table varies depending
	// on the defines, we also need to make sure that
	// a color table large enough for the image's bit depth
	// is available. otherwise we error out.
	switch (bmpHeader.bmpDepth) {
	case 32:   return false;       // not tested yet so not supported
		break;
	case 24:
		break;
	case 16:   return false;       // not tested yet so not supported
		break;

	// following bit depth checks allow for a smaller bit depth
	// to be supported by a larger bit depth since what matters
	// is the color table size which increases as the bit depth
	// increases. if 8 bit depth is supported then so is 4 bit depth.
	case 1:
#if defined(SUPPORT_1_BIT_DEPTH)
		break;
#endif
		// fall through and check if we support 4 bit depth.
	case 4:
#if defined(SUPPORT_4_BIT_DEPTH)
		break;
#endif
		// fall through and check if we support 8 bit depth.
	case 8:
#if defined(SUPPORT_8_BIT_DEPTH)
		break;
#endif
		// fall through and report false as the default is not supported.
	default: return false;
	}

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

#if defined(SUPPORT_8_BIT_DEPTH) || defined(SUPPORT_4_BIT_DEPTH) || defined(SUPPORT_1_BIT_DEPTH)
//  See http://www.cs.ucc.ie/~gavin/cs1050/the_internet/slides/ch07s01s02.html.htm
static void fetchColorTable(SDFile &bmpFile, uint32_t bmpColorTableoffset, unsigned short  *ctBuffer, unsigned short size)
{
	unsigned short  *ctBufferEnd = ctBuffer + size;

	bmpFile.seek(bmpColorTableoffset);
	for (; ctBuffer < ctBufferEnd; ctBuffer++) {
		unsigned short rgb565 = 0;
		unsigned char buffer[4];
		bmpFile.read(buffer, 4);
		rgb565 |= buffer[0] >> 3;           // blue, 5 bits
		rgb565 |= (buffer[1] >> 2) << 5;    // green, 6 bits,  color hue value
		rgb565 |= (buffer[2] >> 3) << 11;   // red, 5 bits, color intensity value
											// ignore the fourth byte of the set.
		*ctBuffer = rgb565;
	}
}
#endif

#if defined(SUPPORT_8_BIT_DEPTH) || defined(SUPPORT_4_BIT_DEPTH) || defined(SUPPORT_1_BIT_DEPTH)
#if defined(SUPPORT_8_BIT_DEPTH)
// if supporting both 8 bit depth and 4 bit depth then we need
// a color table large enought for either one.
// if supporting only 4 bit depth then we can save memory and
// use a table sized for 4 bit depth.
static unsigned short ctBuffer[256] = { 0 };
#else
#if defined(SUPPORT_4_BIT_DEPTH)
static unsigned short ctBuffer[16] = { 0 };
#else
static unsigned short ctBuffer[2] = { 0 };
#endif
#endif
#endif

static void KeDei_SD::bmpdraw(SDFile &bmpFile, BMP_Header &bmpHeader, unsigned short x0, unsigned short y0, unsigned short x1, unsigned short y1) {

#if defined(SUPPORT_8_BIT_DEPTH)
	if (bmpHeader.bmpDepth == 8) fetchColorTable(bmpFile, bmpHeader.bmpColorTableoffset, ctBuffer, 256);
#endif
#if defined(SUPPORT_4_BIT_DEPTH) || defined(SUPPORT_8_BIT_DEPTH)
	if (bmpHeader.bmpDepth == 4) fetchColorTable(bmpFile, bmpHeader.bmpColorTableoffset, ctBuffer, 16);
#endif
#if defined(SUPPORT_1_BIT_DEPTH) || defined(SUPPORT_4_BIT_DEPTH) || defined(SUPPORT_8_BIT_DEPTH)
	if (bmpHeader.bmpDepth == 1) fetchColorTable(bmpFile, bmpHeader.bmpColorTableoffset, ctBuffer, 2);
#endif

	bmpFile.seek(bmpHeader.bmpImageoffset);

	// image file read buffer. needs to be large enough to read
	// the number of bytes in the file which represents a pixel.
	// the number of bytes per pixel differs depending on the
	// bit depth of the image. the largest is RGB32A, 32 bit
	// RGB with an alpha channel which requires 4 bytes per pixel.
	static const unsigned short BuffPixel = 12;
	uint8_t sdbuffer[4 * BuffPixel];
	uint8_t buffidx = 8 * BuffPixel;

	TFTLCD::set_area(x0, y0, x1, y1);
	for (int i = 0; i < bmpHeader.bmpHeight; i++) {
		for (int j = 0; j < bmpHeader.bmpWidth; j++) {
			unsigned short rgb565 = 0;

			switch (bmpHeader.bmpDepth) {
#if 0
		// this code is removed for now as it has not been tested
			case 32:
				// The 32-bit per pixel (32bpp) format supports 4,294,967,296 distinct
				// colors and stores 1 pixel per 4-byte DWORD. Each DWORD can define the
				// alpha, red, green and blue samples of the pixel.
				// read more pixels. in triplets since 32 bit color is 1 pixel per 4 bytes
				if (buffidx >= 4 * BuffPixel) {
					bmpFile.read(sdbuffer, 4 * BuffPixel);
					buffidx = 0;
				}
				// convert pixel from RGB 888 to RGB 565
				rgb565 = sdbuffer[buffidx++] >> 3;          // blue, 5 bits
				rgb565 |= (sdbuffer[buffidx++] >> 2) << 5;   // green, 6 bits
				rgb565 |= (sdbuffer[buffidx++] >> 3) << 11;  // red, 5 bits
				buffidx++;             // ignore the alpha channel
				break;
#endif
			case 24:
				// read more pixels. in triplets since 24 bit color is 1 pixel per 3 bytes
				if (buffidx >= 3 * BuffPixel) {
					bmpFile.read(sdbuffer, 3 * BuffPixel);
					buffidx = 0;
				}
				// convert pixel from RGB 888 to RGB 565
				rgb565 = sdbuffer[buffidx++] >> 3;          // blue, 5 bits
				rgb565 |= (sdbuffer[buffidx++] >> 2) << 5;   // green, 6 bits
				rgb565 |= (sdbuffer[buffidx++] >> 3) << 11;  // red, 5 bits
				break;
#if 0
		// this code is removed for now as it has not been tested
			case 16:
				// The 16-bit per pixel (16bpp) format supports 65536 distinct colors
				// and stores 1 pixel per 2-byte WORD. Each WORD can define the alpha,
				// red, green and blue samples of the pixel.
				// read more pixels. in pairs since 16 bit color is 1 pixel per 2 bytes
				if (buffidx >= 2 * BuffPixel) {
					bmpFile.read(sdbuffer, 2 * BuffPixel);
					buffidx = 0;
				}
				// convert pixel from RGB 888 to RGB 565
				rgb565 = (sdbuffer[buffidx] & 0x0f);           // blue, 5 bits
				rgb565 |= (sdbuffer[buffidx++] >> 4) << 5;     // green, 6 bits
				rgb565 |= (sdbuffer[buffidx++] & 0x0f) << 11;  // red, 5 bits
				                                               // alpha channel is ignored
				break;
#endif
#if defined(SUPPORT_1_BIT_DEPTH) || defined(SUPPORT_4_BIT_DEPTH) || defined(SUPPORT_8_BIT_DEPTH)
			case 1:
				// The 1 - bit per pixel(1bpp) format supports 2 distinct colors,
				// (for example: black and white).The pixel values are stored in
				// each bit, with the first(left - most) pixel in the most - significant
				// bit of the first byte.[5] Each bit is an index into a table of
				// 2 colors.An unset bit will refer to the first color table entry,
				// and a set bit will refer to the last(second) color table entry.
				// read more pixels
				if (buffidx >= 8 * BuffPixel) {
					bmpFile.read(sdbuffer, 1 * BuffPixel);
					buffidx = 0;
				}

				// look up the color value in the color table
				// convert pixel from RGB 888 to RGB 565
				rgb565 = ctBuffer[(sdbuffer[buffidx >> 3 ] >> (7 - buffidx % 8)) & 1];
				buffidx++;
				break;
#endif
#if defined(SUPPORT_4_BIT_DEPTH) || defined(SUPPORT_8_BIT_DEPTH)
			case 4:
				// The 4-bit per pixel (4bpp) format supports 16 distinct colors
				// and stores 2 pixels per 1 byte, the left-most pixel being in the
				// more significant nibble.[5] Each pixel value is a 4-bit index
				// into a table of up to 16 colors.
				// read more pixels
				if (buffidx >= 2 * BuffPixel) {
					bmpFile.read(sdbuffer, 1 * BuffPixel);
					buffidx = 0;
				}

				// look up the color value in the color table
				// convert pixel from RGB 888 to RGB 565
				if (buffidx & 1) {
					// odd numbered pixels are in lower part of byte
					rgb565 = ctBuffer[sdbuffer[buffidx >> 1] & 0x0f];
				}
				else {
					// even numbered pixels are in upper part of byte
					rgb565 = ctBuffer[sdbuffer[buffidx >> 1] >> 4];
				}
				buffidx++;
				break;
#endif
#if defined(SUPPORT_8_BIT_DEPTH)
			case 8:
				// The 8-bit per pixel (8bpp) format supports 256 distinct colors
				// and stores 1 pixel per 1 byte. Each byte is an index into a table
				// of up to 256 colors.
				// read more pixels
				if (buffidx >= 1 * BuffPixel) {
					bmpFile.read(sdbuffer, 1 * BuffPixel);
					buffidx = 0;
				}

				// look up the color value in the color table
				// convert pixel from RGB 888 to RGB 565
				rgb565 = ctBuffer[sdbuffer[buffidx]];
				buffidx++;
				break;
#endif
			}

			// clip the image to the display area specified.
			// the result of a clipped image is a rectangle whose
			// lower left corner is the lower left of the image.
			// this means the top portion and the right portion
			// may not be displayed if it is outside of the
			// clipping region.
			if (y0 + i <= y1 && x0 + j <= x1) {
				// write out the 16 bits of color
					TFTLCD::w_data(rgb565 >> 8);
					TFTLCD::w_data(rgb565);
			}
		}
	}
}