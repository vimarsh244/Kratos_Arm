#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>


#include <ros.h>
#include <std_msgs/Float32MultiArray.h>

ros::NodeHandle nh;
std_msgs::Float32MultiArray sensor_data;

ros::Publisher sensor_data_pub("ld_sensor_data", &sensor_data);

#define SEALEVELPRESSURE_HPA (1013.25)

Adafruit_BME280 bme; // I2C

#include "SparkFun_SCD4x_Arduino_Library.h" //Click here to get the library: http://librarymanager/All#SparkFun_SCD4x
SCD4x SCD4xSensor;

#include "MutichannelGasSensor.h"



unsigned long delayTime;

void setup() {
  nh.initNode();
  unsigned status;
    
  // default settings
  status = bme.begin();  
  

  nh.advertise(sensor_data_pub);

  if (SCD4xSensor.begin() == false)
  {
    nh.logerror("scd4x sensor initialization failed...");
  }

  // multichannel gas sensor:
    gas.begin(0x04);//the default I2C address of the slave is 0x04
    gas.powerOn();


  nh.logerror("bme status : ");
  // nh.logerror(status);
  delayTime = 1000; // Initial delay for the first publish
}

float sensor_data_raw[6];


//Sensor Data Message format:
/*
0 = CO
1 = CH4
2 = CO2
3 = Temp
4 = Humidity
5 = Air Pressure
 = 
*/


void read_data(){

  sensor_data_raw[0]=gas.measure_CO();
  sensor_data_raw[1]=gas.measure_CH4();

  sensor_data_raw[2] = SCD4xSensor.getCO2();
  
  float temp = (SCD4xSensor.getTemperature() + bme.readTemperature())/2;
  sensor_data_raw[3] = temp;
  temp = (SCD4xSensor.getHumidity()+bme.readHumidity())/2;
  sensor_data_raw[4] = temp; // same here
  sensor_data_raw[5] = (bme.readPressure()); // will give value in  hPa with 2 decimal places so again divide by 100
  
  
}

void loop() {
  
  read_data();
  // char* to_send = "sensor data: "+sensor_data_raw[4];
  // nh.logerror(to_send);
    sensor_data.data = sensor_data_raw;
    // int test[] = {1,2,3};
    // sensor_data.data = test;
    sensor_data.data_length = 6;
  sensor_data_pub.publish(&sensor_data);

  nh.spinOnce();
  delay(delayTime);
}

