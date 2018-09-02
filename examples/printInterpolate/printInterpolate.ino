#include "msgeq7.h"

// MSGEQ7
#define ANALOGPIN 3
#define STROBEPIN 2
#define RESETPIN 7
Msgeq7 fft(ANALOGPIN, STROBEPIN, RESETPIN);

float bin_select = .33; //some non-whole number value

void setup(){
    Serial.begin(115200);
    fft.begin();
}

void loop(){
    fft.update();

    Serial.print("Value at bin: ");
    Serial.print(bin_select * 6);
    Serial.print(" = ");
    Serial.print(fft.getInterpolate(bin_select));
    Serial.println();

    delay(10);
}