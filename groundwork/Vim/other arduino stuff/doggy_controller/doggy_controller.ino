// #include <ArduinoHardware.h>
#include <Cytron_SmartDriveDuo.h>
#define BLYNK_USE_DIRECT_CONNECT
// You could use a spare Hardware Serial on boards that have it (like Mega)
#include <SoftwareSerial.h>
SoftwareSerial DebugSerial(2, 3); // RX, TX
#define BLYNK_PRINT DebugSerial
#include <BlynkSimpleSerialBLE.h>
// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "WRw0imnuy0DwfpZm_D2OpKx2qX3pRF47";
// Cytron config
#define IN1 6
#define BAUDRATE 115200
Cytron_SmartDriveDuo smartDriveDuo30(SERIAL_SIMPLIFIED, IN1, BAUDRATE);
 float right_wheel=0;
 float left_wheel=0;
 float linear=0;
 float angular=0;
BLYNK_WRITE(V1)
{
  int angular = param[0].asInt(); // assigning incoming value from pin V1 to a variable
  int linear = param[1].asInt();
  right_wheel = (linear + angular) * 100;
  left_wheel = (linear - angular) * 100;
  // process received value
}
void setup()
{
  // Debug console
  DebugSerial.begin(9600);
  // Blynk will work through Serial
  // 9600 is for HC-06. For HC-05 default speed is 38400
  // Do not read or write this serial manually in your sketch
  Serial.begin(9600);
  Blynk.begin(Serial, auth);
}
void loop()
{
  smartDriveDuo30.control(right_wheel,left_wheel);
  Blynk.run();
}