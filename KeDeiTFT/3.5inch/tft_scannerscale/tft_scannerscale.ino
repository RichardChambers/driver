
#include <KeDei_TFT.h>
#include <KeDei_TP.h>
#include "KeDei_font.h"
#include "KeDei_button.h"


// following define turns on the Serial debug output
// when testing with the Arduino IDE.
// for production this should be commented out.
//#define USE_SERIAL

#define backcolor 0xf800

#if 0
static const unsigned char font_table_local[59][8] = {
  { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },   // U+0020 (space)
  { 0x18, 0x3C, 0x3C, 0x18, 0x18, 0x00, 0x18, 0x00 },   // U+0021 (!)
  { 0x36, 0x36, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },   // U+0022 (")
  { 0x36, 0x36, 0x7F, 0x36, 0x7F, 0x36, 0x36, 0x00 },   // U+0023 (#)
  { 0x0C, 0x3E, 0x03, 0x1E, 0x30, 0x1F, 0x0C, 0x00 },   // U+0024 ($)
  { 0x00, 0x63, 0x33, 0x18, 0x0C, 0x66, 0x63, 0x00 },   // U+0025 (%)
  { 0x1C, 0x36, 0x1C, 0x6E, 0x3B, 0x33, 0x6E, 0x00 },   // U+0026 (&)
  { 0x06, 0x06, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00 },   // U+0027 (')
  { 0x18, 0x0C, 0x06, 0x06, 0x06, 0x0C, 0x18, 0x00 },   // U+0028 (()
  { 0x06, 0x0C, 0x18, 0x18, 0x18, 0x0C, 0x06, 0x00 },   // U+0029 ())
  { 0x00, 0x66, 0x3C, 0xFF, 0x3C, 0x66, 0x00, 0x00 },   // U+002A (*)
  { 0x00, 0x0C, 0x0C, 0x3F, 0x0C, 0x0C, 0x00, 0x00 },   // U+002B (+)
  { 0x00, 0x00, 0x00, 0x00, 0x00, 0x0C, 0x0C, 0x06 },   // U+002C (,)
  { 0x00, 0x00, 0x00, 0x3F, 0x00, 0x00, 0x00, 0x00 },   // U+002D (-)
  { 0x00, 0x00, 0x00, 0x00, 0x00, 0x0C, 0x0C, 0x00 },   // U+002E (.)
  { 0x60, 0x30, 0x18, 0x0C, 0x06, 0x03, 0x01, 0x00 },   // U+002F (/)
  { 0x3E, 0x63, 0x73, 0x7B, 0x6F, 0x67, 0x3E, 0x00 },   // U+0030 (0)
  { 0x0C, 0x0E, 0x0C, 0x0C, 0x0C, 0x0C, 0x3F, 0x00 },   // U+0031 (1)
  { 0x1E, 0x33, 0x30, 0x1C, 0x06, 0x33, 0x3F, 0x00 },   // U+0032 (2)
  { 0x1E, 0x33, 0x30, 0x1C, 0x30, 0x33, 0x1E, 0x00 },   // U+0033 (3)
  { 0x38, 0x3C, 0x36, 0x33, 0x7F, 0x30, 0x78, 0x00 },   // U+0034 (4)
  { 0x3F, 0x03, 0x1F, 0x30, 0x30, 0x33, 0x1E, 0x00 },   // U+0035 (5)
  { 0x1C, 0x06, 0x03, 0x1F, 0x33, 0x33, 0x1E, 0x00 },   // U+0036 (6)
  { 0x3F, 0x33, 0x30, 0x18, 0x0C, 0x0C, 0x0C, 0x00 },   // U+0037 (7)
  { 0x1E, 0x33, 0x33, 0x1E, 0x33, 0x33, 0x1E, 0x00 },   // U+0038 (8)
  { 0x1E, 0x33, 0x33, 0x3E, 0x30, 0x18, 0x0E, 0x00 },   // U+0039 (9)
  { 0x00, 0x0C, 0x0C, 0x00, 0x00, 0x0C, 0x0C, 0x00 },   // U+003A (:)
  { 0x00, 0x0C, 0x0C, 0x00, 0x00, 0x0C, 0x0C, 0x06 },   // U+003B (;)
  { 0x18, 0x0C, 0x06, 0x03, 0x06, 0x0C, 0x18, 0x00 },   // U+003C (<)
  { 0x00, 0x00, 0x3F, 0x00, 0x00, 0x3F, 0x00, 0x00 },   // U+003D (=)
  { 0x06, 0x0C, 0x18, 0x30, 0x18, 0x0C, 0x06, 0x00 },   // U+003E (>)
  { 0x1E, 0x33, 0x30, 0x18, 0x0C, 0x00, 0x0C, 0x00 },   // U+003F (?)
  { 0x3E, 0x63, 0x7B, 0x7B, 0x7B, 0x03, 0x1E, 0x00 },   // U+0040 (@)
  { 0x0C, 0x1E, 0x33, 0x33, 0x3F, 0x33, 0x33, 0x00 },   // U+0041 (A)
  { 0x3F, 0x66, 0x66, 0x3E, 0x66, 0x66, 0x3F, 0x00 },   // U+0042 (B)
  { 0x3C, 0x66, 0x03, 0x03, 0x03, 0x66, 0x3C, 0x00 },   // U+0043 (C)
  { 0x1F, 0x36, 0x66, 0x66, 0x66, 0x36, 0x1F, 0x00 },   // U+0044 (D)
  { 0x7F, 0x46, 0x16, 0x1E, 0x16, 0x46, 0x7F, 0x00 },   // U+0045 (E)
  { 0x7F, 0x46, 0x16, 0x1E, 0x16, 0x06, 0x0F, 0x00 },   // U+0046 (F)
  { 0x3C, 0x66, 0x03, 0x03, 0x73, 0x66, 0x7C, 0x00 },   // U+0047 (G)
  { 0x33, 0x33, 0x33, 0x3F, 0x33, 0x33, 0x33, 0x00 },   // U+0048 (H)
  { 0x1E, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0x1E, 0x00 },   // U+0049 (I)
  { 0x78, 0x30, 0x30, 0x30, 0x33, 0x33, 0x1E, 0x00 },   // U+004A (J)
  { 0x67, 0x66, 0x36, 0x1E, 0x36, 0x66, 0x67, 0x00 },   // U+004B (K)
  { 0x0F, 0x06, 0x06, 0x06, 0x46, 0x66, 0x7F, 0x00 },   // U+004C (L)
  { 0x63, 0x77, 0x7F, 0x7F, 0x6B, 0x63, 0x63, 0x00 },   // U+004D (M)
  { 0x63, 0x67, 0x6F, 0x7B, 0x73, 0x63, 0x63, 0x00 },   // U+004E (N)
  { 0x1C, 0x36, 0x63, 0x63, 0x63, 0x36, 0x1C, 0x00 },   // U+004F (O)
  { 0x3F, 0x66, 0x66, 0x3E, 0x06, 0x06, 0x0F, 0x00 },   // U+0050 (P)
  { 0x1E, 0x33, 0x33, 0x33, 0x3B, 0x1E, 0x38, 0x00 },   // U+0051 (Q)
  { 0x3F, 0x66, 0x66, 0x3E, 0x36, 0x66, 0x67, 0x00 },   // U+0052 (R)
  { 0x1E, 0x33, 0x07, 0x0E, 0x38, 0x33, 0x1E, 0x00 },   // U+0053 (S)
  { 0x3F, 0x2D, 0x0C, 0x0C, 0x0C, 0x0C, 0x1E, 0x00 },   // U+0054 (T)
  { 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x3F, 0x00 },   // U+0055 (U)
  { 0x33, 0x33, 0x33, 0x33, 0x33, 0x1E, 0x0C, 0x00 },   // U+0056 (V)
  { 0x63, 0x63, 0x63, 0x6B, 0x7F, 0x77, 0x63, 0x00 },   // U+0057 (W)
  { 0x63, 0x63, 0x36, 0x1C, 0x1C, 0x36, 0x63, 0x00 },   // U+0058 (X)
  { 0x33, 0x33, 0x33, 0x1E, 0x0C, 0x0C, 0x1E, 0x00 },   // U+0059 (Y)
  { 0x7F, 0x63, 0x31, 0x18, 0x4C, 0x66, 0x7F, 0x00 }   // U+005A (Z)
};
#endif

// Set up our TFT LCD display objects so that we can display
// information on the LCD display screen and to also accept
// changes to the current settings for weight and for the current
// bar code to be sent when the scanButton is pressed.
//
// Create a keypad object on the display screen to allow entry of
// an amount of weight.

Font  font1;        //Font class object for upper text region
Font  font2;        //Font class object for buttons
Font  font3;        //Font class object for lower text region

static const TFTLCD::TftColor bgColorTop = TFTLCD::RGB_TO_565(60,150,70);
static const TFTLCD::TftColor bgColorBottom = TFTLCD::RGB_TO_565(60,150,100);

Button  scanButton;      // button to trigger sending current bar code as a scanner message

// using shared buttons for the data change part of the UI as these can be
// the same font and colors and such.
ButtonData    weightData;
ButtonShared  weightButton[4](weightData); // buttons to change the weight setting. first pair to increment/decrement by one unit, second by .1 unit.

TFTLCD::TftPos weightPos;

ButtonShared statusButton[4](weightData);  // buttons to change the status bytes. buttons toggle the setting. once to turn on, again to turn off.

char cBuff[48] = {0};


// table of scanner data. this determines values returned in a scan response.
// the symChar indicates the symbology used for the barcode
//   - A   UPC-A, length 12
//   - E   UPC-E, length 7
//   - FF  JAN-8, EAN-8, length 9
//   - F   Jan-13, EAN-13, length 13
//   - B1  Code 39
//   - B2  Interleaved 2 of 5
//   - B3  Code 128
//   - ]e0 RSS-14

struct ScannerData {
  char symChar[4];      // string representing symbology such as 'A' for UPC-A
  char barcode[16];     // string of digits from the barcode
};

const ScannerData pluList[] = {
  {"A", "070177155766"},          //    Twinings English Afternoon tea 20 bags
  {"A", "070177154240"},          //    Twinings Irish Breakfast tea 20 bags
  {"A", "070177154127"},          //    Twinings Darjeeling tea 20 bags
  {"A", "072310001893"},          //    Bigelow Plantation Mint tea 20 bags
  {"A", "747599303142"},          //    Ghirardelli Squares Dark Chocolate Sea Caramel
  {"E", "1215704"}                //    Aquafina bottled water 1L

#if 0
  {"A", "070177155766"},          //    Twinings English Afternoon tea 20 bags
  {"A", "070177154240"},          //    Twinings Irish Breakfast tea 20 bags
  {"A", "070177154127"},          //    Twinings Darjeeling tea 20 bags
  {"A", "072310001893"},          //    Bigelow Plantation Mint tea 20 bags
  {"A", "072310001978"},          //    Bigelow Lemon Lift tea 20 bags
  {"A", "072310001053"},          //    Bigelow Constant Comment tea 20 bags
  {"A", "747599303142"},          //    Ghirardelli Squares Dark Chocolate Sea Caramel
  {"A", "046677426002"},          //    4 pack Philips EcoVantage Soft White 40w A19 bulbs
  {"A", "046677426040"},          //    4 pack Philips Soft White 100w A19 bulbs
  {"A", "086854005682"},          //    5.75 oz bottle Laura Lynn Manzanilla Olives with minced pimiento
  {"A", "086854043622"},          //    8.5 oz bottle Laura Lynn extra virgin olive oil
  {"A", "086854042311"},          //    14.5 oz can Laura Lynn diced tomatoes no salt added
  {"A", "041443113421"},          //    14.5 oz can Margaret Holmes Italian Green Beans
  {"A", "039400017066"},          //    16 oz can Bush's Reduced Sodium Garbanzos chick peas
  {"A", "052000011227"},          //    15 oz can Van Camp's Pork and Beans in tomato sauce
  {"A", "029000076501"},          //    16 oz Planters Dry Roasted Peanuts Lightly salted
  {"A", "037000388517"},          //    Charmin Ultra Soft toilet tissue 6 roll Super Mega
  {"A", "037000527787"},          //    Charmin Ultra Soft toilet tissue 6 roll Mega
  {"A", "201404309526"},          //    container of beef loin 1.59lbs @ $5.99 (PLU, 01404 with price $9.52)
  {"A", "200065109001"},          //    container London Broil 2.44lbs @ $3.69 (PLU, 00065 with price $9.00)
  {"A", "206141306005"},          //    container deli lunch $6.00
  {"A", "681131161565"},          //    12 oz bag organic broccoli florets
  {"A", "681131160599"},          //    12 oz bag organic green beans
  {"A", "033363200107"},          //    8 oz carton baby bella mushrooms
  {"A", "881979000112"},          //    #4081 eggplant, scalable
  {"E", "1215704"}                //    Aquafina bottled water 1L
#endif
};


// scale measurement data. this determines values returned in a weight response.

static const unsigned char UIE_SCALE_IN_MOTION =0x01;   /* status byte 1 scale in motion       */
static const unsigned char UIE_SCALE_ZERO=0x02;         /* zstatus byte 1 ero weight           */
static const unsigned char UIE_SCALE_UNDER=0x01;        /* status byte 2 under capacity        */
static const unsigned char UIE_SCALE_OVER=0x02;         /* status byte 2 over capacity         */

int   lb1 = 0, lb2 = 250;    // most significant and least signicant parts of weight.
unsigned char s1 = 0x30, s2 = 0x30;   // status byte 1 and status byte 2

enum  ScaleUnits {English, Metric};
ScaleUnits   iUnits = English;

unsigned short usNotOnFileCounter = 0;    // if not zero then do Not On File tone countdown.

enum DeviceSim { Device78xxScannerOnly = 0, Device78xxScannerScale = 1, Device78xxScannerScaleBCC= 2, Device7852Scanner=3};
DeviceSim  deviceInUse = Device78xxScannerScale;
enum SpecInUse { Scp_01 = 0, Scp_02 = 1};
SpecInUse  specInUse = Scp_02;

struct {
  char *specScan;
  char *specStatus;
  bool  bSendBcc;
} specInUseFmtScanner [] = {
      //weight then units then status
      { "38%s%s\x03", "130%c%c\x03", false},     // NCR 78xx without BCC appended to message
      { "08%s%s\x03%2.2x", "130%c%c\x03", true}  // NCR 78xx with BCC appended to message
};

struct {
  char *specWeight;
  char *specStatus;
  short maxMsp;
  short maxLsp;
} specInUseFmtScale [] = {
      //weight then units then status
      { "\n%4.4d.%2.2d%s\r\n%c%c\r\x03", "\n%c%c\r\x03", 4, 2},    // SCP-01 specification for response
      { "\n%2.2d.%3.3d%s\r\nS%c%c\r\x03", "\nS%c%c\r\x03", 2, 3 }  // SCP-02 specification for response
};

const char * emptyLine = "\n";
const char * unknownResponse = "\n?\r\x03";

// calculate the BCC or Block Check Character which is a
// checksum on the message to send. It is added to the
// message after the ETX character in the message.
// See https://en.wikipedia.org/wiki/Binary_Synchronous_Communications
//
unsigned char ScannerScaleCalcBCC(unsigned char *puchData, short sLength)
{
    unsigned char   uchBCC = 0;
    short   sIndex;

    for (sIndex = 0; sIndex < sLength; sIndex++) {
        uchBCC ^= *(puchData + sIndex);
    }

    return (uchBCC);
}

char * handle78xxScannerOnly (const String &inCommand, char *cBuff)
{
  switch(inCommand[1]) {
    case 0x30:    // enable command
      // 78xx scanner only: "\x32\x30\x03"
      break;
    case 0x36:    // status command
      // 78xx scanner only: "\x30\x36\x03"
    case 0x33:    // status command
      // 78xx scanner only: "\x30\x33\x03"
      break;
    case 0x42:    // disable command
      // 78xx scanner only: "\x32\x42\x03"
      break;
    case 0x46:    // not on file command
      // 78xx scanner only: "\x33\x46\x03"
      // issue the Not On File indicator tone 
      usNotOnFileCounter = 10;
      break;
  }
  
  if (deviceInUse == Device78xxScannerOnly)
    sprintf (cBuff, specInUseFmtScanner[0].specStatus, s1, s2);
//  else
//    sprintf (cBuff, emptyLine);
    
  return cBuff;
}


char * handle78xxScannerScale (const String &inCommand, char *cBuff)
{
  switch(inCommand[1]) {
    case 0x31:    // enable command
      // 78xx scanner/scale w/o BCC: "\x30\x31\x03"
      // 78xx scanner/scale w/  BCC: "\x30\x31\x03\x02"
      break;
    case 0x33:    // status command
      // 78xx scanner/scale w/o BCC: "\x30\x33\x03"
      // 78xx scanner/scale w/  BCC: "\x30\x33\x03\x00"
      break;
    case 0x35:    // not on file command
      // 78xx scanner/scale w/o BCC: "\x30\x35\x03"
      // 78xx scanner/scale w/  BCC: "\x30\x35\x03\x06"
      // issue the Not On File indicator tone 
      usNotOnFileCounter = 10;
      break;
    case 0x36:    // disable command
      // 78xx scanner/scale w/o BCC: "\x30\x36\x03"
      // 78xx scanner/scale w/  BCC: "\x30\x36\x03\x05"
      break;
  }
  
  if (deviceInUse == Device78xxScannerScale)
    sprintf (cBuff, specInUseFmtScanner[0].specStatus, s1, s2);
//  else
//    sprintf (cBuff, emptyLine);
    
  return cBuff;
}

void handle_command(const String &inCommand) {
  
    cBuff[0] = 0;
    
#if defined(USE_SERIAL)
    Serial.println(inCommand);
#endif
    switch (inCommand[0]) {
      case 0x31:    // status command
#if defined(USE_SERIAL)
        Serial.println("0x31 command");
#endif
        if (inCommand[1] == 0x33) {
          sprintf (cBuff, specInUseFmtScanner[0].specStatus, s1, s2);
        } else {
          sprintf (cBuff, specInUseFmtScanner[0].specScan, pluList[0].symChar, pluList[0].barcode);
        }
        break;
 
      case 0x30:    // 78xx scanner/scale
#if defined(USE_SERIAL)
        Serial.println("0x30 command");
#endif
        handle78xxScannerScale (inCommand, cBuff);
        break;
        
      case 0x32:    // 78xx scanner only
      case 0x33:    // 78xx scanner only
#if defined(USE_SERIAL)
        Serial.println("0x33 command");
#endif
        handle78xxScannerOnly (inCommand, cBuff);
        break;
        
      case 0x46:    // status command
#if defined(USE_SERIAL)
        Serial.println("0x46 command");
#endif
          // 7852 scanner: "\x46\x36\x03"
        if (inCommand[1] == 0x36)
          sprintf (cBuff, specInUseFmtScanner[0].specStatus, s1, s2);
        break;
        
      case 'W':    // weight command
      case 'w':
        {
          if (iUnits == English)
            sprintf (cBuff, specInUseFmtScale[specInUse].specWeight, lb1, lb2, "LB", s1, s2);
          else
            sprintf (cBuff, specInUseFmtScale[specInUse].specWeight, lb1, lb2, "KG", s1, s2);
        }
        break;
      case 'S':    // status command
      case 's':
        sprintf (cBuff, specInUseFmtScale[specInUse].specStatus, s1, s2);
        break;
      default:     // unrecognized command
        sprintf (cBuff, unknownResponse);
        break;
    }
    
    if (cBuff[0] == 0) sprintf (cBuff, unknownResponse);

    Serial.print(cBuff);
#if defined(USE_SERIAL)
    Serial.println("");
#endif
}

void setup() {
  
  // put your setup code here, to run on`ce:
  Serial.begin(9600); // Turn the serial protocol ON

  delay (1000);

  //TFT initialization and font initialization
   TFTLCD::begin();
   
   // create a background RGB565 color which we are going to use
   // for the background color for the screen as a whole as well as
   // for the text region we are going to create. by using the same
   // background color we can just over print text and the background
   // color will overwrite what ever is there.
 
   TFTLCD::clear(bgColorTop);

   // Font::FontTable::Flags_DoubleHigh | 
   // Font::FontTable::Flags_DoubleWide | 
//   Font::set_fonttable(59, 8, (unsigned char *)font_table_local, Font::FontTable::Flags_UpperOnly);
   
   // Set the text area for the upper left corner (30, 10), the lower right corner (320,200).
   // Set the font color to red blue and use the same background color as for the display.
   // Our text region is the upper half of the screen.
   font1.set_fontcolor(TFTLCD::RGB_TO_565(100,0,100));
   font1.set_txt(2, 5, TFTLCD::x_all, TFTLCD::y_all / 2, bgColorTop);
   
   //Displays a string
   font1.setFontFlags(Font::FontTable::Flags_DoubleWide | Font::FontTable::Flags_DoubleHigh | Font::FontTable::Flags_NoLineFeed);
   font1.lcd_string("Scanner Scale");

   font1.setFontFlags(Font::FontTable::Flags_DoubleHigh | Font::FontTable::Flags_WrapLine);
   font1.lcd_string ("\n");
   TFTLCD::TftPos p0 = font1.getFontPos();
   font1.lcd_string ("Scanner\n");
   //Draw the first round button1
   font2.setFontFlags(Font::FontTable::Flags_DoubleHigh);
    p0.x += 150;
   scanButton.drawButton(p0, 1, "Scan", font2);
   
   font1.lcd_string(" 070177155766\n Twinings English Afternoon tea");

   if (iUnits == English)
      sprintf (cBuff, specInUseFmtScale[specInUse].specWeight, lb1, lb2, "LB", s1, s2);
    else
      sprintf (cBuff, specInUseFmtScale[specInUse].specWeight, lb1, lb2, "KG", s1, s2);

    font1.lcd_string ("\nScale");
    weightPos = font1.getFontPos();
    font1.lcd_string(cBuff);

   // UI on Bottom half of screen
   font3.set_fontcolor(TFTLCD::RGB_TO_565(100,0,100));
   font3.set_txt(0, TFTLCD::y_all / 2, TFTLCD::x_all, TFTLCD::y_all, bgColorBottom);

   p0.setPos(5, TFTLCD::y_all / 2 + 10);
   font3.setFontPos(p0);
   font3.lcd_string("Weight");
   p0.setPos(100, p0.y);
   weightButton[0].drawButton (p0, 1, "- 1.0", font2);
   p0.movePos(100, 0);
   weightButton[2].drawButton (p0, 1, "- 0.1", font2);
   p0.setPos(100, p0.movePos(0, 60).y);
   weightButton[1].drawButton (p0, 1, "+ 1.0", font2);
   p0.movePos(100, 0);
   weightButton[3].drawButton (p0, 1, "+ 0.1", font2);

   // status byte modification controls go down below the weight modification controls.
   // just as for weight we have a label with the set of controls following.
   p0.setPos(5, p0.movePos(0, 60).y);
   font3.setFontPos(p0);
   font3.lcd_string("Status");
   p0.setPos(100, p0.y);
   TFTLCD::h_line (p0.x - 20, p0.y - 10, 200, font3.get_fontcolor());
   statusButton[0].drawButton (p0, 1, "UC", font2);
   p0.movePos(100, 0);
   statusButton[1].drawButton (p0, 1, "OC", font2);
   
   p0.setPos(100, p0.movePos(0, 60).y);
   statusButton[2].drawButton (p0, 1, "IM", font2);
   p0.movePos(100, 0);
   statusButton[3].drawButton (p0, 1, "SZ", font2);
}

byte incoming;
String inBuffer;

void loop() {

    if (usNotOnFileCounter > 1) {
        if (usNotOnFileCounter > 9) {
          TFTLCD::FillCircle(250, 200, 40, TFTLCD::RGB_TO_565(255,0,0));
        }
        usNotOnFileCounter--;
        delay(50);
    } else if (usNotOnFileCounter > 0) {
        usNotOnFileCounter = 0;
        TFTLCD::FillCircle(250, 200, 40, bgColorTop);
    }

    //check Touch current state detection
    TP::pen_down();
    
    if(TP::flag && TP::y_val && TP::x_val) {
       //The touch screen is touched. Check which button was pressed
       if(scanButton.isTouchState())
        {
          handle_command("11");
          // delay(500);+
          
          //Button to restore the original appearance
          // Clear the string for the next command
          inBuffer = "";
        }

        for (unsigned char i = 0; i < 4; i++) {
            if(weightButton[i].isTouchState())
            {
                switch (i) {
                  case 0:    // - 1.0 button
                      (lb1 > 0) && (lb1 -= 1);
                      break;
                  case 1:    // + 1.0 button
                      (lb1 < 9) && (lb1 += 1);
                      break;
                  case 2:    // - 0.1 button
                      (lb2 > 50) && (lb2 -= 100);
                      break;
                  case 3:    // - 0.1 button
                      (lb2 < 900) && (lb2 += 100);
                      break;
                }
            }
        }
       
        for (unsigned char i = 0; i < 4; i++) {
            if(statusButton[i].isTouchState())
            {
                switch (i) {
                  case 0:    // UC button for Under Capacity
                      s1 ^= UIE_SCALE_UNDER;
                      break;
                  case 1:    // OC button for Over Capacity
                      s1 ^= UIE_SCALE_OVER;
                      break;
                  case 2:    // IM button for scale in motion
                      s2 ^= UIE_SCALE_IN_MOTION;
                      break;
                  case 3:    // SZ button for sale zero
                      s2 ^= UIE_SCALE_ZERO;
                      break;
                }
            }
        }
        font1.setFontPos(weightPos);
        if (iUnits == English)
          sprintf (cBuff, specInUseFmtScale[specInUse].specWeight, lb1, lb2, "LB", s1, s2);
        else
          sprintf (cBuff, specInUseFmtScale[specInUse].specWeight, lb1, lb2, "KG", s1, s2);
        font1.lcd_string(cBuff);
     } else {
        // no touch event pending so clear the pendown() with a call to penup()
        // for each of the buttons displayed.
        scanButton.penup();
        
        weightButton[0].penup();
        weightButton[1].penup();
        weightButton[2].penup();
        weightButton[3].penup();
        
        statusButton[0].penup();
        statusButton[1].penup();
        statusButton[2].penup();
        statusButton[3].penup();
     }
      
     // setup as non-blocking code
     incoming = Serial.read();
     if(incoming < 255) {
         if(incoming == '\n' || incoming == '\r' || incoming == '\x03') {  // newline, carriage return, both, or custom character
            // handle the incoming command
            handle_command(inBuffer);

            // Clear the string for the next command
            inBuffer = "";
        } else{
            // add the character to the buffer
            inBuffer += (char)incoming;
        }
    }
}
