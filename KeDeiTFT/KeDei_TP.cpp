/*
welcome use KeDeiTFT
*/
#include	"KeDei_TP.h"

static unsigned short 	TP::x = 0;     // screen row or x coordinate of touch position
static unsigned short 	TP::y = 0;     // screen column or y coordinate of touch position
static bool	TP::flag = false;          // if true then valid touch event with touch position available.
static bool	TP::x_val = false;
static bool	TP::y_val = false;

/*****************************************
 *The function name ： get_xy
 *Function  ： 获取触摸的坐标
 *Input  ： none
 *Output   ： none
 *Author   ： KeDei
 *Time   ：2015/4/21
 ****************************************/
static void TP::get_xy(void)
{
	// indicate we have a touch event.
	// when we process the actual raw touch data values
	// we will test whether each of the coordinates is
	// possibly not valid with flas x_val and y_val.
	flag = true;

#ifdef  __AVR_ATmega328P__
	DDRC|=2;
	PORTC|=2;
	DDRD|=0X20;
	PORTB&=0XDF;
	DDRD&=0XBF;
	DDRC&=0XFB;

#else
#endif
	// following variables are used in reading and processing
	// the touch screen coordinates from a touch event.
	long tp_max;
	long tp_min;
	long tp_temp;
	long temp_xy;

	// calculate the x coordinate of the touch position.
	//
	// query the touch position reported by the display
	// multiple times so that we can then average the
	// reported values and use that average value in our
	// touch position calculations. we keep a copy of the
	// maximum and minimum values because the average calculation
	// will throw away the highest and lowest value and then
	// calculate the mean from the remaining values.
	tp_max = analogRead(YP);
	tp_min = tp_max;
	tp_temp = 0;
	for(unsigned char tp_i = 0; tp_i < 12; tp_i++)
	{
		temp_xy = analogRead(YP);
		if(temp_xy > tp_max) tp_max = temp_xy;
		if(temp_xy < tp_min) tp_min = temp_xy;
		tp_temp += temp_xy;
	}

#if 0
	// debug output when troubleshooting incorrect
	// touch position coordinates.
	Serial.print("  TFTLCD::MODULE = ");
	Serial.println(TFTLCD::MODULE);

	Serial.print("x  tp_max = ");
	Serial.print(tp_max);
	Serial.print("  tp_min = ");
	Serial.print(tp_min);
	Serial.print("  tp_temp = ");
	Serial.println(tp_temp);
#endif

	// check that the distance between maximum and minimum
	// values is sufficiently small and the raw data value
	// we will use in our touch position calculation is
	// reasonable.
	x_val = ((tp_max - tp_min) < 50);

	// create an average by throwing out the largest and smallest
	// values read and then divide by the count of the remaining values.
	// use this average raw data value in the calculation for turning
	// the raw data value into a touch position coordinate.
	tp_temp = (tp_temp - tp_max - tp_min) / 10;
	if(TFTLCD::MODULE == _MODULE_1_)
	{
#ifdef  ROTATE_0
		x = (tp_temp - 104) * 24 / 73;
#endif
	}
	else
	{
		x = (tp_temp - 109) * 32 / 74;
	}

#if 0
	// debug output when troubleshooting incorrect
	// touch position coordinates.
	Serial.print("  x = ");
	Serial.print(x);
	Serial.print("  tp_max = ");
	Serial.print(tp_max);
	Serial.print("  tp_min = ");
	Serial.print(tp_min);
	Serial.print("  tp_temp = ");
	Serial.println(tp_temp);
#endif

#ifdef  __AVR_ATmega328P__	
	DDRC|=4;
	PORTC|=4;
	DDRD|=0X40;
	PORTD&=0XBF;
	DDRD&=0XDF;
	DDRC&=0XFD;

#else
#endif
	
	// now query for the y coordinate and do the same
	// processing we did for the x coordinate up above.
	// see those comments for an explanation.

	tp_max = analogRead(XP);
	tp_min = tp_max;
	tp_temp = 0;
	for(unsigned char tp_i = 0; tp_i < 12; tp_i++)
	{
		temp_xy = analogRead(XP);
		if(temp_xy > tp_max) tp_max = temp_xy;
		if(temp_xy < tp_min) tp_min = temp_xy;
		tp_temp += temp_xy;
	}

#if 0
	// debug output when troubleshooting incorrect
	// touch position coordinates.
	Serial.print("y  tp_max = ");
	Serial.print(tp_max);
	Serial.print("  tp_min = ");
	Serial.print(tp_min);
	Serial.print("  tp_temp = ");
	Serial.println(tp_temp);
#endif

	// check that the distance between maximum and minimum
	// values is sufficiently small and the raw data value
	// we will use in our touch position calculation is
	// reasonable.
	y_val = ((tp_max - tp_min) < 50);

	tp_temp = (tp_temp - tp_max - tp_min) / 10;
	if(TFTLCD::MODULE == _MODULE_1_)
	{
#ifdef  ROTATE_0
		y = (tp_temp - 70) * 32 / 75;
#endif
	}
	else
	{
		y = (tp_temp - 73) * 48 / 78;
	}

#if 0
	// debug output when troubleshooting incorrect
	// touch position coordinates.
	Serial.print("  y = ");
	Serial.print(y);
	Serial.print("  tp_max = ");
	Serial.print(tp_max);
	Serial.print("  tp_min = ");
	Serial.print(tp_min);
	Serial.print("  tp_temp = ");
	Serial.println(tp_temp);
#endif
}


/*****************************************
 *The function name ： pen_down
 *Function  ： 检测当前触摸的状态
 *Input  ： none
 *Output   ： none
 *Author   ： KeDei
 *Time   ：2015/4/21
 ****************************************/
static bool TP::pen_down()
{
	pinMode(XP,INPUT_PULLUP);
	pinMode(XM,INPUT);
//	DDRB&=0XFE;
	pinMode(YP, INPUT);
//	DDRC&=0XFD;

	pinMode(YM,OUTPUT);
//	DDRB|=2;
	digitalWrite(YM,LOW);
	digitalWrite(YP,LOW);
//	PORTB&=0XFD;
//	delay(1);

	// initialize the various flags to false and then
	// let get_xy(), if it is called, do the honors of
	// setting them appropriately.
	flag = false;      // no touch coordinates available
	y_val = false;     // x coordinate of touch position is invalid
	x_val = false;     // y coordinate of touch position is invalid
	x = y = 0;         // initialize the coordinates to a known value.
	analogRead(XP);    // read the y coordinate line and discard allow the line to settle to a known state
	if (200 > analogRead(XP))
	{
		// sufficient signal on the pin to indicate touch event so lets
		// process it by reading both x and y pins and generating a touch position.
		get_xy();
	}

//	DDRB|=3;
//	DDRC|=6;

	pinMode(XP,OUTPUT);
	pinMode(XM,OUTPUT);
	pinMode(YP,OUTPUT);

	return flag;
}
