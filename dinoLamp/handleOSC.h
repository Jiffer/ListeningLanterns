#include <Adafruit_NeoPixel.h>

// LED Strip constants
// NeoPixel stuff:
#define PIN            13
#define NUMPIXELS     30
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

LEDStrip* lantern;

bool newData = false;
bool gotColor = false;

// brightness lookup table
byte ledBrightness[256] = {
  0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
  1, 2, 2, 2, 2, 2, 2, 2, 2, 3, 3, 3, 3, 3, 4, 4,
  4, 4, 4, 5, 5, 5, 5, 6, 6, 6, 6, 7, 7, 7, 7, 8,
  8, 8, 9, 9, 9, 10, 10, 10, 11, 11, 12, 12, 12, 13, 13, 14,
  14, 15, 15, 15, 16, 16, 17, 17, 18, 18, 19, 19, 20, 20, 21, 22,
  22, 23, 23, 24, 25, 25, 26, 26, 27, 28, 28, 29, 30, 30, 31, 32,
  33, 33, 34, 35, 36, 36, 37, 38, 39, 40, 40, 41, 42, 43, 44, 45,
  46, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60,
  61, 62, 63, 64, 65, 67, 68, 69, 70, 71, 72, 73, 75, 76, 77, 78,
  80, 81, 82, 83, 85, 86, 87, 89, 90, 91, 93, 94, 95, 97, 98, 99,
  101, 102, 104, 105, 107, 108, 110, 111, 113, 114, 116, 117, 119, 121, 122, 124,
  125, 127, 129, 130, 132, 134, 135, 137, 139, 141, 142, 144, 146, 148, 150, 151,
  153, 155, 157, 159, 161, 163, 165, 166, 168, 170, 172, 174, 176, 178, 180, 182,
  184, 186, 189, 191, 193, 195, 197, 199, 201, 204, 206, 208, 210, 212, 215, 217,
  219, 221, 224, 226, 228, 231, 233, 235, 238, 240, 243, 245, 248, 250, 253, 255
};
double maxBrightness = 1;

int getBrightness(int value) {
  return (int) (maxBrightness * ledBrightness[value]);
}


void routeBrightness(OSCMessage &msg, int addrOffset) {
  //  Serial.print("got /brightness");

  float value = msg.getInt(0);
  lantern->brightness = getBrightness(value);
  //  Serial.println(value);
  newData = true;

}

void rgb(OSCMessage &msg, int addrOFFSET) {
  lantern->color[0] = msg.getInt(0); // come in between 0:100
  lantern->color[1] = msg.getInt(1);
  lantern->color[2] = msg.getInt(2);

  newData = true;
  gotColor = true;
}
