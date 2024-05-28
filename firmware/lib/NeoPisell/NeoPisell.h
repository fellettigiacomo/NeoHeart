/*!
 * @file NeoPisell.h
 *
 * This is part of Adafruit's NeoPixel library for the Arduino platform,
 * allowing a broad range of microcontroller boards (most AVR boards,
 * many ARM devices, ESP8266 and ESP32, among others) to control Adafruit
 * NeoPixels, FLORA RGB Smart Pixels and compatible devices -- WS2811,
 * WS2812, WS2812B, SK6812, etc.
 *
 * Adafruit invests time and resources providing this open source code,
 * please support Adafruit and open-source hardware by purchasing products
 * from Adafruit!
 *
 * Written by Phil "Paint Your Dragon" Burgess for Adafruit Industries,
 * with contributions by PJRC, Michael Miller and other members of the
 * open source community.
 *
 * This file is part of the NeoPisell library.
 *
 * NeoPisell is free software: you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public License as
 * published by the Free Software Foundation, either version 3 of the
 * License, or (at your option) any later version.
 *
 * NeoPisell is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with NeoPixel.  If not, see
 * <http://www.gnu.org/licenses/>.
 *
 */

#ifndef ADAFRUIT_NEOPIXEL_H
#define ADAFRUIT_NEOPIXEL_H

#include <Arduino.h>

#ifndef __AVR__
#error "This library only supports AVR processors."
#endif

#include "AttinyPins.h"


// The order of primary colors in the NeoPixel data stream can vary among
// device types, manufacturers and even different revisions of the same
// item.  The third parameter to the NeoPisell constructor encodes
// the per-pixel byte offsets of the red, green and blue primaries (plus
// white, if present) in the data stream -- the following #defines provide
// an easier-to-use named version for each permutation. e.g. NEO_GRB
// indicates a NeoPixel-compatible device expecting three bytes per pixel,
// with the first byte transmitted containing the green value, second
// containing red and third containing blue. The in-memory representation
// of a chain of NeoPixels is the same as the data-stream order; no
// re-ordering of bytes is required when issuing data to the chain.
// Most of these values won't exist in real-world devices, but it's done
// this way so we're ready for it (also, if using the WS2811 driver IC,
// one might have their pixels set up in any weird permutation).

// Bits 5,4 of this value are the offset (0-3) from the first byte of a
// pixel to the location of the red color byte.  Bits 3,2 are the green
// offset and 1,0 are the blue offset.  If it is an RGBW-type device
// (supporting a white primary in addition to R,G,B), bits 7,6 are the
// offset to the white byte...otherwise, bits 7,6 are set to the same value
// as 5,4 (red) to indicate an RGB (not RGBW) device.
// i.e. binary representation:
// 0bWWRRGGBB for RGBW devices
// 0bRRRRGGBB for RGB

// If 400 KHz support is enabled, the third parameter to the constructor
// requires a 16-bit value (in order to select 400 vs 800 KHz speed).
// If only 800 KHz is enabled (as is default on ATtiny), an 8-bit value
// is sufficient to encode pixel color order, saving some space.

#ifdef NEO_KHZ400
using neopixel_t = uint16_t; ///< 3rd arg to NeoPisell constructor
#else
using neopixel_t = uint8_t; ///< 3rd arg to NeoPisell constructor
#endif

// RGB NeoPixel permutations; white and red offsets are always same
// Offset:        W          R          G          B
static constexpr neopixel_t NEO_RGB = ((0 << 6) | (0 << 4) | (1 << 2) | (2)); ///< Transmit as R,G,B
static constexpr neopixel_t NEO_RBG = ((0 << 6) | (0 << 4) | (2 << 2) | (1)); ///< Transmit as R,B,G
static constexpr neopixel_t NEO_GRB = ((1 << 6) | (1 << 4) | (0 << 2) | (2)); ///< Transmit as G,R,B
static constexpr neopixel_t NEO_GBR = ((2 << 6) | (2 << 4) | (0 << 2) | (1)); ///< Transmit as G,B,R
static constexpr neopixel_t NEO_BRG = ((1 << 6) | (1 << 4) | (2 << 2) | (0)); ///< Transmit as B,R,G
static constexpr neopixel_t NEO_BGR = ((2 << 6) | (2 << 4) | (1 << 2) | (0)); ///< Transmit as B,G,R

// RGBW NeoPixel permutations; all 4 offsets are distinct
// Offset:         W          R          G          B
static constexpr neopixel_t NEO_WRGB = ((0 << 6) | (1 << 4) | (2 << 2) | (3)); ///< Transmit as W,R,G,B
static constexpr neopixel_t NEO_WRBG = ((0 << 6) | (1 << 4) | (3 << 2) | (2)); ///< Transmit as W,R,B,G
static constexpr neopixel_t NEO_WGRB = ((0 << 6) | (2 << 4) | (1 << 2) | (3)); ///< Transmit as W,G,R,B
static constexpr neopixel_t NEO_WGBR = ((0 << 6) | (3 << 4) | (1 << 2) | (2)); ///< Transmit as W,G,B,R
static constexpr neopixel_t NEO_WBRG = ((0 << 6) | (2 << 4) | (3 << 2) | (1)); ///< Transmit as W,B,R,G
static constexpr neopixel_t NEO_WBGR = ((0 << 6) | (3 << 4) | (2 << 2) | (1)); ///< Transmit as W,B,G,R

static constexpr neopixel_t NEO_RWGB = ((1 << 6) | (0 << 4) | (2 << 2) | (3)); ///< Transmit as R,W,G,B
static constexpr neopixel_t NEO_RWBG = ((1 << 6) | (0 << 4) | (3 << 2) | (2)); ///< Transmit as R,W,B,G
static constexpr neopixel_t NEO_RGWB = ((2 << 6) | (0 << 4) | (1 << 2) | (3)); ///< Transmit as R,G,W,B
static constexpr neopixel_t NEO_RGBW = ((3 << 6) | (0 << 4) | (1 << 2) | (2)); ///< Transmit as R,G,B,W
static constexpr neopixel_t NEO_RBWG = ((2 << 6) | (0 << 4) | (3 << 2) | (1)); ///< Transmit as R,B,W,G
static constexpr neopixel_t NEO_RBGW = ((3 << 6) | (0 << 4) | (2 << 2) | (1)); ///< Transmit as R,B,G,W

static constexpr neopixel_t NEO_GWRB = ((1 << 6) | (2 << 4) | (0 << 2) | (3)); ///< Transmit as G,W,R,B
static constexpr neopixel_t NEO_GWBR = ((1 << 6) | (3 << 4) | (0 << 2) | (2)); ///< Transmit as G,W,B,R
static constexpr neopixel_t NEO_GRWB = ((2 << 6) | (1 << 4) | (0 << 2) | (3)); ///< Transmit as G,R,W,B
static constexpr neopixel_t NEO_GRBW = ((3 << 6) | (1 << 4) | (0 << 2) | (2)); ///< Transmit as G,R,B,W
static constexpr neopixel_t NEO_GBWR = ((2 << 6) | (3 << 4) | (0 << 2) | (1)); ///< Transmit as G,B,W,R
static constexpr neopixel_t NEO_GBRW = ((3 << 6) | (2 << 4) | (0 << 2) | (1)); ///< Transmit as G,B,R,W

static constexpr neopixel_t NEO_BWRG = ((1 << 6) | (2 << 4) | (3 << 2) | (0)); ///< Transmit as B,W,R,G
static constexpr neopixel_t NEO_BWGR = ((1 << 6) | (3 << 4) | (2 << 2) | (0)); ///< Transmit as B,W,G,R
static constexpr neopixel_t NEO_BRWG = ((2 << 6) | (1 << 4) | (3 << 2) | (0)); ///< Transmit as B,R,W,G
static constexpr neopixel_t NEO_BRGW = ((3 << 6) | (1 << 4) | (2 << 2) | (0)); ///< Transmit as B,R,G,W
static constexpr neopixel_t NEO_BGWR = ((2 << 6) | (3 << 4) | (1 << 2) | (0)); ///< Transmit as B,G,W,R
static constexpr neopixel_t NEO_BGRW = ((3 << 6) | (2 << 4) | (1 << 2) | (0)); ///< Transmit as B,G,R,W

// Add NEO_KHZ400 to the color order value to indicate a 400 KHz device.
// All but the earliest v1 NeoPixels expect an 800 KHz data stream, this is
// the default if unspecified. Because flash space is very limited on ATtiny
// devices (e.g. Trinket, Gemma), v1 NeoPixels aren't handled by default on
// those chips, though it can be enabled by removing the ifndef/endif below,
// but code will be bigger. Conversely, can disable the NEO_KHZ400 line on
// other MCUs to remove v1 support and save a little space.

#define NEO_KHZ800 0x0000 ///< 800 KHz data transmission
#ifndef __AVR_ATtiny85__
#define NEO_KHZ400 0x0100 ///< 400 KHz data transmission
#endif


// These two tables are declared outside the NeoPisell class
// because some boards may require oldschool compilers that don't
// handle the C++11 constexpr keyword.

/* A PROGMEM (flash mem) table containing 8-bit unsigned sine wave (0-255).
   Copy & paste this snippet into a Python REPL to regenerate:
import math
for x in range(256):
    print("{:3},".format(int((math.sin(x/128.0*math.pi)+1.0)*127.5+0.5))),
    if x&15 == 15: print
*/
static const uint8_t PROGMEM _NeoPixelSineTable[256] = {
        128, 131, 134, 137, 140, 143, 146, 149, 152, 155, 158, 162, 165, 167, 170,
        173, 176, 179, 182, 185, 188, 190, 193, 196, 198, 201, 203, 206, 208, 211,
        213, 215, 218, 220, 222, 224, 226, 228, 230, 232, 234, 235, 237, 238, 240,
        241, 243, 244, 245, 246, 248, 249, 250, 250, 251, 252, 253, 253, 254, 254,
        254, 255, 255, 255, 255, 255, 255, 255, 254, 254, 254, 253, 253, 252, 251,
        250, 250, 249, 248, 246, 245, 244, 243, 241, 240, 238, 237, 235, 234, 232,
        230, 228, 226, 224, 222, 220, 218, 215, 213, 211, 208, 206, 203, 201, 198,
        196, 193, 190, 188, 185, 182, 179, 176, 173, 170, 167, 165, 162, 158, 155,
        152, 149, 146, 143, 140, 137, 134, 131, 128, 124, 121, 118, 115, 112, 109,
        106, 103, 100, 97, 93, 90, 88, 85, 82, 79, 76, 73, 70, 67, 65,
        62, 59, 57, 54, 52, 49, 47, 44, 42, 40, 37, 35, 33, 31, 29,
        27, 25, 23, 21, 20, 18, 17, 15, 14, 12, 11, 10, 9, 7, 6,
        5, 5, 4, 3, 2, 2, 1, 1, 1, 0, 0, 0, 0, 0, 0,
        0, 1, 1, 1, 2, 2, 3, 4, 5, 5, 6, 7, 9, 10, 11,
        12, 14, 15, 17, 18, 20, 21, 23, 25, 27, 29, 31, 33, 35, 37,
        40, 42, 44, 47, 49, 52, 54, 57, 59, 62, 65, 67, 70, 73, 76,
        79, 82, 85, 88, 90, 93, 97, 100, 103, 106, 109, 112, 115, 118, 121,
        124};

/* Similar to above, but for an 8-bit gamma-correction table.
   Copy & paste this snippet into a Python REPL to regenerate:
import math
gamma=2.6
for x in range(256):
    print("{:3},".format(int(math.pow((x)/255.0,gamma)*255.0+0.5))),
    if x&15 == 15: print
*/
static const uint8_t PROGMEM _NeoPixelGammaTable[256] = {
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 3,
        3, 3, 3, 3, 3, 4, 4, 4, 4, 5, 5, 5, 5, 5, 6,
        6, 6, 6, 7, 7, 7, 8, 8, 8, 9, 9, 9, 10, 10, 10,
        11, 11, 11, 12, 12, 13, 13, 13, 14, 14, 15, 15, 16, 16, 17,
        17, 18, 18, 19, 19, 20, 20, 21, 21, 22, 22, 23, 24, 24, 25,
        25, 26, 27, 27, 28, 29, 29, 30, 31, 31, 32, 33, 34, 34, 35,
        36, 37, 38, 38, 39, 40, 41, 42, 42, 43, 44, 45, 46, 47, 48,
        49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63,
        64, 65, 66, 68, 69, 70, 71, 72, 73, 75, 76, 77, 78, 80, 81,
        82, 84, 85, 86, 88, 89, 90, 92, 93, 94, 96, 97, 99, 100, 102,
        103, 105, 106, 108, 109, 111, 112, 114, 115, 117, 119, 120, 122, 124, 125,
        127, 129, 130, 132, 134, 136, 137, 139, 141, 143, 145, 146, 148, 150, 152,
        154, 156, 158, 160, 162, 164, 166, 168, 170, 172, 174, 176, 178, 180, 182,
        184, 186, 188, 191, 193, 195, 197, 199, 202, 204, 206, 209, 211, 213, 215,
        218, 220, 223, 225, 227, 230, 232, 235, 237, 240, 242, 245, 247, 250, 252,
        255};

/*!
    @brief  Class that stores state and functions for interacting with
            Adafruit NeoPixels and compatible devices.
*/

template<uint16_t NumPins, int8_t Pin, neopixel_t NeoPixelType = NEO_GRB + NEO_KHZ800>
class NeoPisell {
private:
    static_assert(Pin >= 0, "Invalid pin number");
    using PIN = PinInfo<Pin>;

    static constexpr int8_t pin = Pin;                                ///< Output pin number (-1 if not yet set)
    static constexpr uint16_t numLEDs = NumPins;                      ///< Number of RGB LEDs in strip
    static constexpr uint8_t rOffset = (NeoPixelType >> 4) & 0b11;    ///< Red index within each 3- or 4-byte pixel
    static constexpr uint8_t gOffset = (NeoPixelType >> 2) & 0b11;    ///< Index of green byte
    static constexpr uint8_t bOffset = NeoPixelType & 0b11;           ///< Index of blue byte
    static constexpr uint8_t wOffset = (NeoPixelType >> 6) & 0b11;    ///< Index of white (==rOffset if no white)
    static constexpr uint16_t numBytes = NumPins * ((wOffset == rOffset) ? 3 : 4);  ///< Size of 'pixels' buffer below

#ifdef NEO_KHZ400 // If 400 KHz NeoPixel support enabled...
    static constexpr bool is800KHz = (NeoPixelType < 256);            ///< true if 800 KHz pixels
#endif

    bool begun = false;                                               ///< true if begin() previously called
    uint8_t brightness = 0;                                           ///< Strip brightness 0-255 (stored as +1)
    uint8_t pixels[numBytes]{};                                       ///< Holds LED color values (3 or 4 bytes each)

    uint32_t endTime = 0;                                             ///< Latch timing reference

public:
    NeoPisell() {
      clear();
    }

    ~NeoPisell() {
      if (begun) {
        pinMode(pin, INPUT);
      }
    }

    void begin() {
      pinMode(pin, OUTPUT);
      digitalWrite(pin, LOW);
      begun = true;
    }

    void show(void) {
      // Data latch = 300+ microsecond pause in the output stream. Rather than
      // put a delay at the end of the function, the ending time is noted and
      // the function will simply hold off (if needed) on issuing the
      // subsequent round of data until the latch time has elapsed. This
      // allows the mainline code to start generating the next frame of data
      // rather than stalling for the latch.
      while (!canShow());
      // endTime is a private member (rather than global var) so that multiple
      // instances on different pins can be quickly issued in succession (each
      // instance doesn't delay the next).

      // In order to make this code runtime-configurable to work with any pin,
      // SBI/CBI instructions are eschewed in favor of full PORT writes via the
      // OUT or ST instructions. It relies on two facts: that peripheral
      // functions (such as PWM) take precedence on output pins, so our PORT-
      // wide writes won't interfere, and that interrupts are globally disabled
      // while data is being issued to the LEDs, so no other code will be
      // accessing the PORT. The code takes an initial 'snapshot' of the PORT
      // state, computes 'pin high' and 'pin low' values, and writes these back
      // to the PORT register as needed.

      // AVR MCUs -- ATmega & ATtiny (no XMEGA) ---------------------------------

      volatile uint16_t i = numBytes; // Loop counter
      volatile uint8_t *ptr = pixels; // Pointer to next byte
      volatile uint8_t b = *ptr++;    // Current byte value
      volatile uint8_t hi;            // PORT w/output bit set high
      volatile uint8_t lo;            // PORT w/output bit set low

      // Hand-tuned assembly code issues data to the LED drivers at a specific
      // rate. There's separate code for different CPU speeds (8, 16 MHz)
      // for both the WS2811 (400 KHz) and WS2812 (800 KHz) drivers. The
      // datastream timing for the LED drivers allows a little wiggle room each
      // way (listed in the datasheets), so the conditions for compiling each
      // case are set up for a range of frequencies rather than just the exact
      // 8 or 16 MHz values, permitting use with some close-but-not-spot-on
      // devices (e.g. 16.5 MHz DigiSpark). The ranges were arrived at based
      // on the datasheet figures and have not been extensively tested outside
      // the canonical 8/16 MHz speeds; there's no guarantee these will work
      // close to the extremes (or possibly they could be pushed further).
      // Keep in mind only one CPU speed case actually gets compiled; the
      // resulting program isn't as massive as it might look from source here.

// 8 MHz(ish) AVR ---------------------------------------------------------
#if (F_CPU >= 7400000UL) && (F_CPU <= 9500000UL)

      volatile VPORT_t *const port = PIN::vport();
      uintptr_t portOut = PIN::vportAddr + offsetof(VPORT_t, OUT);

      hi = port->OUT | PIN::pinMask;
      lo = port->OUT & ~PIN::pinMask;

#if defined(NEO_KHZ400) // 800 KHz check needed only if 400 KHz support enabled
      if constexpr (is800KHz) {
#endif

        // First, next bits out
        volatile uint8_t n1;
        volatile uint8_t n2 = 0;

        // Squeezing an 800 KHz stream out of an 8 MHz chip requires code
        // specific to each PORT register.

        // 10 instruction clocks per bit: HHxxxxxLLL
        // OUT instructions:              ^ ^    ^   (NeoPixelType=0,2,7)

        n1 = lo;
        if (b & 0x80)
          n1 = hi;

        // Dirty trick: RJMPs proceeding to the next instruction are used
        // to delay two clock cycles in one instruction word (rather than
        // using two NOPs). This was necessary in order to squeeze the
        // loop down to exactly 64 words -- the maximum possible for a
        // relative branch.

        asm volatile(
                "headD:"
                "\n\t" // Clk  Pseudocode
                // Bit 7:
                "out  %[port] , %[hi]"
                "\n\t" // 1    PORT = hi
                "mov  %[n2]   , %[lo]"
                "\n\t" // 1    n2   = lo
                "out  %[port] , %[n1]"
                "\n\t" // 1    PORT = n1
                "rjmp .+0"
                "\n\t" // 2    nop nop
                "sbrc %[byte] , 6"
                "\n\t" // 1-2  if(b & 0x40)
                "mov %[n2]   , %[hi]"
                "\n\t" // 0-1   n2 = hi
                "out  %[port] , %[lo]"
                "\n\t" // 1    PORT = lo
                "rjmp .+0"
                "\n\t" // 2    nop nop
                // Bit 6:
                "out  %[port] , %[hi]"
                "\n\t" // 1    PORT = hi
                "mov  %[n1]   , %[lo]"
                "\n\t" // 1    n1   = lo
                "out  %[port] , %[n2]"
                "\n\t" // 1    PORT = n2
                "rjmp .+0"
                "\n\t" // 2    nop nop
                "sbrc %[byte] , 5"
                "\n\t" // 1-2  if(b & 0x20)
                "mov %[n1]   , %[hi]"
                "\n\t" // 0-1   n1 = hi
                "out  %[port] , %[lo]"
                "\n\t" // 1    PORT = lo
                "rjmp .+0"
                "\n\t" // 2    nop nop
                // Bit 5:
                "out  %[port] , %[hi]"
                "\n\t" // 1    PORT = hi
                "mov  %[n2]   , %[lo]"
                "\n\t" // 1    n2   = lo
                "out  %[port] , %[n1]"
                "\n\t" // 1    PORT = n1
                "rjmp .+0"
                "\n\t" // 2    nop nop
                "sbrc %[byte] , 4"
                "\n\t" // 1-2  if(b & 0x10)
                "mov %[n2]   , %[hi]"
                "\n\t" // 0-1   n2 = hi
                "out  %[port] , %[lo]"
                "\n\t" // 1    PORT = lo
                "rjmp .+0"
                "\n\t" // 2    nop nop
                // Bit 4:
                "out  %[port] , %[hi]"
                "\n\t" // 1    PORT = hi
                "mov  %[n1]   , %[lo]"
                "\n\t" // 1    n1   = lo
                "out  %[port] , %[n2]"
                "\n\t" // 1    PORT = n2
                "rjmp .+0"
                "\n\t" // 2    nop nop
                "sbrc %[byte] , 3"
                "\n\t" // 1-2  if(b & 0x08)
                "mov %[n1]   , %[hi]"
                "\n\t" // 0-1   n1 = hi
                "out  %[port] , %[lo]"
                "\n\t" // 1    PORT = lo
                "rjmp .+0"
                "\n\t" // 2    nop nop
                // Bit 3:
                "out  %[port] , %[hi]"
                "\n\t" // 1    PORT = hi
                "mov  %[n2]   , %[lo]"
                "\n\t" // 1    n2   = lo
                "out  %[port] , %[n1]"
                "\n\t" // 1    PORT = n1
                "rjmp .+0"
                "\n\t" // 2    nop nop
                "sbrc %[byte] , 2"
                "\n\t" // 1-2  if(b & 0x04)
                "mov %[n2]   , %[hi]"
                "\n\t" // 0-1   n2 = hi
                "out  %[port] , %[lo]"
                "\n\t" // 1    PORT = lo
                "rjmp .+0"
                "\n\t" // 2    nop nop
                // Bit 2:
                "out  %[port] , %[hi]"
                "\n\t" // 1    PORT = hi
                "mov  %[n1]   , %[lo]"
                "\n\t" // 1    n1   = lo
                "out  %[port] , %[n2]"
                "\n\t" // 1    PORT = n2
                "rjmp .+0"
                "\n\t" // 2    nop nop
                "sbrc %[byte] , 1"
                "\n\t" // 1-2  if(b & 0x02)
                "mov %[n1]   , %[hi]"
                "\n\t" // 0-1   n1 = hi
                "out  %[port] , %[lo]"
                "\n\t" // 1    PORT = lo
                "rjmp .+0"
                "\n\t" // 2    nop nop
                // Bit 1:
                "out  %[port] , %[hi]"
                "\n\t" // 1    PORT = hi
                "mov  %[n2]   , %[lo]"
                "\n\t" // 1    n2   = lo
                "out  %[port] , %[n1]"
                "\n\t" // 1    PORT = n1
                "rjmp .+0"
                "\n\t" // 2    nop nop
                "sbrc %[byte] , 0"
                "\n\t" // 1-2  if(b & 0x01)
                "mov %[n2]   , %[hi]"
                "\n\t" // 0-1   n2 = hi
                "out  %[port] , %[lo]"
                "\n\t" // 1    PORT = lo
                "sbiw %[count], 1"
                "\n\t" // 2    i-- (don't act on Z flag yet)
                // Bit 0:
                "out  %[port] , %[hi]"
                "\n\t" // 1    PORT = hi
                "mov  %[n1]   , %[lo]"
                "\n\t" // 1    n1   = lo
                "out  %[port] , %[n2]"
                "\n\t" // 1    PORT = n2
                "ld   %[byte] , %a[ptr]+"
                "\n\t" // 2    b = *ptr++
                "sbrc %[byte] , 7"
                "\n\t" // 1-2  if(b & 0x80)
                "mov %[n1]   , %[hi]"
                "\n\t" // 0-1   n1 = hi
                "out  %[port] , %[lo]"
                "\n\t" // 1    PORT = lo
                "brne headD"
                "\n" // 2    while(i) (Z flag set above)
                : [byte] "+r"(b), [n1] "+r"(n1), [n2] "+r"(n2), [count] "+w"(i)
        : [port] "I"(portOut), [ptr] "e"(ptr), [hi] "r"(hi),
        [lo] "r"(lo));


#if defined(NEO_KHZ400)
      } else { // end 800 KHz, do 400 KHz

        // Timing is more relaxed; unrolling the inner loop for each bit is
        // not necessary. Still using the peculiar RJMPs as 2X NOPs, not out
        // of need but just to trim the code size down a little.
        // This 400-KHz-datastream-on-8-MHz-CPU code is not quite identical
        // to the 800-on-16 code later -- the hi/lo timing between WS2811 and
        // WS2812 is not simply a 2:1 scale!

        // 20 inst. clocks per bit: HHHHxxxxxxLLLLLLLLLL
        // ST instructions:         ^   ^     ^          (NeoPixelType=0,4,10)

        volatile uint8_t next;
        volatile uint8_t bit;

        next = lo;
        bit = 8;

        asm volatile("head20:"
                     "\n\t" // Clk  Pseudocode    (NeoPixelType =  0)
                     "st   %a[port], %[hi]"
                     "\n\t" // 2    PORT = hi     (NeoPixelType =  2)
                     "sbrc %[byte] , 7"
                     "\n\t" // 1-2  if(b & 128)
                     "mov  %[next], %[hi]"
                     "\n\t" // 0-1   next = hi    (NeoPixelType =  4)
                     "st   %a[port], %[next]"
                     "\n\t" // 2    PORT = next   (NeoPixelType =  6)
                     "mov  %[next] , %[lo]"
                     "\n\t" // 1    next = lo     (NeoPixelType =  7)
                     "dec  %[bit]"
                     "\n\t" // 1    bit--         (NeoPixelType =  8)
                     "breq nextbyte20"
                     "\n\t" // 1-2  if(bit == 0)
                     "rol  %[byte]"
                     "\n\t" // 1    b <<= 1       (NeoPixelType = 10)
                     "st   %a[port], %[lo]"
                     "\n\t" // 2    PORT = lo     (NeoPixelType = 12)
                     "rjmp .+0"
                     "\n\t" // 2    nop nop       (NeoPixelType = 14)
                     "rjmp .+0"
                     "\n\t" // 2    nop nop       (NeoPixelType = 16)
                     "rjmp .+0"
                     "\n\t" // 2    nop nop       (NeoPixelType = 18)
                     "rjmp head20"
                     "\n\t" // 2    -> head20 (next bit out)
                     "nextbyte20:"
                     "\n\t" //                    (NeoPixelType = 10)
                     "st   %a[port], %[lo]"
                     "\n\t" // 2    PORT = lo     (NeoPixelType = 12)
                     "nop"
                     "\n\t" // 1    nop           (NeoPixelType = 13)
                     "ldi  %[bit]  , 8"
                     "\n\t" // 1    bit = 8       (NeoPixelType = 14)
                     "ld   %[byte] , %a[ptr]+"
                     "\n\t" // 2    b = *ptr++    (NeoPixelType = 16)
                     "sbiw %[count], 1"
                     "\n\t" // 2    i--           (NeoPixelType = 18)
                     "brne head20"
                     "\n" // 2    if(i != 0) -> (next byte)
                : [port] "+e"(portOut), [byte] "+r"(b), [bit] "+r"(bit),
        [next] "+r"(next), [count] "+w"(i)
        : [hi] "r"(hi), [lo] "r"(lo), [ptr] "e"(ptr));
      }
#endif // NEO_KHZ400

      // 16 MHz(ish) AVR --------------------------------------------------------
#elif (F_CPU >= 15400000UL) && (F_CPU <= 19000000L)

      volatile PORT_t *port = PIN::port();
      volatile register8_t *portOut = &port->OUT;

      hi = port->OUT | PIN::pinMask;
      lo = port->OUT & ~PIN::pinMask;
      volatile uint8_t next = lo;
      volatile uint8_t bit = 8;


#if defined(NEO_KHZ400) // 800 KHz check needed only if 400 KHz support enabled
      if constexpr (is800KHz) {
#endif

        // WS2811 and WS2812 have different hi/lo duty cycles; this is
        // similar but NOT an exact copy of the prior 400-on-8 code.

        // 20 inst. clocks per bit: HHHHHxxxxxxxxLLLLLLL
        // ST instructions:         ^   ^        ^       (NeoPixelType=0,5,13)

        asm volatile("head20:"
                     "\n\t" // Clk  Pseudocode    (NeoPixelType =  0)
                     "st   %a[port],  %[hi]"
                     "\n\t" // 2    PORT = hi     (NeoPixelType =  2)
                     "sbrc %[byte],  7"
                     "\n\t" // 1-2  if(b & 128)
                     "mov  %[next], %[hi]"
                     "\n\t" // 0-1   next = hi    (NeoPixelType =  4)
                     "dec  %[bit]"
                     "\n\t" // 1    bit--         (NeoPixelType =  5)
                     "st   %a[port],  %[next]"
                     "\n\t" // 2    PORT = next   (NeoPixelType =  7)
                     "mov  %[next] ,  %[lo]"
                     "\n\t" // 1    next = lo     (NeoPixelType =  8)
                     "breq nextbyte20"
                     "\n\t" // 1-2  if(bit == 0) (from dec above)
                     "rol  %[byte]"
                     "\n\t" // 1    b <<= 1       (NeoPixelType = 10)
                     "rjmp .+0"
                     "\n\t" // 2    nop nop       (NeoPixelType = 12)
                     "nop"
                     "\n\t" // 1    nop           (NeoPixelType = 13)
                     "st   %a[port],  %[lo]"
                     "\n\t" // 2    PORT = lo     (NeoPixelType = 15)
                     "nop"
                     "\n\t" // 1    nop           (NeoPixelType = 16)
                     "rjmp .+0"
                     "\n\t" // 2    nop nop       (NeoPixelType = 18)
                     "rjmp head20"
                     "\n\t" // 2    -> head20 (next bit out)
                     "nextbyte20:"
                     "\n\t" //                    (NeoPixelType = 10)
                     "ldi  %[bit]  ,  8"
                     "\n\t" // 1    bit = 8       (NeoPixelType = 11)
                     "ld   %[byte] ,  %a[ptr]+"
                     "\n\t" // 2    b = *ptr++    (NeoPixelType = 13)
                     "st   %a[port], %[lo]"
                     "\n\t" // 2    PORT = lo     (NeoPixelType = 15)
                     "nop"
                     "\n\t" // 1    nop           (NeoPixelType = 16)
                     "sbiw %[count], 1"
                     "\n\t" // 2    i--           (NeoPixelType = 18)
                     "brne head20"
                     "\n" // 2    if(i != 0) -> (next byte)
                : [port] "+e"(portOut), [byte] "+r"(b), [bit] "+r"(bit),
        [next] "+r"(next), [count] "+w"(i)
        : [ptr] "e"(ptr), [hi] "r"(hi), [lo] "r"(lo));

#if defined(NEO_KHZ400)
      } else { // 400 KHz

        // The 400 KHz clock on 16 MHz MCU is the most 'relaxed' version.

        // 40 inst. clocks per bit: HHHHHHHHxxxxxxxxxxxxLLLLLLLLLLLLLLLLLLLL
        // ST instructions:         ^       ^           ^         (NeoPixelType=0,8,20)

        asm volatile("head40:"
                     "\n\t" // Clk  Pseudocode    (NeoPixelType =  0)
                     "st   %a[port], %[hi]"
                     "\n\t" // 2    PORT = hi     (NeoPixelType =  2)
                     "sbrc %[byte] , 7"
                     "\n\t" // 1-2  if(b & 128)
                     "mov  %[next] , %[hi]"
                     "\n\t" // 0-1   next = hi    (NeoPixelType =  4)
                     "rjmp .+0"
                     "\n\t" // 2    nop nop       (NeoPixelType =  6)
                     "rjmp .+0"
                     "\n\t" // 2    nop nop       (NeoPixelType =  8)
                     "st   %a[port], %[next]"
                     "\n\t" // 2    PORT = next   (NeoPixelType = 10)
                     "rjmp .+0"
                     "\n\t" // 2    nop nop       (NeoPixelType = 12)
                     "rjmp .+0"
                     "\n\t" // 2    nop nop       (NeoPixelType = 14)
                     "rjmp .+0"
                     "\n\t" // 2    nop nop       (NeoPixelType = 16)
                     "rjmp .+0"
                     "\n\t" // 2    nop nop       (NeoPixelType = 18)
                     "rjmp .+0"
                     "\n\t" // 2    nop nop       (NeoPixelType = 20)
                     "st   %a[port], %[lo]"
                     "\n\t" // 2    PORT = lo     (NeoPixelType = 22)
                     "nop"
                     "\n\t" // 1    nop           (NeoPixelType = 23)
                     "mov  %[next] , %[lo]"
                     "\n\t" // 1    next = lo     (NeoPixelType = 24)
                     "dec  %[bit]"
                     "\n\t" // 1    bit--         (NeoPixelType = 25)
                     "breq nextbyte40"
                     "\n\t" // 1-2  if(bit == 0)
                     "rol  %[byte]"
                     "\n\t" // 1    b <<= 1       (NeoPixelType = 27)
                     "nop"
                     "\n\t" // 1    nop           (NeoPixelType = 28)
                     "rjmp .+0"
                     "\n\t" // 2    nop nop       (NeoPixelType = 30)
                     "rjmp .+0"
                     "\n\t" // 2    nop nop       (NeoPixelType = 32)
                     "rjmp .+0"
                     "\n\t" // 2    nop nop       (NeoPixelType = 34)
                     "rjmp .+0"
                     "\n\t" // 2    nop nop       (NeoPixelType = 36)
                     "rjmp .+0"
                     "\n\t" // 2    nop nop       (NeoPixelType = 38)
                     "rjmp head40"
                     "\n\t" // 2    -> head40 (next bit out)
                     "nextbyte40:"
                     "\n\t" //                    (NeoPixelType = 27)
                     "ldi  %[bit]  , 8"
                     "\n\t" // 1    bit = 8       (NeoPixelType = 28)
                     "ld   %[byte] , %a[ptr]+"
                     "\n\t" // 2    b = *ptr++    (NeoPixelType = 30)
                     "rjmp .+0"
                     "\n\t" // 2    nop nop       (NeoPixelType = 32)
                     "st   %a[port], %[lo]"
                     "\n\t" // 2    PORT = lo     (NeoPixelType = 34)
                     "rjmp .+0"
                     "\n\t" // 2    nop nop       (NeoPixelType = 36)
                     "sbiw %[count], 1"
                     "\n\t" // 2    i--           (NeoPixelType = 38)
                     "brne head40"
                     "\n" // 1-2  if(i != 0) -> (next byte)
                : [port] "+e"(portOut), [byte] "+r"(b), [bit] "+r"(bit),
        [next] "+r"(next), [count] "+w"(i)
        : [ptr] "e"(ptr), [hi] "r"(hi), [lo] "r"(lo));
      }
#endif // NEO_KHZ400

#else
#error "CPU SPEED NOT SUPPORTED"
#endif // end F_CPU ifdefs on __AVR__

      // END AVR ----------------------------------------------------------------

      endTime = micros(); // Save EOD time for latch on next call
    }

    void setPixelColor(uint16_t n, uint8_t r, uint8_t g, uint8_t b) {
      if (n < numLEDs) {
        if (brightness) { // See notes in setBrightness()
          r = (r * brightness) >> 8;
          g = (g * brightness) >> 8;
          b = (b * brightness) >> 8;
        }
        uint8_t *p;
        if (wOffset == rOffset) { // Is an RGB-type strip
          p = &pixels[n * 3];     // 3 bytes per pixel
        } else {                  // Is a WRGB-type strip
          p = &pixels[n * 4];     // 4 bytes per pixel
          p[wOffset] = 0;         // But only R,G,B passed -- set W to 0
        }
        p[rOffset] = r; // R,G,B always stored
        p[gOffset] = g;
        p[bOffset] = b;
      }
    }

    void setPixelColor(uint16_t n, uint8_t r, uint8_t g, uint8_t b, uint8_t w) {
      if (n < numLEDs) {
        if (brightness) { // See notes in setBrightness()
          r = (r * brightness) >> 8;
          g = (g * brightness) >> 8;
          b = (b * brightness) >> 8;
          w = (w * brightness) >> 8;
        }
        uint8_t *p;
        if (wOffset == rOffset) { // Is an RGB-type strip
          p = &pixels[n * 3];     // 3 bytes per pixel (ignore W)
        } else {                  // Is a WRGB-type strip
          p = &pixels[n * 4];     // 4 bytes per pixel
          p[wOffset] = w;         // Store W
        }
        p[rOffset] = r; // Store R,G,B
        p[gOffset] = g;
        p[bOffset] = b;
      }
    }

    void setPixelColor(uint16_t n, uint32_t c) {
      if (n < numLEDs) {
        uint8_t *p, r = (uint8_t) (c >> 16), g = (uint8_t) (c >> 8), b = (uint8_t) c;
        if (brightness) { // See notes in setBrightness()
          r = (r * brightness) >> 8;
          g = (g * brightness) >> 8;
          b = (b * brightness) >> 8;
        }
        if (wOffset == rOffset) {
          p = &pixels[n * 3];
        } else {
          p = &pixels[n * 4];
          uint8_t w = (uint8_t) (c >> 24);
          p[wOffset] = brightness ? ((w * brightness) >> 8) : w;
        }
        p[rOffset] = r;
        p[gOffset] = g;
        p[bOffset] = b;
      }
    }

    void fill(uint32_t c = 0, uint16_t first = 0, uint16_t count = 0) {
      uint16_t i, end;

      if (first >= numLEDs) {
        return; // If first LED is past end of strip, nothing to do
      }

      // Calculate the index ONE AFTER the last pixel to fill
      if (count == 0) {
        // Fill to end of strip
        end = numLEDs;
      } else {
        // Ensure that the loop won't go past the last pixel
        end = first + count;
        if (end > numLEDs)
          end = numLEDs;
      }

      for (i = first; i < end; i++) {
        this->setPixelColor(i, c);
      }
    }

    void setBrightness(uint8_t b) {
      // Stored brightness value is different than what's passed.
      // This simplifies the actual scaling math later, allowing a fast
      // 8x8-bit multiply and taking the MSB. 'brightness' is a uint8_t,
      // adding 1 here may (intentionally) roll over...so 0 = max brightness
      // (color values are interpreted literally; no scaling), 1 = min
      // brightness (off), 255 = just below max brightness.
      uint8_t newBrightness = b + 1;
      if (newBrightness != brightness) { // Compare against prior value
        // Brightness has changed -- re-scale existing data in RAM,
        // This process is potentially "lossy," especially when increasing
        // brightness. The tight timing in the WS2811/WS2812 code means there
        // aren't enough free cycles to perform this scaling on the fly as data
        // is issued. So we make a pass through the existing color data in RAM
        // and scale it (subsequent graphics commands also work at this
        // brightness level). If there's a significant step up in brightness,
        // the limited number of steps (quantization) in the old data will be
        // quite visible in the re-scaled version. For a non-destructive
        // change, you'll need to re-render the full strip data. C'est la vie.
        uint8_t c, *ptr = pixels,
                oldBrightness = brightness - 1; // De-wrap old brightness value
        uint16_t scale;
        if (oldBrightness == 0)
          scale = 0; // Avoid /0
        else if (b == 255)
          scale = 65535 / oldBrightness;
        else
          scale = (((uint16_t) newBrightness << 8) - 1) / oldBrightness;
        for (uint16_t i = 0; i < numBytes; i++) {
          c = *ptr;
          *ptr++ = (c * scale) >> 8;
        }
        brightness = newBrightness;
      }
    }

    void clear(void) { memset(pixels, 0, numBytes); }


    /*!
      @brief   Check whether a call to show() will start sending data
               immediately or will 'block' for a required interval. NeoPixels
               require a short quiet time (about 300 microseconds) after the
               last bit is received before the data 'latches' and new data can
               start being received. Usually one's sketch is implicitly using
               this time to generate a new frame of animation...but if it
               finishes very quickly, this function could be used to see if
               there's some idle time available for some low-priority
               concurrent task.
      @return  1 or true if show() will start sending immediately, 0 or false
               if show() would block (meaning some idle time is available).
    */
    bool canShow(void) {
      // It's normal and possible for endTime to exceed micros() if the
      // 32-bit clock counter has rolled over (about every 70 minutes).
      // Since both are uint32_t, a negative delta correctly maps back to
      // positive space, and it would seem like the subtraction below would
      // suffice. But a problem arises if code invokes show() very
      // infrequently...the micros() counter may roll over MULTIPLE times in
      // that interval, the delta calculation is no longer correct and the
      // next update may stall for a very long time. The check below resets
      // the latch counter if a rollover has occurred. This can cause an
      // extra delay of up to 300 microseconds in the rare case where a
      // show() call happens precisely around the rollover, but that's
      // neither likely nor especially harmful, vs. other code that might
      // stall for 30+ minutes, or having to document and frequently remind
      // and/or provide tech support explaining an unintuitive need for
      // show() calls at least once an hour.
      uint32_t now = micros();
      if (endTime > now) {
        endTime = now;
      }
      return (now - endTime) >= 300L;
    }


    uint8_t getBrightness(void) const { return brightness - 1; }

    /*!
      @brief   Retrieve the pin number used for NeoPixel data output.
      @return  Arduino pin number (-1 if not set).
    */
    int16_t getPin(void) const { return pin; };

    /*!
      @brief   Return the number of pixels in an NeoPisell strip object.
      @return  Pixel count (0 if not set).
    */
    uint16_t numPixels(void) const { return numLEDs; }

    uint32_t getPixelColor(uint16_t n) const {
      if (n >= numLEDs)
        return 0; // Out of bounds, return no color.

      uint8_t *p;

      if (wOffset == rOffset) { // Is RGB-type device
        p = &pixels[n * 3];
        if (brightness) {
          // Stored color was decimated by setBrightness(). Returned value
          // attempts to scale back to an approximation of the original 24-bit
          // value used when setting the pixel color, but there will always be
          // some error -- those bits are simply gone. Issue is most
          // pronounced at low brightness levels.
          return (static_cast<uint32_t>((p[rOffset] << 8) / brightness) << 16) |
                 (static_cast<uint32_t>((p[gOffset] << 8) / brightness) << 8) |
                 static_cast<uint32_t>((p[bOffset] << 8) / brightness);
        } else {
          // No brightness adjustment has been made -- return 'raw' color
          return static_cast<uint32_t>(p[rOffset] << 16) | static_cast<uint32_t>(p[gOffset] << 8) |
                 static_cast<uint32_t>(p[bOffset]);
        }
      } else { // Is RGBW-type device
        p = &pixels[n * 4];
        if (brightness) { // Return scaled color
          return (static_cast<uint32_t>((p[wOffset] << 8) / brightness) << 24) |
                 (static_cast<uint32_t>((p[rOffset] << 8) / brightness) << 16) |
                 (static_cast<uint32_t>((p[gOffset] << 8) / brightness) << 8) |
                 static_cast<uint32_t>((p[bOffset] << 8) / brightness);
        } else { // Return raw color
          return static_cast<uint32_t>(p[wOffset] << 24) | static_cast<uint32_t>(p[rOffset] << 16) |
                 static_cast<uint32_t>(p[gOffset] << 8) | static_cast<uint32_t>(p[bOffset]);
        }
      }
    }

    /*!
      @brief   An 8-bit integer sine wave function, not directly compatible
               with standard trigonometric units like radians or degrees.
      @param   x  Input angle, 0-255; 256 would loop back to zero, completing
                  the circle (equivalent to 360 degrees or 2 pi radians).
                  One can therefore use an unsigned 8-bit variable and simply
                  add or subtract, allowing it to overflow/underflow and it
                  still does the expected contiguous thing.
      @return  Sine result, 0 to 255, or -128 to +127 if type-converted to
               a signed int8_t, but you'll most likely want unsigned as this
               output is often used for pixel brightness in animation effects.
    */
    static uint8_t sine8(uint8_t x) {
      return pgm_read_byte(&_NeoPixelSineTable[x]); // 0-255 in, 0-255 out
    }

    /*!
      @brief   An 8-bit gamma-correction function for basic pixel brightness
               adjustment. Makes color transitions appear more perceptially
               correct.
      @param   x  Input brightness, 0 (minimum or off/black) to 255 (maximum).
      @return  Gamma-adjusted brightness, can then be passed to one of the
               setPixelColor() functions. This uses a fixed gamma correction
               exponent of 2.6, which seems reasonably okay for average
               NeoPixels in average tasks. If you need finer control you'll
               need to provide your own gamma-correction function instead.
    */
    static uint8_t gamma8(uint8_t x) {
      return pgm_read_byte(&_NeoPixelGammaTable[x]); // 0-255 in, 0-255 out
    }

    /*!
      @brief   Convert separate red, green and blue values into a single
               "packed" 32-bit RGB color.
      @param   r  Red brightness, 0 to 255.
      @param   g  Green brightness, 0 to 255.
      @param   b  Blue brightness, 0 to 255.
      @return  32-bit packed RGB value, which can then be assigned to a
               variable for later use or passed to the setPixelColor()
               function. Packed RGB format is predictable, regardless of
               LED strand color order.
    */
    static uint32_t Color(uint8_t r, uint8_t g, uint8_t b) {
      return static_cast<uint32_t>(r << 16) | static_cast<uint32_t>(g << 8) | b;
    }

    /*!
      @brief   Convert separate red, green, blue and white values into a
               single "packed" 32-bit WRGB color.
      @param   r  Red brightness, 0 to 255.
      @param   g  Green brightness, 0 to 255.
      @param   b  Blue brightness, 0 to 255.
      @param   w  White brightness, 0 to 255.
      @return  32-bit packed WRGB value, which can then be assigned to a
               variable for later use or passed to the setPixelColor()
               function. Packed WRGB format is predictable, regardless of
               LED strand color order.
    */
    static uint32_t Color(uint8_t r, uint8_t g, uint8_t b, uint8_t w) {
      return static_cast<uint32_t>(w << 24) | static_cast<uint32_t>(r << 16) | static_cast<uint32_t>(g << 8) | b;
    }

    static uint32_t ColorHSV(uint16_t hue, uint8_t sat = 255, uint8_t val = 255) {

      uint8_t r, g, b;

      // Remap 0-65535 to 0-1529. Pure red is CENTERED on the 64K rollover;
      // 0 is not the start of pure red, but the midpoint...a few values above
      // zero and a few below 65536 all yield pure red (similarly, 32768 is the
      // midpoint, not start, of pure cyan). The 8-bit RGB hexcone (256 values
      // each for red, green, blue) really only allows for 1530 distinct hues
      // (not 1536, more on that below), but the full unsigned 16-bit type was
      // chosen for hue so that one's code can easily handle a contiguous color
      // wheel by allowing hue to roll over in either direction.
      hue = (hue * 1530L + 32768) / 65536;
      // Because red is centered on the rollover point (the +32768 above,
      // essentially a fixed-point +0.5), the above actually yields 0 to 1530,
      // where 0 and 1530 would yield the same thing. Rather than apply a
      // costly modulo operator, 1530 is handled as a special case below.

      // So you'd think that the color "hexcone" (the thing that ramps from
      // pure red, to pure yellow, to pure green and so forth back to red,
      // yielding six slices), and with each color component having 256
      // possible values (0-255), might have 1536 possible items (6*256),
      // but in reality there's 1530. This is because the last element in
      // each 256-element slice is equal to the first element of the next
      // slice, and keeping those in there this would create small
      // discontinuities in the color wheel. So the last element of each
      // slice is dropped...we regard only elements 0-254, with item 255
      // being picked up as element 0 of the next slice. Like this:
      // Red to not-quite-pure-yellow is:        255,   0, 0 to 255, 254,   0
      // Pure yellow to not-quite-pure-green is: 255, 255, 0 to   1, 255,   0
      // Pure green to not-quite-pure-cyan is:     0, 255, 0 to   0, 255, 254
      // and so forth. Hence, 1530 distinct hues (0 to 1529), and hence why
      // the constants below are not the multiples of 256 you might expect.

      // Convert hue to R,G,B (nested ifs faster than divide+mod+switch):
      if (hue < 510) { // Red to Green-1
        b = 0;
        if (hue < 255) { //   Red to Yellow-1
          r = 255;
          g = hue;       //     g = 0 to 254
        } else {         //   Yellow to Green-1
          r = 510 - hue; //     r = 255 to 1
          g = 255;
        }
      } else if (hue < 1020) { // Green to Blue-1
        r = 0;
        if (hue < 765) { //   Green to Cyan-1
          g = 255;
          b = hue - 510;  //     b = 0 to 254
        } else {          //   Cyan to Blue-1
          g = 1020 - hue; //     g = 255 to 1
          b = 255;
        }
      } else if (hue < 1530) { // Blue to Red-1
        g = 0;
        if (hue < 1275) { //   Blue to Magenta-1
          r = hue - 1020; //     r = 0 to 254
          b = 255;
        } else { //   Magenta to Red-1
          r = 255;
          b = 1530 - hue; //     b = 255 to 1
        }
      } else { // Last 0.5 Red (quicker than % operator)
        r = 255;
        g = b = 0;
      }

      // Apply saturation and value to R,G,B, pack into 32-bit result:
      uint32_t v1 = 1 + val;  // 1 to 256; allows >>8 instead of /255
      uint16_t s1 = 1 + sat;  // 1 to 256; same reason
      uint8_t s2 = 255 - sat; // 255 to 0
      return ((((((r * s1) >> 8) + s2) * v1) & 0xff00) << 8) |
             (((((g * s1) >> 8) + s2) * v1) & 0xff00) |
             (((((b * s1) >> 8) + s2) * v1) >> 8);
    }

    /*!
      @brief   A gamma-correction function for 32-bit packed RGB or WRGB
               colors. Makes color transitions appear more perceptially
               correct.
      @param   x  32-bit packed RGB or WRGB color.
      @return  Gamma-adjusted packed color, can then be passed in one of the
               setPixelColor() functions. Like gamma8(), this uses a fixed
               gamma correction exponent of 2.6, which seems reasonably okay
               for average NeoPixels in average tasks. If you need finer
               control you'll need to provide your own gamma-correction
               function instead.
    */
    static uint32_t gamma32(uint32_t x) {
      uint8_t *y = (uint8_t *) &x;
      // All four bytes of a 32-bit value are filtered even if RGB (not WRGB),
      // to avoid a bunch of shifting and masking that would be necessary for
      // properly handling different endianisms (and each byte is a fairly
      // trivial operation, so it might not even be wasting cycles vs a check
      // and branch for the RGB case). In theory this might cause trouble *if*
      // someone's storing information in the unused most significant byte
      // of an RGB value, but this seems exceedingly rare and if it's
      // encountered in reality they can mask values going in or coming out.
      for (uint8_t i = 0; i < 4; i++)
        y[i] = gamma8(y[i]);
      return x; // Packed 32-bit return
    }

    void rainbow(uint16_t first_hue = 0, int8_t reps = 1,
                 uint8_t saturation = 255, uint8_t brightness = 255,
                 bool gammify = true) {
      for (uint16_t i = 0; i < numLEDs; i++) {
        uint16_t hue = first_hue + (i * reps * 65536) / numLEDs;
        uint32_t color = ColorHSV(hue, saturation, brightness);
        if (gammify) color = gamma32(color);
        setPixelColor(i, color);
      }
    }

    static neopixel_t str2order(const char *v) {
      int8_t r = 0, g = 0, b = 0, w = -1;
      if (v) {
        char c;
        for (uint8_t i = 0; ((c = tolower(v[i]))); i++) {
          if (c == 'r') r = i;
          else if (c == 'g') g = i;
          else if (c == 'b') b = i;
          else if (c == 'w') w = i;
        }
        r &= 3;
      }
      if (w < 0) w = r; // If 'w' not specified, duplicate r bits
      return (w << 6) | (r << 4) | ((g & 3) << 2) | (b & 3);
    }


};

#endif // ADAFRUIT_NEOPIXEL_H
