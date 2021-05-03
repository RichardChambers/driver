
#include <SD.h>


// following define adds support for the color table
// needed for 8 bit and 4 bit color depth bitmaps.
// these formats have a color table which requires additional
// storage which may not be realistic for a device such as
// the Arduino.

//#define SUPPORT_8_BIT_DEPTH

class KeDei_SD {
public:
	static const unsigned char GRAY_LEVELS = 255;
	struct ctstruct {
		unsigned char blue;
		unsigned char green;
		unsigned char red;
	};
	// See Wikipedia topic https://en.wikipedia.org/wiki/BMP_file_format
	struct BMP_Header {
		uint32_t bmpFileSize;
		uint32_t bmpImageoffset;        // offset to the bitmap image data
		uint32_t bmpColorTableoffset;   // offset to the color table
		uint32_t bmpWidth;              // bitmap width in pixels
		uint32_t bmpHeight;             // bitmap height in pixels
		uint16_t bmpPlanes;
		uint16_t bmpDepth;              // number of bits per pixel, color depth, typically 1, 4, 8, 16, 24, and 32
		uint32_t bmpCompression;        // compression method used
		uint32_t bmpPaletteCount;       // number of colors in the color palette
	};

	static bool bmpReadHeader(SDFile &bmpFile, BMP_Header &bmpHeader);
	static void bmpdraw(SDFile &bmpFile, BMP_Header &bmpHeader, unsigned short x0, unsigned short y0, unsigned short x1, unsigned short y1);
};