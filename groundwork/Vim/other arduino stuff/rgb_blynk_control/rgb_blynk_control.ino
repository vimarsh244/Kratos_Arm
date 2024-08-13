
/* Comment this out to disable prints and save space */
#define BLYNK_PRINT Serial

#define BLYNK_TEMPLATE_ID           "TMPxxxxxx"
#define BLYNK_TEMPLATE_NAME         "Device"


/* Fill in information from Blynk Device Info here */
//#define BLYNK_TEMPLATE_ID           "TMPxxxxxx"
//#define BLYNK_TEMPLATE_NAME         "Device"
//#define BLYNK_AUTH_TOKEN            "YourAuthToken"


#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

#include <WiFiClient.h>
#include <Adafruit_NeoPixel.h>    // This library is used for controlling the RGB LED strip
#define PIN 5                    // Pin number
#define NUM 100                    // No of LEDs which is used in the strip
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUM,PIN, NEO_GRB + NEO_KHZ800);    // NeoPixel strip object 
char auth[] = "8u2gGT1Hxp6rIqB1S2K9Z5PuYkpRW71g";

char ssid[] = "Vimarsh";
char pass[] = "lol12345678";
int r,g,b,data;
void setup()
{
  Serial.begin(115200);
  Blynk.begin(auth, ssid, pass, "blynk-server.vimarsh.co", 80);
  pixels.begin();
}
void loop()
{
  Blynk.run();
}
// BLYNK_WRITE function is written to check for incoming data at V3 and V2 Virtual terminal, then assign them in three different variables. The variable r, g, b here represents the value of Red, Green, and Blue code of the selected color. Then these values are sent to the function static1 which is used for driving the LED strip.
BLYNK_WRITE(V2)
{
r = param[0].asInt();
g = param[1].asInt();
b = param[2].asInt();
if(data==0)
static1(r,g,b);
}
BLYNK_WRITE(V3)
{
data = param.asInt();
Serial.println(data);
if(data==0)
{
  static1(r,g,b);
}
else if(data==1)
{
  animation1();
}
}
// Static1 () function is used to drive the LED strip with distinct colors. Here, pixels.setPixelColor is used for driving the LED as per our required color.
void static1(int r, int g, int b)
{
  for(int i=0;i<=NUM;i++)
  {
  pixels.setPixelColor(i, pixels.Color(r,g,b));
  pixels.show();
  }
}
// Animation1() function is used to run a customized animation using LEDs. Different animations can be made as per the user's choice as shown below. 
void animation1()
{
  for(int i=0;i<NUM;i++)
  {
    pixels.setPixelColor(i, pixels.Color(255,0,0));
    pixels.show();
    delay(100);
  }
  for(int i=NUM;i>=0;i--)
  {
    pixels.setPixelColor(i, pixels.Color(0,255,0));
    pixels.show();
    delay(100);
  }
  for(int i=0;i<NUM;i++)
  {
    pixels.setPixelColor(i, pixels.Color(0,255,255));
    pixels.show();
    delay(100);
  }
  for(int i=NUM;i>=0;i--)
  {
    pixels.setPixelColor(i, pixels.Color(255,255,0));
    pixels.show();
    delay(100);
  }
}
