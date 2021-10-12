

class LEDStrip {

    unsigned long pushTimer = 0;
    int pushInterval = 10;

  public:
    int pushPointer = 0;
    int raisePointer = 0;
    int nPixels;
    int pixelArray[30][3];
    int brightness;
    int color[3];
    bool animating = true;
    bool raise = true;


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

    void raisePixel() {
      int otherSide = 15 + raisePointer;
      
      pixelArray[otherSide][0] = getColor(0);
      pixelArray[raisePointer][0] = getColor(0);

      pixelArray[otherSide][1] = getColor(1);
      pixelArray[raisePointer][1] = getColor(1);
      pixelArray[otherSide][2] = getColor(2);
      pixelArray[raisePointer++][2] = getColor(2);

      if(raisePointer > 14){
        raisePointer = 0;
      }
      pushPointer = raisePointer;

    }

    void animate() {
      // if pixelPusher
      // check if its time to update
      if (millis() > pushTimer) {
        pushTimer = millis() + pushInterval;
        if(raise){
          raisePixel();
        }else{
          pushPixel();
        }

      }
    }
};
