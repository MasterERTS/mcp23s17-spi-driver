/**
 * @file main.cpp
 * @author Erwin lejeune (erwin.lejeune15@gmail.com)
 * @brief Abstraction layers for a SPI driver
 * @version 0.1
 * @date 2020-01-12
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#include "stm32f3xx.h"
#include "Adafruit_GFX.h"
#include "Adafruit_ST7735.h"
#include "adc.h"

//font definition.
#define PROGMEM
#define FONT_WIDTH 11
#define FONT_HEIGHT 21
#include "tft/Adafruit-GFX-Library/fontconvert/veraMono9.h"
#define FONT_NAME VeraMono9pt7b

#ifdef __cplusplus
 extern "C" {
#endif /* __cplusplus */

#include "mcp.h"

// Adafruit_ST7735 tft = Adafruit_ST7735();
mcp23s17 ioExt;

void wait()
{
	volatile int i=0;
	for(i=0;i<200000;i++);
}

void setup()
{
	/*tft.initR(INITR_BLACKTAB);   // initialize a ST7735S chip, black tab
	tft.setFont(&FONT_NAME);
	tft.fillScreen(ST7735_BLACK);
	tft.setTextColor(ST7735_RED);
	tft.setCursor(10, FONT_HEIGHT);
	tft.print("Hello World! ");*/
	ioExt.begin(); 
	for (int i = 0 ; i < 8 ; i++) ioExt.pinMode(ioExt.PORTA, i, ioExt.OUTPUT);
	ioExt.pinMode(ioExt.PORTB, 0, ioExt.INPUT_PULLUP);
}

//this is a simple application that uses the TFT display.
// => it first write a string in the top of the screen (in setup)
// => it writes the ADC value of the potentiometer in green, and
//    refreshes it each time the value differs more than 5.
int main()
{
	setup();
	int i = 0;

	while(1) {
		if ((ioExt.readBits(ioExt.PORTB) & 0x1) == 1) {
			ioExt.digitalWrite(ioExt.PORTA, i, 1);
			wait();
			ioExt.digitalWrite(ioExt.PORTA, i, 0);
			i++;
			if (i > 7) i = 0;
		} else if ((ioExt.readBits(ioExt.PORTB) & 0x1) == 0) {
			ioExt.digitalWrite(ioExt.PORTA, i, 1);
			wait();
			ioExt.digitalWrite(ioExt.PORTA, i, 0);
			i--;
			if (i < 0) i = 8;
		}
	}
}

#ifdef __cplusplus
 }
#endif /* __cplusplus */
