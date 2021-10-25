#include <Wire.h>
#include <Arduino.h>
#include <LiquidCrystal.h>
#include <tinyexpr.h>

// a few key points about this function:
// - this is an implementation of the missing fabs() function required by TinyExpr
// - it should be in the Arduino standard library, but for some reason it's missing
// - I stole it from musl: https://git.musl-libc.org/cgit/musl/tree/src/math/fabsf.c
// - I have absolutely no idea how it works
double fabs(double x)
{
    union {double f; uint32_t i;} u = {x};
    u.i &= 0x7fffffff;
    return u.f;
}

char* leak;
double calcresult;
int calcerr;
LiquidCrystal lcd(2, 3, 4, 5, 6, 7);

void setup() {
  lcd.begin(16, 2);
  lcd.print(te_interp("2.0+abs(-2.0)", &calcerr));
}

void loop() {}