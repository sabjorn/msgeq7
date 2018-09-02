#include "msgeq7.h"

// MSGEQ7
#define ANALOGPIN 3
#define STROBEPIN 2
#define RESETPIN 7
Msgeq7 fft(ANALOGPIN, STROBEPIN, RESETPIN);

uint8_t *freqBins;

void setup(){
    Serial.begin(115200);
    fft.begin();
    freqBins = fft.getFreqBins(); // access to bin array
}

void loop(){
    fft.update();

    for(int i = 0; i < 7; ++i){
        Serial.print(freqBins[i]);
        Serial.print("\t");
    }
    Serial.println();

    if(fft.checkClipping()) Serial.println("CLIPPING");

    delay(10);
}