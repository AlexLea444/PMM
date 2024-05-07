/*
 * remote_control.cpp
 * Purple Mountain Majesties
 *  - Eddy Zhang, Alexander Lea, Connor Nightingale, Jacob Carulli
 * 5/6/2024
 *
 */

#include <Arduino.h>
#include <ArduinoMqttClient.h>
#include <WiFiNINA.h>

#include "remote_control.h"
#include "arduino_secrets.h"
#include "pins.h"

///////please enter your sensitive data in the Secret tab/arduino_secrets.h
char ssid[] = SECRET_SSID2;        // your network SSID
char pass[] = SECRET_PASS2;    // your network password

WiFiClient wifiClient;
MqttClient mqttClient(wifiClient);

const char broker[] = "10.5.15.62";
int        port     = 1883;
const char topic[]  = "Remote";


/* Function: runRemote
 * Description: Call this function to drive the bot remotely via MQTT
 * Parameters:
 *   - None
 * Returns: None
 */
void runRemote() {
    // attempt to connect to Wifi network:
  Serial.print("Attempting to connect to SSID: ");
  Serial.println(ssid);
  while (WiFi.begin(ssid, pass) != WL_CONNECTED) {
    // failed, retry
    Serial.print(".");
    delay(5000);
  }

  Serial.println("You're connected to the network");
  Serial.println();

  Serial.print("Attempting to connect to the MQTT broker: ");
  Serial.println(broker);

  if (!mqttClient.connect(broker, port)) {
    Serial.print("MQTT connection failed! Error code = ");
    Serial.println(mqttClient.connectError());

    while (1);
  }

  Serial.println("You're connected to the MQTT broker!");
  Serial.println();

  // set the message receive callback
  mqttClient.onMessage(onMqttMessage);

  Serial.print("Subscribing to topic: ");
  Serial.println(topic);
  Serial.println();

  // subscribe to a topic
  mqttClient.subscribe(topic);

  // topics can be unsubscribed using:
  // mqttClient.unsubscribe(topic);

  Serial.print("Topic: ");
  Serial.println(topic);

  Serial.println();

  while (true) {
    // call poll() regularly to allow the library to receive MQTT messages and
    // send MQTT keep alive which avoids being disconnected by the broker
    mqttClient.poll();
  }
}


/* Function: onMqttMessage
 * Description: Function called when the mqtt client reads a new message
 * Parameters:
 *   - messageSize: Size of incoming message, required by mqttClient
 * Returns: None
 */
void onMqttMessage(int messageSize) {
  // Read the message into a buffer
  char message[messageSize + 1];
  for (int i = 0; i < messageSize; i++) {
    message[i] = (char)mqttClient.read();
  }
  message[messageSize] = '\0'; // Null terminate the string

  // Parse the message as two int numbers
  int x, y;
  if (sscanf(message, "%d,%d", &x, &y) != 2) {
    Serial.println("Failed to parse message");
    return;
  }

  y = -y;

  int speed = sqrt(x * x + y * y);

  if (abs(y) > abs(x)) {
    if (y > 0) {
      forward(speed);
      Serial.println("forward " + String(speed));
    } else {
      back(speed);
      Serial.println("back" + String(speed));
    }
  } else {
    if (x > 0) {
      right(speed);
      Serial.println("right" + String(speed));
    } else {
      left(speed);
      Serial.println("left" + String(speed));
    }
  }
}


/* Function: forward
 * Description: Drive forward at the given speed
 * Parameters:
 *   - speed: Integer between 0 and 100 which controls speed of bot
 * Returns: None
 */
void forward(int speed) {
  analogWrite(Pins::motor1, 0);
  analogWrite(Pins::motor2, speed);
  analogWrite(Pins::motor3, int(speed * 1.42));
  analogWrite(Pins::motor4, 0);
}

/* Function: left
 * Description: Turn left at the given speed
 * Parameters:
 *   - speed: Integer between 0 and 100 which controls speed of bot
 * Returns: None
 */
void left(int speed) {
  analogWrite(Pins::motor1, speed);
  analogWrite(Pins::motor2, 0);
  analogWrite(Pins::motor3, speed);
  analogWrite(Pins::motor4, 0);
}

/* Function: back
 * Description: Drive backward at the given speed
 * Parameters:
 *   - speed: Integer between 0 and 100 which controls speed of bot
 * Returns: None
 */
void back(int speed) {
  analogWrite(Pins::motor1, speed);
  analogWrite(Pins::motor2, 0);
  analogWrite(Pins::motor3, 0);
  analogWrite(Pins::motor4, int(speed * 1.36));
}

/* Function: right
 * Description: Turn right at the given speed
 * Parameters:
 *   - speed: Integer between 0 and 100 which controls speed of bot
 * Returns: None
 */
void right(int speed) {
  analogWrite(Pins::motor1, 0);
  analogWrite(Pins::motor2, speed);
  analogWrite(Pins::motor3, 0);
  analogWrite(Pins::motor4, speed);
}