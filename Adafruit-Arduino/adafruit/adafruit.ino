//thinger LIBRARIES
#include <SPI.h>
#include <ESP8266WiFi.h>       //ESP8266 WiFi connection library
#include <ThingerESP8266.h>    //THINGER.IO library

//DHT22 LIBRARIES
#include <DHT.h>
#include <DHT_U.h>
#include <Adafruit_Sensor.h>

//SERVO LIBRARIES
#include <Servo.h>

//dht functions and pins
#define DHTPIN 14
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

//led pins
#define LED1 13
#define LED2 12

//servo pins
#define servoPin 16
Servo servo1;

// Thinger.io connection parameters
#define user "xumengh"
#define device_Id "esp8266"
#define device_credentials "_wABmUBI012_&++E"
ThingerESP8266 thing(user, device_Id, device_credentials);

void setup() {
  Serial.begin(9600);

  //sensor control
  dht.begin();
  pinMode(DHTPIN, INPUT);

  //led control
  pinMode(LED1,OUTPUT);
  pinMode(LED2,OUTPUT);

  //servo control
  pinMode(servoPin, OUTPUT);
  servo1.attach(servoPin);
  servo1.write(90);
  
  // Setup WiFi
  thing.add_wifi("freeman", "cogeco388");
  // Define the 'thing' with a name and data direction

//    //LED1
//    thing["LED1"] << [](pson& in){
//      digitalWrite(LED1, in ? HIGH : LOW);
//    };
//
//    //LED2
//    thing["LED2"] << [](pson & in) {
//      digitalWrite(LED2, in ? HIGH : LOW); 
//    };

      thing["LED1"]<< digitalPin(LED1);
      thing["LED2"]<< digitalPin(LED2);

    //sensor 
//    thing["dht22"] >> [](pson& out){
//    // Add the values and the corresponding code
//      out["celsius"] = dht.readTemperature();
//      out["humidity"] = dht.readHumidity();
//    };

    thing["dhtTemp"] >> [](pson& out){
    // Add the values and the corresponding code
      out["celsius"] = dht.readTemperature();
    };

    thing["dhtHumi"] >> [](pson& out){
      out["humidity"] = dht.readHumidity();
    };

  //servo control
    ///// stop speed
  thing["SERVOstop"] << [] (pson & in) {
    if (!in.is_empty()) {
      servo1.write(90);
    }
    in = false;
  };

  ///// slow forward speed
  thing ["SERVOforward"] << [] (pson & in) {
    if (!in.is_empty()) {
      servo1.write(110);
    }
    in = false;
  };

}

void loop() {
 thing.handle();
 Serial.print("Temperature: "); 
 Serial.println(dht.readTemperature());
 Serial.print("Humidity: ");
 Serial.println(dht.readHumidity());

 delay(500);
}
