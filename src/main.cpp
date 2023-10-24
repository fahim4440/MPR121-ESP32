// /*********************************************************
// This is a library for the MPR121 12-channel Capacitive touch sensor
// Designed specifically to work with the MPR121 Breakout in the Adafruit shop 
//   ----> https://www.adafruit.com/products/
// These sensors use I2C communicate, at least 2 pins are required 
// to interface
// Adafruit invests time and resources providing this open source code, 
// please support Adafruit and open-source hardware by purchasing 
// products from Adafruit!
// Written by Limor Fried/Ladyada for Adafruit Industries.  
// BSD license, all text above must be included in any redistribution
// **********************************************************/
// #include <Wire.h>
// #include <Arduino.h>
// #include "Adafruit_MPR121.h"
// // You can have up to 4 on one i2c bus but one is enough for testing!
// Adafruit_MPR121 cap = Adafruit_MPR121();
// // Keeps track of the last pins touched
// // so we know when buttons are 'released'
// uint16_t lasttouched = 0;
// uint16_t currtouched = 0;
// void setup() {
//   Serial.begin(115200);
//   Serial.println("Adafruit MPR121 Capacitive Touch sensor test"); 
  
//   // Default address is 0x5A, if tied to 3.3V its 0x5B
//   // If tied to SDA its 0x5C and if SCL then 0x5D
//   if (!cap.begin(0x5A)) {
//     Serial.println("MPR121 not found, check wiring?");
//     while (1);
//   }
//   Serial.println("MPR121 found!");
// }
// void loop() {
//   // Get the currently touched pads
//   currtouched = cap.touched();
//   Serial.println(currtouched);
  
//   for (uint8_t i=0; i<12; i++) {
//     // it if *is* touched and *wasnt* touched before, alert!
//     if ((currtouched & _BV(i)) && !(lasttouched & _BV(i)) ) {
//       Serial.print(i); Serial.println(" touched");
//     }
//     // if it *was* touched and now *isnt*, alert!
//     if (!(currtouched & _BV(i)) && (lasttouched & _BV(i)) ) {
//       Serial.print(i); Serial.println(" released");
//     }
//   }
//   // reset our state
//   lasttouched = currtouched;
//   // comment out this line for detailed data from the sensor!
//   return;
  
//   // debugging info, what
//   Serial.print("\t\t\t\t\t\t\t\t\t\t\t\t\t 0x"); Serial.println(cap.touched(), HEX);
//   Serial.print("Filt: ");
//   for (uint8_t i=0; i<12; i++) {
//     Serial.print(cap.filteredData(i)); Serial.print("\t");
//   }
//   Serial.println();
//   Serial.print("Base: ");
//   for (uint8_t i=0; i<12; i++) {
//     Serial.print(cap.baselineData(i)); Serial.print("\t");
//   }
//   Serial.println();
  
//   // put a delay so it isn't overwhelming
//   delay(100);
// }

// // void setup() {
// //   Serial.begin(115200);
// //   Serial.println("Hello");
// // }

// // void loop() {

// // }

/*********
  Rui Santos
  Complete project details at https://randomnerdtutorials.com
  Based on the NTP Client library example
*********/

#include <WiFi.h>
#include <NTPClient.h>
#include <WiFiUdp.h>

// Replace with your network credentials
const char* ssid     = "2019";
const char* password = "mymctg2019";

// Define NTP Client to get time
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP);

// Variables to save date and time
String formattedDate;
String dayStamp;
String timeStamp;

void setup() {
  // Initialize Serial Monitor
  Serial.begin(115200);
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  // Print local IP address and start web server
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

// Initialize a NTPClient to get time
  timeClient.begin();
  // Set offset time in seconds to adjust for your timezone, for example:
  // GMT +1 = 3600
  // GMT +8 = 28800
  // GMT -1 = -3600
  // GMT 0 = 0
  timeClient.setTimeOffset(21600);
}
void loop() {
  while(!timeClient.update()) {
    timeClient.forceUpdate();
  }
  // The formattedDate comes with the following format:
  // 2018-05-28T16:00:13Z
  // We need to extract date and time
  formattedDate = timeClient.getFormattedDate();
  Serial.println(formattedDate);
  unsigned long now = timeClient.getEpochTime();
  Serial.println(now);

  // Extract date
  int splitT = formattedDate.indexOf("T");
  dayStamp = formattedDate.substring(0, splitT);
  Serial.print("DATE: ");
  Serial.println(dayStamp);
  // Extract time
  timeStamp = formattedDate.substring(splitT+1, formattedDate.length()-1);
  Serial.print("HOUR: ");
  Serial.println(timeStamp);
  delay(1000);
}