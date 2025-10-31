// #include <WiFi.h>
// #include <PubSubClient.h>
// void reconnect();

// // Wi-Fi credentials
// const char* ssid = "jinay";
// const char* password = "jshah123";

// // MQTT broker details
// const char* mqtt_server = "broker.hivemq.com";  // Free MQTT broker
// const int mqtt_port = 1883;
// const char* topic = "blindstick/alerts";

// WiFiClient espClient;
// PubSubClient client(espClient);

// // Pin definitions
// #define trigPin 14  // ESP32 GPIO 14 for ultrasonic sensor
// #define echoPin 12  // ESP32 GPIO 12 for ultrasonic sensor
// #define sosButton 4 // ESP32 GPIO 4 for SOS button
// #define buzzerPin 0 // ESP32 GPIO 0 for Buzzer

// void setup() {
//   Serial.begin(115200);

//   // Setup pin modes
//   pinMode(trigPin, OUTPUT);
//   pinMode(echoPin, INPUT);
//   pinMode(sosButton, INPUT_PULLUP);  // Pull-up for button
//   pinMode(buzzerPin, OUTPUT);

//   // Connect to Wi-Fi
//   WiFi.begin(ssid, password);
//   while (WiFi.status() != WL_CONNECTED) {
//     delay(1000);
//     Serial.println("Connecting to Wi-Fi...");
//   }
//   Serial.println("Connected to Wi-Fi");

//   // Set up MQTT client
//   client.setServer(mqtt_server, mqtt_port);
//   reconnect();
// }

// void reconnect() {
//   // Reconnect to MQTT if disconnected
//   while (!client.connected()) {
//     Serial.print("Attempting MQTT connection...");
//     if (client.connect("ESP32Client")) {
//       Serial.println("Connected to MQTT broker");
//     } else {
//       Serial.print("Failed, rc=");
//       Serial.print(client.state());
//       Serial.println(" Trying again in 5 seconds");
//       delay(5000);
//     }
//   }
// }

// void loop() {
//   // Ensure Wi-Fi and MQTT connections
//   if (WiFi.status() != WL_CONNECTED) {
//     Serial.println("WiFi disconnected! Reconnecting...");
//     WiFi.reconnect();  // Attempt to reconnect to Wi-Fi
//     delay(5000);
//   }

//   if (!client.connected()) {
//     reconnect();
//   }

//   client.loop();  // Maintain MQTT connection

//   // Obstacle detection with ultrasonic sensor
//   long duration, distance;
//   digitalWrite(trigPin, LOW);
//   delayMicroseconds(2);  
//   digitalWrite(trigPin, HIGH);
//   delayMicroseconds(10);  // 10-microsecond pulse to trigger the sensor
//   digitalWrite(trigPin, LOW);

//   // Measure echo time
//   duration = pulseIn(echoPin, HIGH);
  
//   if (duration == 0) {
//     Serial.println("No echo detected.");
//   } else {
//     // Calculate distance in cm
//     distance = (duration * 0.034) / 2;
//     Serial.print("Distance: ");
//     Serial.println(distance);
//   }

//   // Check for obstacle and publish message
//   if (distance > 0 && distance < 50) {
//     digitalWrite(buzzerPin, HIGH);  // Activate buzzer
//     Serial.println("Obstacle detected! Publishing to MQTT...");
//     client.publish(topic, "Obstacle detected within 50cm range!");
//     delay(500);
//     digitalWrite(buzzerPin, LOW);
//   }

//   // SOS button press check with debouncing
//   static bool lastButtonState = HIGH;  // Last button state
//   bool currentButtonState = digitalRead(sosButton);

//   if (lastButtonState == HIGH && currentButtonState == LOW) {
//     Serial.println("SOS Alert! Publishing to MQTT...");
//     client.publish(topic, "SOS ALERT! Assistance required.");
//     delay(1000);  // Debounce delay
//   }

//   lastButtonState = currentButtonState;
//   delay(500);
// }

// #include <WiFi.h>
// #include <HTTPClient.h>

// // Wi-Fi credentials
// const char* ssid = "jinay";
// const char* password = "jshah123";

// // HTTP Server details
// const char* serverURL = "http://172.20.10.4:5000/alert"; // Replace with your actual server URL

// // Pin definitions
// #define trigPin 14  // ESP32 GPIO 14 for ultrasonic sensor
// #define echoPin 12  // ESP32 GPIO 12 for ultrasonic sensor
// #define sosButton 4 // ESP32 GPIO 4 for SOS button
// #define buzzerPin 0 // ESP32 GPIO 0 for Buzzer

// void setup() {
//   Serial.begin(115200);

//   // Setup pin modes
//   pinMode(trigPin, OUTPUT);
//   pinMode(echoPin, INPUT);
//   pinMode(sosButton, INPUT_PULLUP);  // Pull-up for button
//   pinMode(buzzerPin, OUTPUT);

//   // Connect to Wi-Fi
//   WiFi.begin(ssid, password);
//   while (WiFi.status() != WL_CONNECTED) {
//     delay(1000);
//     Serial.println("Connecting to Wi-Fi...");
//   }
//   Serial.println("Connected to Wi-Fi");
// }

// void sendAlert(const char* message) {
//   if (WiFi.status() == WL_CONNECTED) {  // Ensure Wi-Fi is connected
//     HTTPClient http;
//     http.begin(serverURL);  // Specify destination URL
//     http.addHeader("Content-Type", "application/json");  // Set content type to JSON

//     // Create JSON payload
//     String payload = "{\"message\":\"";
//     payload += message;
//     payload += "\"}";

//     // Send HTTP POST request
//     int httpResponseCode = http.POST(payload);

//     // Check response
//     if (httpResponseCode > 0) {
//       Serial.print("HTTP Response code: ");
//       Serial.println(httpResponseCode);
//     } else {
//       Serial.print("Error code: ");
//       Serial.println(httpResponseCode);
//     }
//     http.end();  // Free resources
//   } else {
//     Serial.println("WiFi Disconnected");
//   }
// }

// void loop() {
//   // Ensure Wi-Fi connection
//   if (WiFi.status() != WL_CONNECTED) {
//     Serial.println("WiFi disconnected! Reconnecting...");
//     WiFi.reconnect();  // Attempt to reconnect to Wi-Fi
//     delay(5000);
//   }

//   // Obstacle detection with ultrasonic sensor
//   long duration, distance;
//   digitalWrite(trigPin, LOW);
//   delayMicroseconds(2);  
//   digitalWrite(trigPin, HIGH);
//   delayMicroseconds(10);  // 10-microsecond pulse to trigger the sensor
//   digitalWrite(trigPin, LOW);

//   // Measure echo time
//   duration = pulseIn(echoPin, HIGH);
  
//   if (duration == 0) {
//     Serial.println("No echo detected.");
//   } else {
//     // Calculate distance in cm
//     distance = (duration * 0.034) / 2;
//     Serial.print("Distance: ");
//     Serial.println(distance);
//   }

//   // Check for obstacle and send alert
//   if (distance > 0 && distance < 50) {
//     digitalWrite(buzzerPin, HIGH);  // Activate buzzer
//     Serial.println("Obstacle detected! Sending alert...");
//     sendAlert("Obstacle detected within 50cm range!");
//     delay(500);
//     digitalWrite(buzzerPin, LOW);
//   }

//   // SOS button press check with debouncing
//   static bool lastButtonState = HIGH;  // Last button state
//   bool currentButtonState = digitalRead(sosButton);

//   if (lastButtonState == HIGH && currentButtonState == LOW) {
//     Serial.println("SOS Alert! Sending alert...");
//     sendAlert("SOS ALERT! Assistance required.");
//     delay(1000);  // Debounce delay
//   }

//   lastButtonState = currentButtonState;
//   delay(500);
// }

#include <WiFi.h>
#include <HTTPClient.h>

// Wi-Fi credentials
const char* ssid = "jinay";
const char* password = "jshah123";

// HTTP Server details
const char* serverURL = "http://172.20.10.4:5000/alert"; // Replace with your actual server URL

// Pin definitions
#define trigPin 14  // ESP32 GPIO 14 for ultrasonic sensor
#define echoPin 12  // ESP32 GPIO 12 for ultrasonic sensor
#define sosButton 4 // ESP32 GPIO 4 for SOS button
#define buzzerPin 0 // ESP32 GPIO 0 for Buzzer Signal Pin

void setup() {
  Serial.begin(115200);

  // Setup pin modes
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(sosButton, INPUT_PULLUP);  // Pull-up for button
  pinMode(buzzerPin, OUTPUT);  // Buzzer Signal Pin

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to Wi-Fi...");
  }
  Serial.println("Connected to Wi-Fi");
}

void sendAlert(const char* message) {
  if (WiFi.status() == WL_CONNECTED) {  // Ensure Wi-Fi is connected
    HTTPClient http;
    http.begin(serverURL);  // Specify destination URL
    http.addHeader("Content-Type", "application/json");  // Set content type to JSON

    // Create JSON payload
    String payload = "{\"message\":\"";
    payload += message;
    payload += "\"}";

    // Send HTTP POST request
    int httpResponseCode = http.POST(payload);

    // Check response
    if (httpResponseCode > 0) {
      Serial.print("HTTP Response code: ");
      Serial.println(httpResponseCode);
    } else {
      Serial.print("Error code: ");
      Serial.println(httpResponseCode);
    }
    http.end();  // Free resources
  } else {
    Serial.println("WiFi Disconnected");
  }
}

void loop() {
  // Ensure Wi-Fi connection
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("WiFi disconnected! Reconnecting...");
    WiFi.reconnect();  // Attempt to reconnect to Wi-Fi
    delay(5000);
  }

  // Obstacle detection with ultrasonic sensor
  long duration, distance;
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);  
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);  // 10-microsecond pulse to trigger the sensor
  digitalWrite(trigPin, LOW);

  // Measure echo time
  duration = pulseIn(echoPin, HIGH);
  
  if (duration == 0) {
    Serial.println("No echo detected.");
  } else {
    // Calculate distance in cm
    distance = (duration * 0.034) / 2;
    Serial.print("Distance: ");
    Serial.println(distance);
  }

  // Check for obstacle and send alert
  if (distance > 0 && distance < 50) {
    digitalWrite(buzzerPin, HIGH);  // Activate buzzer
    Serial.println("Obstacle detected! Sending alert...");
    sendAlert("Obstacle detected within 50cm range!");
    delay(500);
    digitalWrite(buzzerPin, LOW);
  }

  // SOS button press check with debouncing
  static bool lastButtonState = HIGH;  // Last button state
  bool currentButtonState = digitalRead(sosButton);

  if (lastButtonState == HIGH && currentButtonState == LOW) {
    Serial.println("SOS Alert! Sending alert...");
    sendAlert("SOS ALERT! Assistance required.");
    delay(1000);  // Debounce delay
  }

  lastButtonState = currentButtonState;
  delay(500);
}