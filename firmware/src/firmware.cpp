#include "firmware.h"

#ifdef __AVR__
#include <avr/interrupt.h>
#include <avr/power.h>
#include <avr/wdt.h>
#include <avr/sleep.h>
#endif

#define BTN PIN_PC1
#define MOSFET PIN_PC2

using namespace neoheart;

void setup() {
    // init leds
    initLeds();
    // init button
    pinMode(BTN, INPUT_PULLUP);

    // init random seed
    randomSeed(analogRead(PIN_PA2));

    // attach to interrupt
    attachInterrupt(digitalPinToInterrupt(BTN), disableSleep, FALLING);
}

void loop() {
    if (digitalRead(BTN) == LOW) {
        // run animations
        void (*animations[])() = {heartbeat, bottomup, theatherFill, bounce, incrementalFill, chase, colorWipe, rainbow, theaterChaseRainbow};
        int randomIndex = random(sizeof(animations) / sizeof(animations[0]));
        animations[randomIndex]();
        enableSleep();
    }
}

void enableSleep() {
    set_sleep_mode(SLEEP_MODE_PWR_DOWN);  
    sleep_enable();                      
    sleep_cpu();                          
    sleep_disable();                      
}

void disableSleep() {
    sleep_disable(); 
    detachInterrupt(digitalPinToInterrupt(BTN));
}

void softwareReset() {
 wdt_disable();
 wdt_enable(WDTO_15MS);
 while (1) {}
}

