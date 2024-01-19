#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

// Define Blynk authentication token and WiFi credentials
#define BLYNK_AUTH_TOKEN "your_blynk_auth_token"
#define WIFI_SSID "YourWiFiSSID"
#define WIFI_PASSWORD "YourWiFiPassword"

// Define pin assignments for PIR sensors, buzzer, and LED
#define MAINDOOR_SENSOR_PIN 13
#define BACKYARD_SENSOR_PIN 16
#define ALARM_PIN 14
#define ALERT_LIGHT_PIN 4

// Variables to store sensor states and values
int MAINDOOR_SENSOR_value;
int MAINDOOR_SENSOR_state;

int BACKYARD_SENSOR_value;
int BACKYARD_SENSOR_state;

int ALARM_state;
int ALARM_value;

int ALERT_LIGHT_state;
int ALERT_LIGHT_value;

// Blynk virtual pin handlers
BLYNK_WRITE(V3) {
  MAINDOOR_SENSOR_state = param.asInt();
}

BLYNK_WRITE(V1) {
  BACKYARD_SENSOR_state = param.asInt();
}

BLYNK_WRITE(V2) {
  ALARM_state = param.asInt();
}

BLYNK_WRITE(V4) {
  ALERT_LIGHT_state = param.asInt();
}

void setup() {
  Serial.begin(115200);
  delay(10);

  // Initialize Blynk with authentication token and WiFi credentials
  Blynk.begin(BLYNK_AUTH_TOKEN, WIFI_SSID, WIFI_PASSWORD);

  // Set pin modes for sensors, buzzer, and LED
  pinMode(MAINDOOR_SENSOR_PIN, INPUT);
  pinMode(BACKYARD_SENSOR_PIN, INPUT);
  pinMode(ALARM_PIN, OUTPUT);
  pinMode(ALERT_LIGHT_PIN, OUTPUT);
}

void loop() {
  // Check and handle sensor states based on Blynk commands
  if (MAINDOOR_SENSOR_state == HIGH) {
    getMAINDOOR_SENSOR_value();
  }

  if (BACKYARD_SENSOR_state == HIGH) {
    getBACKYARD_SENSOR_value();
  }

  if (ALARM_state == HIGH) {
    getALARM_value();
  }

  if (ALERT_LIGHT_state == HIGH) {
    getALERT_LIGHT_value();
  }

  // Run Blynk to handle communication
  Blynk.run();
}

// Function to handle MAIN DOOR sensor data
void getMAINDOOR_SENSOR_value() {
  MAINDOOR_SENSOR_value = digitalRead(MAINDOOR_SENSOR_PIN);

  if (MAINDOOR_SENSOR_value) {
    digitalWrite(ALARM_PIN, HIGH);
    Serial.println("Someone Detected near MAIN DOOR");
    Blynk.notify("Someone Detected near MAIN DOOR. Alarm has been Turned ON");
    delay(5000);
    digitalWrite(ALERT_LIGHT_PIN, HIGH);
    Blynk.notify("");
  }
}

// Function to handle BACKYARD sensor data
void getBACKYARD_SENSOR_value() {
  BACKYARD_SENSOR_value = digitalRead(BACKYARD_SENSOR_PIN);

  if (BACKYARD_SENSOR_value) {
    digitalWrite(ALARM_PIN, HIGH);
    Serial.println("Someone Detected in BACKYARD");
    Blynk.notify("Someone Detected in BACKYARD. Alarm has been Turned ON");
    delay(5000);
    digitalWrite(ALERT_LIGHT_PIN, HIGH);
    Blynk.notify("");
  }
}

// Function to handle buzzer (ALARM) state
void getALARM_value() {
  ALARM_value = digitalRead(ALARM_PIN);

  if (ALARM_value) {
    digitalWrite(ALARM_PIN, LOW);
    Serial.println("Alarm has Turned OFF");
    Blynk.notify("Alarm has been Turned OFF");
  }
}

// Function to handle alert light state
void getALERT_LIGHT_value() {
  ALERT_LIGHT_value = digitalRead(ALERT_LIGHT_PIN);

  if (ALERT_LIGHT_value) {
    digitalWrite(ALERT_LIGHT_PIN, LOW);
    Serial.println("Lights are Turned OFF");
    Blynk.notify("Alert Lights are Turned OFF");
  }
}
