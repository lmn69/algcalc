// main.cpp - Input
// ----------------
// Entry point of the firmware.
// This initializes the App and handles the serial/physical keyboard input.

// comment this to use physical keyboard instead of the serial port
#define ALGCALC_SERIAL

#include <Arduino.h>
#include "app.hpp"

void setup() {
	App::init();
#ifdef ALGCALC_SERIAL
	Serial.begin(9600);
#endif
}

void loop() {
#ifdef ALGCALC_SERIAL
	int input;
	if ((input = Serial.read()) == -1) return;
	switch ((char)input)
	{
		case 'l': App::input(App::InputType::right); break;
		case 'h': App::input(App::InputType::left); break;
		case 'p': App::input(App::InputType::del); break;
		case '0': App::input(App::InputType::d0); break;
		case '1': App::input(App::InputType::d1); break;
		case '2': App::input(App::InputType::d2); break;
		case '3': App::input(App::InputType::d3); break;
		case '4': App::input(App::InputType::d4); break;
		case '5': App::input(App::InputType::d5); break;
		case '6': App::input(App::InputType::d6); break;
		case '7': App::input(App::InputType::d7); break;
		case '8': App::input(App::InputType::d8); break;
		case '9': App::input(App::InputType::d9); break;
	}
#endif
}