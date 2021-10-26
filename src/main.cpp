#include <Arduino.h>
#include "app.hpp"

void setup() {
	Serial.begin(9600);
	app_init();
}

void loop() {
	int input;
	if ((input = Serial.read()) == -1) return;
	switch ((char)input)
	{
	case 'l':
		app_input(right);
		break;
	
	case 'h':
		app_input(left);
		break;
	}
}