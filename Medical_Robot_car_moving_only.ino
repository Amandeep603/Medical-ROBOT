#define BLYNK_TEMPLATE_ID "TMPL3ri496K50"
#define BLYNK_TEMPLATE_NAME "Medical Robot"
#define BLYNK_AUTH_TOKEN "KN0960P6EJl1eFjkRsR5RJPzs0on87F1"

// Include the library files
#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

// Define motor pins
#define IN1 16  // Left motor Forward
#define IN2 5   // Left motor Backward
#define IN3 4   // Right motor Forward
#define IN4 0   // Right motor Backward


// Variables for joystick and speed control
int x = 50;         // Joystick X-axis (default center)
int y = 50;         // Joystick Y-axis (default center)

// WiFi credentials
char ssid[] = "Test";       // Enter your WiFi name
char pass[] = "Test12345";  // Enter your WiFi password

void setup() {
  Serial.begin(9600);

  // Set motor pins as outputs
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);


  // Initialize Blynk
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass, "blynk.cloud", 80);
}

// Get joystick X-axis values
BLYNK_WRITE(V1) {
  x = param[0].asInt(); // Update X-axis value
}

// Get joystick Y-axis values
BLYNK_WRITE(V2) {
  y = param[0].asInt(); // Update Y-axis value
}


// Control car movement
void smartcar() {
  if (y > 70) {                // Move forward
    carForward();
    Serial.println("Moving Forward");
  } else if (y < 30) {         // Move backward
    carBackward();
    Serial.println("Moving Backward");
  } else if (x < 30) {         // Turn left
    carLeft();
    Serial.println("Turning Left");
  } else if (x > 70) {         // Turn right
    carRight();
    Serial.println("Turning Right");
  } else {                     // Stop
    carStop();
    Serial.println("Stopping");
  }
}

void loop() {
  Blynk.run();   // Run Blynk functionality
  smartcar();    // Call car control function
}

/************** Motor movement functions ***************/

// Move forward
void carForward() {
  analogWrite(ENA, Speed); // Left motors
  analogWrite(ENB, Speed); // Right motors
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

// Move backward
void carBackward() {
  analogWrite(ENA, Speed); // Left motors
  analogWrite(ENB, Speed); // Right motors
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

// Turn left
void carLeft() {
  analogWrite(ENA, Speed / 2); // Slow down left motors
  analogWrite(ENB, Speed);    // Right motors at full speed
  digitalWrite(IN1, LOW);     // Left motors stop
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);    // Right motors move forward
  digitalWrite(IN4, LOW);
}

// Turn right
void carRight() {
  analogWrite(ENA, Speed);    // Left motors at full speed
  analogWrite(ENB, Speed / 2); // Slow down right motors
  digitalWrite(IN1, HIGH);    // Left motors move forward
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);     // Right motors stop
  digitalWrite(IN4, LOW);
}

// Stop the car
void carStop() {
  analogWrite(ENA, 0);  // Stop left motors
  analogWrite(ENB, 0);  // Stop right motors
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}