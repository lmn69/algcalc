#include <Wire.h>
#include <LiquidCrystal.h>
#include <tinyexpr.h>
#include "app.hpp"

double fabs(double x)
{
	union { double f; uint32_t i; } u = {x};
	u.i &= 0x7fffffff;
	return u.f;
}

LiquidCrystal lcd(2, 3, 4, 5, 6, 7);
char viewbuffer[BUFSIZE], pinbuffer[17];
byte buflength = 0, cursoroffset = 0, viewoffset = 0;

// TODO: implement *lastviewoffset*
void view_render(byte withpin) {
	if (withpin) {
		lcd.setCursor(0,1);
		lcd.print(pinbuffer);
	}
	if (cursoroffset < viewoffset) {
		viewoffset = cursoroffset;
	} else if (cursoroffset > viewoffset+15) {
		viewoffset = cursoroffset >= 15 ? cursoroffset-15 : 0;
	}
	byte viewlength = buflength-viewoffset;
	if (viewlength > 16) viewlength = 16;
	char view[17];
	memcpy(view, viewbuffer+viewoffset, viewlength);
	byte padsize = 16-viewlength;
	if (padsize) {
		memset(view+viewlength, ' ', padsize);
		view[viewlength+padsize] = 0;
	} else {
		view[viewlength] = 0;
	}

	//debug
	Serial.print("Viewlength ");
	Serial.print(viewlength);
	Serial.print(" Viewoffset ");
	Serial.print(viewoffset);
	Serial.print(" Cursoroffset ");
	Serial.print(cursoroffset);
	Serial.print(" Buflength ");
	Serial.print(buflength);
	Serial.println();

	lcd.setCursor(0,0);
	lcd.print(view);
	lcd.setCursor(cursoroffset-viewoffset, 0);
}

void view_left() {
	if (cursoroffset-1 >= 0) cursoroffset--;
}

void view_right() {
	if (cursoroffset+1 < buflength) cursoroffset++;
}

void app_init()
{
	lcd.begin(16, 2);
	lcd.setCursor(1, 0);
	lcd.print(F("algCalc " VERSION));
	lcd.setCursor(1, 1);
	lcd.print(F("Adam & lemonsh"));
	delay(2000);
	lcd.cursor();
	strcpy(viewbuffer, "reasumujacwszystkieaspektykwintesencjitematu");
	buflength = 44;
	view_render(1);
}

void app_input(app_input_type inputtype)
{
	switch (inputtype)
	{
	case left:
		view_left();
		view_render(0);
		break;
	
	case right:
		view_right();
		view_render(0);
		break;
	}
}