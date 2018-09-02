/*
  msgeq7.cpp - Library for interfacing with MSGEQ7 chip.
  Created by Steven A. Bjornson, September 1, 2018.
  See license file for license info.
*/

#include "msgeq7.h"

Msgeq7::Msgeq7(uint8_t analogpin, uint8_t strobepin, uint8_t resetpin, uint8_t threshold){
    analogpin_ = analogpin;
    strobepin_ = strobepin;
    resetpin_ = resetpin;
    threshold_ = threshold;
}

void Msgeq7::begin(){
    /*
        Sets up output pins
        Uses registers for speed
    */
    DDRD |= _BV(strobepin_);
    DDRD |= _BV(resetpin_);
    PORTD |= _BV(strobepin_);
    PORTD &= ~_BV(resetpin_);
}

void Msgeq7::update(){
    /*
        fills freqBins buffer and calculates clipping
    */
    cli();
    clippingflag_ = 0;

    PORTD |= _BV(resetpin_); //HIGH
    PORTD &= ~_BV(resetpin_); //LOW

    for (int i = 0; i < 7; i++)
    {
      PORTD &= ~_BV(strobepin_); //low
      delayMicroseconds(30); // to allow the output to settle

      freqBins[i] = analogRead(analogpin_) >> 2;
      freqBins[i] *= (freqBins[i] > threshold_);

      PORTD |= _BV(strobepin_); //high

      clippingflag_ = ((freqBins[i] == 255) | clippingflag_); //check if clipping
    }
    sei();
}

void Msgeq7::setThreshold(uint8_t threshold){
    threshold_ = threshold;
}

bool Msgeq7::checkClipping(){
    return clippingflag_;
}

uint8_t* Msgeq7::getFreqBins(){
    return freqBins;
}
