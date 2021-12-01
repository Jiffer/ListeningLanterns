

class LEDStrip {

    unsigned long pushTimer = 0;

  public:
    int pushPointer = 0;
    int raisePointer = 0;
    int nPixels;
    int pixelArray[30][3];
    int colorRange[3];
    int brightness;
    int color[3];
    bool newData = false;
    bool newBurst = false;
    int burstAmount = 1;
    int animateMode = 0;

    int pushInterval = 10;


    LEDStrip() {
    }

    LEDStrip(int NumPixels) {
      nPixels = NumPixels;
      brightness = 255;
      color[0] = 0; color[1] = 0; color[2] = 0;
    }

    void init() {
      for (int i = 0; i < nPixels; i++) {
        for (int j = 0; j < 3; j++) {
          pixelArray[i][j] = 0;
        }
      }
      colorRange[0] = 10; colorRange[1] = 10; colorRange[2] = 5;
    }


    int getColor(int address) {
      return color[address] * brightness * 0.01;
    }

    void pushPixel() {
      pixelArray[pushPointer][0] = getColor(0);
      pixelArray[pushPointer][1] = getColor(1);
      pixelArray[pushPointer--][2] = getColor(2);

      if (pushPointer < 0) {
        pushPointer = nPixels - 1;
      }
    }

    void glow() {
      
      for (int i = 0; i < nPixels; i++) {

        pixelArray[i][0] = pixelArray[i][0] + random(3) - 1;
        pixelArray[i][1] = pixelArray[i][1] + random(3) - 1;
        pixelArray[i][2] = pixelArray[i][2] + random(3) - 1;

        for (int j = 0; j < 3; j++) {
          if (pixelArray[i][j] > getColor(j) + colorRange[j]) {
            pixelArray[i][j] = getColor(j) + colorRange[j];
          } else if (pixelArray[i][j] < getColor(j) - colorRange[j]) {
            pixelArray[i][j] = getColor(j) - colorRange[j];
          }
          if (pixelArray[i][j] > 255) {
            pixelArray[i][j] = 255;
          } else if (pixelArray[i][j] < 0) {
            pixelArray[i][j] = 0;
          }
        }
      }
    }

    void burst() {
      if (newBurst) {
        // clear the flag
        newBurst = false;
        // turn burstAmount of lights on with randomized color range
        for (int i = 0; i < burstAmount; i++) {
          int randomPixel = random(nPixels);
          for (int j = 0; j < 3; j++) {
            pixelArray[randomPixel][j] = getColor(j) + random(colorRange[j]);
            if (pixelArray[randomPixel][j] > 100) {
              pixelArray[randomPixel][j] = 100;
            }
          }
        }
      }
      else {
        int randomPixel = random(nPixels);
        for (int j = 0; j < 3; j++) {
          pixelArray[randomPixel][j] = 0;
        }
      }
    }

    void raisePixel() {
      int otherSide = 15 + raisePointer;

      pixelArray[otherSide][0] = getColor(0);
      pixelArray[raisePointer][0] = getColor(0);

      pixelArray[otherSide][1] = getColor(1);
      pixelArray[raisePointer][1] = getColor(1);
      pixelArray[otherSide][2] = getColor(2);
      pixelArray[raisePointer++][2] = getColor(2);

      if (raisePointer > 14) {
        raisePointer = 0;
      }
      pushPointer = raisePointer;

    }

    void animate() {
      // if pixelPusher
      // check if its time to update
      if (millis() > pushTimer) {
        pushTimer = millis() + pushInterval;
        if (animateMode == 1) {
          raisePixel();
        } else if (animateMode == 2) {
          pushPixel();
        } else if (animateMode == 3) {
          glow();
        } else if (animateMode == 4) {
          burst();
        }
      }
    }
};
