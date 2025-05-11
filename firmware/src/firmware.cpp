#include "firmware.h"

#ifdef __AVR__
#include <avr/interrupt.h>
#include <avr/power.h>
#include <avr/wdt.h>
#include <avr/sleep.h>
#endif

#define BTN PIN_PC1
#define BOOST_EN PIN_PC2

using namespace neoheart;
void enableSleep();
void softwareReset();
void runRandomAnim();
void disableSleep();

void setup() {
    // leds initialization
    initLeds();
    // clear strip
    clearStrip();
    // init io
    pinMode(BTN, INPUT_PULLUP);
    pinMode(BOOST_EN, OUTPUT);
    // init random seed
    randomSeed(analogRead(PIN_PA2));
    // attach to interrupt
    attachInterrupt(digitalPinToInterrupt(BTN), softwareReset, FALLING);
    // run first animation
    runRandomAnim();
}

void loop() {
    // nothing to do here
}

void runRandomAnim(){
    // the boost converter is enabled to power the strip until the end of the animation, then an interrupt is attached to the button and the attiny816 is put to sleep
    digitalWrite(BOOST_EN, HIGH);
    void (*animations[])() = {heartbeat, bottomup, theatherFill, bounce, incrementalFill, chase, colorWipe, rainbow, theaterChaseRainbow};
    int randomIndex = random(sizeof(animations) / sizeof(animations[0]));
    animations[randomIndex]();
    digitalWrite(BOOST_EN, LOW);
    detachInterrupt(digitalPinToInterrupt(BTN));
    attachInterrupt(digitalPinToInterrupt(BTN), disableSleep, CHANGE);
    enableSleep();
}

void softwareReset() {
    // clear interrupts
    cli();
    // write in the watchdog control register
    _PROTECTED_WRITE(WDT.CTRLA, WDT_PERIOD_8CLK_gc | WDT_WINDOW_OFF_gc);
    // wait for the watchdog to reset the device
    while (1);
}

void enableSleep() {
    sleep_enable();
    set_sleep_mode(SLEEP_MODE_PWR_DOWN);  
    sleep_cpu();
}

void disableSleep() {
    sleep_disable();
    softwareReset();
}
