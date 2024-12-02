#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>

// Initialize LCD with I2C address 0x27
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Define IR sensor pin
const int irSensorPin = 7;

// Define Servo pin and initialize Servo
const int servoPin = 3;
Servo myServo;

// Array of medicine names
String medicines[] = {"Paracetamol", "Ibuprofen", "Amoxicillin", "Cetirizine", "Metformin"};
int totalMedicines = 5;
int currentIndex = 0;  // Start with the first medicine

// Servo angles for each detection
int servoAngles[] = {0, 40, 80, 120, 160, 180};

void setup() {
  // Initialize the Serial Monitor
  Serial.begin(9600);

  // Initialize the LCD
  lcd.init();
  lcd.backlight();

  // Set up the IR sensor pin
  pinMode(irSensorPin, INPUT);

  // Initialize the Servo
  myServo.attach(servoPin);
  myServo.write(0); // Start at 0°

  // Display the first medicine on the LCD
  lcd.setCursor(0, 0);
  lcd.print("Medicine:");
  lcd.setCursor(0, 1);
  lcd.print(medicines[currentIndex]);
}

void loop() {
  int irState = digitalRead(irSensorPin); // Read the IR sensor state

  if (irState == LOW) { // If the IR sensor detects an object
    Serial.println("IR Sensor Triggered!"); // Print detection to the Serial Monitor
    Serial.print("Displaying: ");
    Serial.println(medicines[currentIndex]); // Print the current medicine name

    // Move servo to the next angle
    myServo.write(servoAngles[currentIndex]);

    // Display the current medicine on the LCD
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Medicine:");
    lcd.setCursor(0, 1);
    lcd.print(medicines[currentIndex]);

    currentIndex++; // Move to the next medicine
    if (currentIndex >= totalMedicines) {
      currentIndex = 0; // Reset to the first medicine after the last one

      // Move servo back to 0° within 5 seconds
      for (int angle = 180; angle >= 0; angle -= 10) {
        myServo.write(angle);
        delay(500); // Gradual movement
      }
    }

    delay(2000); // Wait for 2 seconds before checking again
  }
}
