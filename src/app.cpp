#include <Wire.h>
#include <LiquidCrystal.h>
#include <tinyexpr.h>
#include "app.hpp"

#define BUFSIZE 64 // <256
#define VERSION "0.1"

// a few key points about this function:
// - this is an implementation of the missing fabs() function required by TinyExpr
// - it should be in the Arduino standard library, but for some reason it's missing
// - I stole it from musl: https://git.musl-libc.org/cgit/musl/tree/src/math/fabsf.c
// - I have absolutely no idea how it works
double fabs(double x)
{
	union { double f; uint32_t i; } u = {x};
	u.i &= 0x7fffffff;
	return u.f;
}

namespace App
{
	LiquidCrystal lcd(2, 3, 4, 5, 6, 7);
	char viewbuffer[BUFSIZE], pinbuffer[17];
	byte buflength = 0, cursoroffset = 0, viewoffset = 0;

	void view_render(byte withpin)
	{
		if (withpin)
		{
			lcd.setCursor(0, 1);
			lcd.print(pinbuffer);
		}
		if (cursoroffset < viewoffset)
		{
			viewoffset = cursoroffset;
		}
		else if (cursoroffset > viewoffset + 15)
		{
			viewoffset = cursoroffset >= 15 ? cursoroffset - 15 : 0;
		}
		byte viewlength = buflength - viewoffset;
		if (viewlength > 16)
			viewlength = 16;
		char view[17];
		memcpy(view, viewbuffer + viewoffset, viewlength);
		byte padsize = 16 - viewlength;
		if (padsize)
		{
			memset(view + viewlength, ' ', padsize);
			view[viewlength + padsize] = 0;
		}
		else
		{
			view[viewlength] = 0;
		}

		lcd.setCursor(0, 0);
		lcd.print(view);
		lcd.setCursor(cursoroffset - viewoffset, 0);
	}

	void view_left()
	{
		if (cursoroffset - 1 >= 0) {
			cursoroffset--;
			view_render(0);
		}
	}

	void view_right()
	{
		if (cursoroffset + 1 <= buflength) {
			cursoroffset++;
			view_render(0);
		}
	}

	void view_delete_cursor() {
		if (buflength == 0 || cursoroffset == 0) return;
		for (byte i = cursoroffset; i < buflength; i++)
		{
			viewbuffer[i-1] = viewbuffer[i];
		}
		buflength--;
		cursoroffset--;
	}

	void view_insert_cursor(char elem) {
		if (buflength == BUFSIZE) return;
		for (byte i = buflength; i > cursoroffset; i--)
		{
			viewbuffer[i] = viewbuffer[i-1];
		}
		viewbuffer[cursoroffset] = elem;
		buflength++;
		cursoroffset++;		
	}

	void init()
	{
		lcd.begin(16, 2);
		lcd.setCursor(1, 0);
		lcd.print(F("algCalc " VERSION));
		lcd.setCursor(1, 1);
		lcd.print(F("Adam & lemonsh"));
		delay(2000);
		lcd.clear();
		lcd.cursor();
		int terr;
		dtostrf(te_interp("0.1+0.2", &terr), -16, 14, viewbuffer);
		buflength = strlen(viewbuffer);
		view_render(0);
	}

	void input(InputType inputtype)
	{
		switch (inputtype)
		{
		// movement
		case InputType::left:  view_left(); break;
		case InputType::right: view_right(); break;
		case InputType::del:   view_delete_cursor(); break;
		// digits
		case InputType::d0: view_insert_cursor('0'); break;
		case InputType::d1: view_insert_cursor('1'); break;
		case InputType::d2: view_insert_cursor('2'); break;
		case InputType::d3: view_insert_cursor('3'); break;
		case InputType::d4: view_insert_cursor('4'); break;
		case InputType::d5: view_insert_cursor('5'); break;
		case InputType::d6: view_insert_cursor('6'); break;
		case InputType::d7: view_insert_cursor('7'); break;
		case InputType::d8: view_insert_cursor('8'); break;
		case InputType::d9: view_insert_cursor('9'); break;
		}
	}
}