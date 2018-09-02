#ifndef MSGEQ7_H
#define MSGEQ7_H

#if (ARDUINO >= 100)
 #include <Arduino.h>
#else
 #include <WProgram.h>
 #include <pins_arduino.h>
#endif

class Msgeq7{
    public:
        Msgeq7(uint8_t analogpin, uint8_t strobepin, uint8_t resetpin, uint8_t threshold = 0);
        void begin();
        void update();
        void setThreshold(uint8_t threshold);
        bool checkClipping();
        uint8_t getInterpolate(float bin); // input bounded [0, 1]
        uint8_t* getFreqBins();

    private:
        uint8_t analogpin_, strobepin_, resetpin_;
        uint8_t threshold_;
        bool clippingflag_;
        uint8_t freqBins[7]; // frequency levels
};

#endif // MSGEQ7_H
