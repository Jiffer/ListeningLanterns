#ifdef ESP8266
#include <ESP8266WiFi.h>
#else
#include <WiFi.h>
#endif
#include <WiFiUdp.h>

#include <OSCBundle.h>
#include <OSCBoards.h>

#include <Adafruit_NeoPixel.h>

#include "handleOSC.h"

/*
  UDPReceiveOSC
  Set a tone according to incoming OSC control
                            Adrian Freed
*/


char ssid[] = "things";          // your network SSID (name)
char password[] = "Connected";                    // your network password

// A UDP instance to let us send and receive packets over UDP
WiFiUDP Udp;


const unsigned int outPort = 8888;          // remote port (not needed for receive)
const unsigned int localPort = 9999;        // local port to listen for UDP packets (here's where we send the packets)



void setup() {
  //setup ethernet part
  Serial.begin(115200);
  pixels.begin();

  // check flash content
  //  readFlashNumber();
  //  IPAddress ip(10, 0, 0, IPoffset); // my IP address (requested)
IPAddress ip(192, 168, 1, 212); // my IP address (requested)
IPAddress gateway(10, 0, 1, 1);
IPAddress subnet(255, 255, 255, 0);

  // Connect to WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  int i = 0;
  int state = true;
  WiFi.begin(ssid, password);
  //  WiFi.config();
  Serial.println("");
  Serial.println("Connecting to WiFi");

  // Wait for connection
  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    if (i > 10) {
      state = false;
      break;
    }
    i++;
  }

  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  Serial.println("Starting UDP");
  Udp.begin(localPort);
  Serial.print("Local port: ");
#ifdef ESP32
  Serial.println(localPort);
#else
  Serial.println(Udp.localPort());
#endif
//  WiFi.config(ip, gateway, subnet);
  Serial.println();
   Serial.print("MAC: ");
   Serial.println(WiFi.macAddress());

// startup sequence
  for (int i = 0; i < NUMPIXELS; i++) {
    pixels.setPixelColor(i, pixels.Color(getBrightness(150),getBrightness(150),getBrightness(10)));
    if(i >0){
      pixels.setPixelColor(i-1, pixels.Color(0,0,0));
    }
    pixels.show();
    delay(10);
  }
  pixels.setPixelColor(NUMPIXELS-1, pixels.Color(0,0,0));
  pixels.show();
  
}
//reads and dispatches the incoming message
void loop() {
  OSCBundle bundleIN;
  int size;

  if ( (size = Udp.parsePacket()) > 0)
  {
    while (size--)
      bundleIN.fill(Udp.read());

    if (!bundleIN.hasError()) {
      bundleIN.route("/int", routeInt);
      bundleIN.route("/float", routeFloat);
      bundleIN.route("/brightness", routeBrightness);
      bundleIN.route("/rgb", rgb);
      // set individual pixel, rgb
      // set animation modes
      // set delay time / rate
      // pew / cascade
      // sparkle / glow
    }
  }
}
