
#include <SD.h>


// following define adds support for the color table
// needed for 8 bit and 4 bit color depth bitmaps.
// these formats have a color table which requires additional
// storage which may not be realistic for a device such as
// the Arduino.
//
// the color table size needed depends on the bit depth of
// the image which in turn determines the number of possible
// colors. bit depth of 1 requires 2 colors while a bit depth
// of 8 requires 256 colors. bit depth of 4 requires 16 colors.
//
// if you define SUPPORT_8_BIT_DEPTH then you automatically get
// support for bit depth 4 and 1 as well since they use the same
// resources. however if you define SUPPORT_4_BIT_DEPTH you will
// get both 4 bit depth and 1 bit depth but not 8 bit depth since
// the color table for 4 bit depth also supports 1 bit depth but
// is not large enough for 8 bit depth.
//
// 16 bit depth and higher, 24 bit depth and 32 bit depth, do not
// use the color table so you get those regardless of the settings
// of the defines below.

//#define SUPPORT_1_BIT_DEPTH      // color table for bit depth 1 created
//#define SUPPORT_4_BIT_DEPTH      // color table for bit depth 4 and 1 created
//#define SUPPORT_8_BIT_DEPTH      // color table for bit depth 8, 4, and 1 created

class KeDei_SD {
public:
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