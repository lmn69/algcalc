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
	case 'l':
		App::input(App::InputType::right);
		break;
	
	case 'h':
		App::input(App::InputType::left);
		break;
	}
#endif
}