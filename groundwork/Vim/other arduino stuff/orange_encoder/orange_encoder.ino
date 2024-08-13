#include <ros.h>
#include <std_msgs/Int32.h>

ros::NodeHandle nh;

std_msgs::Int32 msg;
ros::Publisher pub("Orange_enc", &msg);

volatile unsigned int temp, counter = 0; //This variable will increase or decrease depending on the rotation of encoder
void setup() {

  nh.initNode();
  nh.advertise(pub);
  // Serial.begin (115200);
  pinMode(27, INPUT_PULLUP); // internal pullup input pin 2
  pinMode(5, INPUT_PULLUP); // internalเป็น pullup input pin 3
  //Setting up interrupt
  //A rising pulse from encodenren activated ai0(). AttachInterrupt 0 is DigitalPin nr 2 on moust Arduino.
  attachInterrupt(digitalPinToInterrupt(27), ai0, RISING);
  //B rising pulse from encodenren activated ai1(). AttachInterrupt 1 is DigitalPin nr 3 on moust Arduino.
  attachInterrupt(digitalPinToInterrupt(5), ai1, RISING);
  }
  void loop() {
  // Send the value of counter
  if( counter != temp ){
  // Serial.println (counter);
  msg.data = counter;
  pub.publish(&msg);
  temp = counter;
  }
  }
  void ai0() {
  // ai0 is activated if DigitalPin nr 2 is going from LOW to HIGH
  // Check pin 3 to determine the direction
  if(digitalRead(5)==LOW) {
  counter++;
  }else{
  counter--;
  }
  }
  void ai1() {
  // ai0 is activated if DigitalPin nr 3 is going from LOW to HIGH
  // Check with pin 2 to determine the direction
  if(digitalRead(27)==LOW) {
  counter--;
  }else{
  counter++;
  }
  }





