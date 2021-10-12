

class LEDStrip {
  int pushPointer = 0;
  
  unsigned long pushTimer = 0;
  int pushInterval = 50;
  
  public:
    int nPixels;
    int pixelArray[30][3];
    int brightness;
    int color[3];
    bool animation = true;
    

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


    int getColor(int address){
      return color[address]*brightness*0.01;
    }

    void push(){
      
    }

    void animate(){
      
    }
};
