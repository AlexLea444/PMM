/*
 * wifi_comm.cpp
 * Purple Mountain Majesties
 *  - Eddy Zhang, Alexander Lea, Connor Nightingale, Jacob Carulli
 * Spring 2024
 *
 */
 
#include <Arduino.h>
#include <SPI.h>
#include <WiFiNINA.h>
#include <string.h>

#include "wifi_comm.h"
#include "drive.h"
#include "pins.h"
#include "utils.h"
#include "arduino_secrets.h"

const char Wifi_Comm::ssid[] = SECRET_SSID1;        // network SSID (name)
const char Wifi_Comm::pass[] = SECRET_PASS1;    // network password (use for WPA, or use as key for WEP)
const int Wifi_Comm::keyIndex = 0;             // network key Index number (needed only for WEP)
const int Wifi_Comm::portNumber = 80;          // defult 
int Wifi_Comm::status = WL_IDLE_STATUS;

// DNS:
const char Wifi_Comm::server[] = "ee31.ece.tufts.edu";    // name address for (using DNS)

// format of postRoute: "POST /senderID/receiverID HTTP/1.1"
// char postRoute[] = "POST /89C87865077A/8050D1451904 HTTP/1.1"; // posting will fail with this ID combo, no idea why
// sending from ourselves to ourselves:
//const char Wifi_Comm::postRoute[] = "POST /89C87865077A/89C87865077A HTTP/1.1"; 

// sending from ourselves to Team Team Red:
const char Wifi_Comm::postRoute[] = "POST /89C87865077A/A20F65BA5E3C HTTP/1.1";

// format of gettRoute: "GET /senderID/receiverID HTTP/1.1"
// char getRoute[] = "GET /89C87865077A/8050D1451904 HTTP/1.1";
const char Wifi_Comm::getRoute[] = "GET /89C87865077A/A20F65BA5E3C HTTP/1.1";
//const char Wifi_Comm::getRoute[] = "GET /A20F65BA5E3C/89C87865077A HTTP/1.1"; 

void Wifi_Comm::printWifiStatus() {
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());
  // print your board's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);
  // print the received signal strength:
  // long rssi = WiFi.RSSI();
  // Serial.print("signal strength (RSSI):");
  // Serial.print(rssi);
  // Serial.println(" dBm");
}

// post message from sender to the receiver
void Wifi_Comm::POSTServer(char *bodyMessage) {
  if (client.connect(server, portNumber)) {
    client.println(postRoute);
    client.print("Host: ");
    client.println(server);
    client.println("Content-Type: application/x-www-form-urlencoded");
    client.print("Content-Length: ");
    int postBodyLength = strlen(bodyMessage);
    client.println(postBodyLength);
    client.println(); // end HTTP header
    client.print(bodyMessage);

    millisDelay(2000);

    // print out the client response
    while (client.connected()) {
      if (client.available()) {
        // read an incoming byte from the server and print it to serial monitor:
        char c = client.read();
        Serial.print(c);
      }
    }

    // the server's disconnected, stop the client:
    client.stop();
    Serial.println();
    Serial.println("disconnected");
  }
}

// get message 
void Wifi_Comm::GETServer(char *message) {
  if (client.connect(server, portNumber)) {
    // Make a HTTP GET request:
    client.println(getRoute);
    client.print("Host: ");
    client.println(server);
    client.println("Connection: close");
    client.println();

    millisDelay(200);

    // index for writing to message buffer
    int messageIndex = 0;

    // print out the client response
    while (client.connected()) {
      if (client.available()) {
        // read an incoming byte from the server and print it to serial monitor:
        char c = client.read();
        message[messageIndex++] = c;
        // Check if the buffer is full
        if (messageIndex >= 512) {
          break; // Stop reading to avoid overflow
        }
      }
    }

    // add null terminator at the end of the message
    message[messageIndex] = '\0';

    // the server's disconnected, stop the client:
    client.stop();
    Serial.println();
    Serial.println("disconnected");
  }
}

void Wifi_Comm::setup() {
  // check for the WiFi module:
  if (WiFi.status() == WL_NO_MODULE) {
    Serial.println("Communication with WiFi module failed!");
    // don't continue
    while (true);
  }

  // attempt to connect to Wifi network:
  while (status != WL_CONNECTED) {
    Serial.print("Connecting to SSID: ");
    Serial.println(ssid);
    // Connect to WPA/WPA2 network. Change this line if using open or WEP network:
    status = WiFi.begin(ssid, pass);
    // wait 10 seconds for connection:
    millisDelay(10000);
  }

  Serial.println("Connected to wifi");
  printWifiStatus();
  Serial.println("\nStarting connection to server...");
}

void Wifi_Comm::chall1_red_bot1() {
  digitalWrite(Pins::redStateLED, LOW);
  millisDelay(150);
  digitalWrite(Pins::redStateLED, HIGH);
  millisDelay(150);
  digitalWrite(Pins::redStateLED, LOW);
  millisDelay(150);
  digitalWrite(Pins::redStateLED, HIGH);

  POSTServer("state=red");

  String response = "";
  char data[512];

  while (response != "red") {
    GETServer(data);
    response = String(data);
    response = response.substring(response.indexOf("state=") + 6, response.indexOf("state=") + 9);
  }
  
  digitalWrite(Pins::redStateLED, LOW);
  millisDelay(150);
  digitalWrite(Pins::redStateLED, HIGH);
  millisDelay(150);
  digitalWrite(Pins::redStateLED, LOW);
  millisDelay(150);
  digitalWrite(Pins::redStateLED, HIGH);
  millisDelay(150);
  digitalWrite(Pins::redStateLED, LOW);
  millisDelay(150);
  digitalWrite(Pins::redStateLED, HIGH);
  millisDelay(150);
  digitalWrite(Pins::redStateLED, LOW);
  digitalWrite(Pins::greenStateLED, HIGH);
}

void Wifi_Comm::chall1_yellow_bot1() {
  POSTServer("state=yellow");
}

void Wifi_Comm::chall1_red_bot2() {
  String response = "";
  char data[512];

  while (response != "red") {
    GETServer(data);
    response = String(data);
    response = response.substring(response.indexOf("state=") + 6, response.indexOf("state=") + 9);
  }
  
  digitalWrite(Pins::redStateLED, HIGH);
  millisDelay(150);
  digitalWrite(Pins::redStateLED, LOW);

  POSTServer("state=red");
}

void Wifi_Comm::chall1_yellow_bot2() {
  String response = "";
  char data[512];

  while (response != "yellow") {
    GETServer(data);
    response = String(data);
    response = response.substring(response.indexOf("state=") + 6, response.indexOf("state=") + 12);
  }
}

void Wifi_Comm::chall1_go_bot1() {
  String response = "";
  char data[512];

  POSTServer("state=go");

  while (response != "go") {
    GETServer(data);
    response = String(data);
    response = response.substring(response.indexOf("state=") + 6, response.indexOf("go") + 8);
  }
}

void Wifi_Comm::chall1_go_bot2() {
  String response = "";
  char data[512];


  while (response != "go") {
    GETServer(data);
    response = String(data);
    response = response.substring(response.indexOf("state=") + 6, response.indexOf("go") + 8);
  }

  POSTServer("state=go");
}

void Wifi_Comm::chall1_end() {
  POSTServer("state=done");

  String response = "";
  char data[512];

  while (response != "done") {
    GETServer(data);
    response = String(data);
    response = response.substring(response.indexOf("state=") + 6, response.indexOf("state=") + 10);
  }

  digitalWrite(Pins::redStateLED, HIGH);
  digitalWrite(Pins::blueStateLED, HIGH);
  digitalWrite(Pins::greenStateLED, HIGH);
  digitalWrite(Pins::yellowStateLED, HIGH);
  delay(150);

  digitalWrite(Pins::redStateLED, LOW);
  digitalWrite(Pins::blueStateLED, LOW);
  digitalWrite(Pins::greenStateLED, LOW);
  digitalWrite(Pins::yellowStateLED, LOW);
  delay(150);

  digitalWrite(Pins::redStateLED, HIGH);
  digitalWrite(Pins::blueStateLED, HIGH);
  digitalWrite(Pins::greenStateLED, HIGH);
  digitalWrite(Pins::yellowStateLED, HIGH);
  delay(150);

  digitalWrite(Pins::redStateLED, LOW);
  digitalWrite(Pins::blueStateLED, LOW);
  digitalWrite(Pins::greenStateLED, LOW);
  digitalWrite(Pins::yellowStateLED, LOW);
  delay(150);

  digitalWrite(Pins::redStateLED, HIGH);
  digitalWrite(Pins::blueStateLED, HIGH);
  digitalWrite(Pins::greenStateLED, HIGH);
  digitalWrite(Pins::yellowStateLED, HIGH);
  delay(150);

  digitalWrite(Pins::redStateLED, LOW);
  digitalWrite(Pins::blueStateLED, LOW);
  digitalWrite(Pins::greenStateLED, LOW);
  digitalWrite(Pins::yellowStateLED, LOW);
  delay(150);

  digitalWrite(Pins::horn, HIGH);
  delay(150);
  digitalWrite(Pins::horn, LOW);
  delay(150);
  digitalWrite(Pins::horn, HIGH);
  delay(150);
  digitalWrite(Pins::horn, LOW);
  delay(150);
}
