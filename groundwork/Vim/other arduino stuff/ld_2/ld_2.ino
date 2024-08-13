#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>

#include <ros.h>
#include <std_msgs/Int16.h>
#include <std_msgs/Float32.h>

ros::NodeHandle nh;
std_msgs::Int16 analog_msg;
std_msgs::Float32 analog_msg_2;

ros::Publisher analog_pub_1("sensor_mq4", &analog_msg);
ros::Publisher analog_pub_2("sensor_mq7", &analog_msg);
ros::Publisher analog_pub_3("sensor_mq7_2", &analog_msg);

ros::Publisher bme280_temp("bme280_temp", &analog_msg_2);
ros::Publisher bme280_humidity("bme280_humidity", &analog_msg_2);
ros::Publisher bme280_pressure("bme280_pressure", &analog_msg_2);


#define SEALEVELPRESSURE_HPA (1013.25)

Adafruit_BME280 bme; // I2C

unsigned long delayTime;


const int analogPin = A0;
void setup() {
  nh.initNode();
  unsigned status;
    
    // default settings
    status = bme.begin();  

  nh.advertise(analog_pub_1);  nh.advertise(analog_pub_2);
  nh.advertise(analog_pub_3);
  nh.advertise(bme280_temp);  nh.advertise(bme280_humidity);
  nh.advertise(bme280_pressure);


}
void loop() {
  analog_msg.data = analogRead(analogPin);
  analog_pub_1.publish(&analog_msg);
  analog_msg.data = analogRead(A1);
  analog_pub_2.publish(&analog_msg);
  analog_msg.data = analogRead(A2);
  analog_pub_3.publish(&analog_msg);

  analog_msg_2.data = bme.readTemperature();
  bme280_temp.publish(&analog_msg_2);
    analog_msg_2.data = bme.readPressure() / 100.0F;

  bme280_pressure.publish(&analog_msg_2);
    analog_msg_2.data = bme.readHumidity();

  bme280_humidity.publish(&analog_msg_2);


  nh.spinOnce();
  delay(1000); // Publish every second
}





