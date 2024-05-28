#include <Adafruit_NeoPixel.h>

#define NEOPIXEL_PIN PIN_PC0
#define NEOPIXEL_COUNT 25
#define NEOPIXEL_BRIGHTNESS 0.1  // 0 <-> 1

namespace neoheart {
// variables used internally
Adafruit_NeoPixel pixels;
int numpixels, middlepixel;

// initialize leds
void initLeds() {
    pixels =
        Adafruit_NeoPixel(NEOPIXEL_COUNT, NEOPIXEL_PIN, NEO_GRB + NEO_KHZ800);
    pixels.begin();
    numpixels = pixels.numPixels();
    middlepixel = numpixels / 2;
}

// red green blue vars used for color generation
int r = 0, g = 0, b = 0;

// color array
struct Color {
    uint8_t r;
    uint8_t g;
    uint8_t b;
};

// animations colors
Color colors[] = {{0, 0, 255}, {144, 8, 255}, {255, 25, 221}, {255, 0, 0}, {255, 128, 0}, {255, 153, 0}, {8, 255, 0}, {28, 255, 142}, {31, 251, 255}, {25, 167, 255}, {115, 255, 117}};

void getRandomColor() {
    int numColors = 11;
    int index = random(numColors);
    r = colors[index].r;
    g = colors[index].g;
    b = colors[index].b;
}

void paintPixel(int pixel, float brightness) {
    pixels.setPixelColor(pixel,
                         pixels.Color(r * brightness * NEOPIXEL_BRIGHTNESS,
                                      g * brightness * NEOPIXEL_BRIGHTNESS,
                                      b * brightness * NEOPIXEL_BRIGHTNESS));
}

void turnOffPixel(int pixel) {
    pixels.setPixelColor(pixel, pixels.Color(0, 0, 0));
}

void clearStrip() {
    for (int i = 0; i < numpixels; i++) {
        turnOffPixel(i);
    }
    pixels.show();
}

void fadeOutStrip() {
    for (int j = 0; j < 8; j++) {
        for (int i = 0; i < numpixels; i++) {
            paintPixel(i, 1 - ((float)j / (float)10));
        }
        pixels.show();
        delay(20);
    }
}

void heartbeat() {
    r = 255;
    g = 0;
    b = 0;
    int animcounter = 0;
    while (animcounter < 3) {
        int fadeinouts = 0;
        while (fadeinouts < 2) {
            // fade in
            for (int j = 1; j < NEOPIXEL_COUNT; j++) {
                for (int i = 0; i < NEOPIXEL_COUNT; i++)
                    paintPixel(i, ((float)j / (float)NEOPIXEL_COUNT));
                pixels.show();
                delay(2);
            }
            // fade out
            for (int j = NEOPIXEL_COUNT; j > 0; j--) {
                for (int i = 0; i < NEOPIXEL_COUNT; i++)
                    paintPixel(i, ((float)j / (float)NEOPIXEL_COUNT));
                pixels.show();
                delay(2);
            }
            fadeinouts++;
        }
        clearStrip();
        delay(500);
        animcounter++;
    }
}

void bottomup() {
    getRandomColor();
    int animcounter = 0;
    while (animcounter < 3) {
        for (int i = 0; i <= numpixels / 2; i++) {
            turnOffPixel(middlepixel + i - 3);
            paintPixel(middlepixel + i - 2, 0.2);
            paintPixel(middlepixel + i - 1, 0.5);
            paintPixel(middlepixel + i, 1);
            turnOffPixel(middlepixel - i + 3);
            paintPixel(middlepixel - i + 2, 0.2);
            paintPixel(middlepixel - i + 1, 0.5);
            paintPixel(middlepixel - i, 1);
            pixels.show();
            delay(30);
        }
        for (int i = 0; i <= numpixels / 2; i++) {
            turnOffPixel(i - 3);
            paintPixel(i - 2, 0.2);
            paintPixel(i - 1, 0.5);
            paintPixel(i, 1);
            turnOffPixel(numpixels - i + 3);
            paintPixel(numpixels - i + 2, 0.2);
            paintPixel(numpixels - i + 1, 0.5);
            paintPixel(numpixels - i, 1);
            pixels.show();
            delay(30);
        }
        clearStrip();
        delay(500);
        animcounter++;
    }
}

void bottomupsingle() {
    getRandomColor();
    int randpixel = 0;
    int animcounter = 0;
    while (animcounter < 2) {
        int affectedpixels[numpixels];
        for (int i = 0; i < numpixels; i++) {
            bool duplicate = false;
            do {
                randpixel = random(0, numpixels);
                bool found = false;
                for (int x = 0; x < numpixels; x++) {
                    if (randpixel == affectedpixels[x]) {
                        found = true;
                        break;
                    }
                }
                duplicate = found;
            } while (duplicate);
            if (animcounter == 0)
                paintPixel(randpixel, 1);
            else
                turnOffPixel(randpixel);
            pixels.show();
            affectedpixels[i] = randpixel;
            delay(60);
        }
        delay(500);
        memset(affectedpixels, 99, sizeof(affectedpixels));
        animcounter++;
    }
    clearStrip();
}

void theatherFill() {
    getRandomColor();
    for (int i = 0; i < numpixels; i++) {
        if (i % 2 == 0) {
            paintPixel(i, 1);
            pixels.show();
            delay(80);
        }
    }
    for (int i = numpixels; i > 0; i--) {
        if (i % 2 == 1) {
            paintPixel(i, 1);
            pixels.show();
            delay(80);
        }
    }
    delay(200);
    int animcounter = 0;
    while (animcounter < 3) {
        for (int j = 0; j < 10; j++) {
            for (int i = 0; i < numpixels; i++) {
                paintPixel(i, 1 - ((float)j / (float)10));
            }
            pixels.show();
            delay(10);
        }
        delay(100);
        for (int j = 0; j < 10; j++) {
            for (int i = 0; i < numpixels; i++) {
                paintPixel(i, (float)j / (float)10);
            }
            pixels.show();
            delay(10);
        }
        delay(100);
        animcounter++;
    }
    delay(200);
    fadeOutStrip();
    clearStrip();
}

void bounce() {
    getRandomColor();
    int trips = 1;
    while (trips < numpixels + 1) {
        for (int i = 0; i < numpixels; i++) {
            paintPixel(i, 1);
            turnOffPixel(i - trips);
            pixels.show();
            delay((numpixels - trips) * (1 / ((float)trips / 4)));
        }
        trips++;
        for (int i = numpixels; i > -1; i--) {
            paintPixel(i, 1);
            turnOffPixel(i + trips);
            pixels.show();
            delay((numpixels - trips) * (1 / ((float)trips / 4)));
        }
        trips++;
    }
    delay(1000);
    fadeOutStrip();
    clearStrip();
}

void incrementalFill() {
    getRandomColor();
    for (int j = 0; j <= numpixels / 2; j++) {
        for (int i = 0; i <= numpixels / 2; i++) {
            paintPixel(middlepixel - i, 1);
            if ((numpixels / 2) - i > j) turnOffPixel(middlepixel - i + 1);
            pixels.show();
            delay(10);
        }
        for (int i = 0; i <= numpixels / 2; i++) {
            paintPixel(middlepixel + i, 1);
            if (i < (numpixels / 2) - j) turnOffPixel(middlepixel + i - 1);
            pixels.show();
            delay(10);
        }
    }
    delay(500);
    fadeOutStrip();
    clearStrip();
}

void chase() {
    getRandomColor();
    int p = 0;
    int currentPixel;
    for (int i = 0; i < (numpixels * 3) + 1; i++) {
        currentPixel = i % numpixels;
        p = currentPixel - 5 >= 0 ? currentPixel - 5 : (currentPixel - 5) + numpixels;
        turnOffPixel(p);
        p = currentPixel - 4 >= 0 ? currentPixel - 4 : (currentPixel - 4) + numpixels;
        paintPixel(p, 0.1);
        p = currentPixel - 3 >= 0 ? currentPixel - 3 : (currentPixel - 3) + numpixels;
        paintPixel(p, 0.2);
        p = currentPixel - 2 >= 0 ? currentPixel - 2 : (currentPixel - 2) + numpixels;
        paintPixel(p, 0.4);
        p = currentPixel - 1 >= 0 ? currentPixel - 1 : (currentPixel - 1) + numpixels;
        paintPixel(p, 0.6);
        paintPixel(currentPixel, 1);
        pixels.show();
        delay(40);
    }
    clearStrip();
}

void colorWipeColor(uint32_t color, int wait) {
    for (int i = 0; i < pixels.numPixels(); i++) {
        pixels.setPixelColor(i, color);
        pixels.show();
        delay(wait);
    }
}

void colorWipe() {
    pixels.setBrightness(255 / (1 / NEOPIXEL_BRIGHTNESS));
    colorWipeColor(pixels.Color(255, 0, 0), 50);
    colorWipeColor(pixels.Color(0, 255, 0), 50);
    colorWipeColor(pixels.Color(0, 0, 255), 50);
    clearStrip();
}

void rainbow() {
    pixels.setBrightness(255 / (1 / NEOPIXEL_BRIGHTNESS));
    for (long firstPixelHue = 0; firstPixelHue < 5 * 65536; firstPixelHue += 256) {
        pixels.rainbow(firstPixelHue);
        pixels.show();
        delay(5);
    }
    clearStrip();
}

void theaterChaseRainbow() {
    pixels.setBrightness(255 / (1 / NEOPIXEL_BRIGHTNESS));
    int firstPixelHue = 0;
    for (int a = 0; a < 30; a++) {
        for (int b = 0; b < 3; b++) {
            pixels.clear();
            for (int c = b; c < pixels.numPixels(); c += 3) {
                int hue = firstPixelHue + c * 65536L / pixels.numPixels();
                uint32_t color = pixels.gamma32(pixels.ColorHSV(hue));
                pixels.setPixelColor(c, color);
            }
            pixels.show();
            delay(100);
            firstPixelHue += 65536 / 15;
        }
    }
    clearStrip();
}
}  // namespace neoheart
