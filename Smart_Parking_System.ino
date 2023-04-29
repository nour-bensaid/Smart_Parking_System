#include <LiquidCrystal.h> // Include the LiquidCrystal library
#include <Servo.h> // Include the Servo library

LiquidCrystal lcd(12, 11, 5, 4, 3, 2); // Initialize the LCD object with the corresponding pins
Servo parkingBar; // Create a Servo object for the parking bar

const int irSensorInPin = 7; // Define the input pin for the IR sensor that detects when a car is entering the parking
const int irSensorOutPin = 8; // Define the input pin for the IR sensor that detects when a car is leaving the parking

int carCount = 0; // Initialize the car count to zero
int availableSpots = 5; // Initialize the number of available spots to the maximum capacity of the parking

void setup() {
  pinMode(irSensorInPin, INPUT); // Set the IR sensor input pins as inputs
  pinMode(irSensorOutPin, INPUT);
  
  parkingBar.attach(9); // Attach the parking bar servo to pin 9

  lcd.begin(16, 2); // Initialize the LCD display with 16 columns and 2 rows
  lcd.print("Smart Parking"); // Print the title of the system on the first row of the display
}

void loop() {
  int inReading = digitalRead(irSensorInPin); // Read the input of the IR sensor that detects when a car is entering the parking
  int outReading = digitalRead(irSensorOutPin); // Read the input of the IR sensor that detects when a car is leaving the parking

  if (inReading == HIGH) { // If a car is entering the parking
    if (availableSpots > 0) { // If there are available spots
      carCount++; // Increment the car count
      availableSpots--; // Decrement the available spots
      lcd.clear(); // Clear the LCD display
      lcd.setCursor(0, 0); // Set the cursor to the first column of the first row
      lcd.print("Car entered: "); // Print the message on the first row of the display
      lcd.print(carCount); // Print the car count on the first row of the display
      lcd.setCursor(0, 1); // Set the cursor to the first column of the second row
      lcd.print("Available: "); // Print the message on the second row of the display
      lcd.print(availableSpots); // Print the number of available spots on the second row of the display
      parkingBar.write(180); // Raise the parking bar
      delay(10000); // Wait for 10 seconds
      parkingBar.write(0); // Lower the parking bar
    }
    else { // If there are no available spots
      lcd.clear(); // Clear the LCD display
      lcd.setCursor(0, 0); // Set the cursor to the first column of the first row
      lcd.print("Parking full"); // Print the message on the first row of the display
    }
  }

  if (outReading == HIGH) { // If a car is leaving the parking
    carCount--; // Decrement the car count
    availableSpots++; // Increment the available spots
    lcd.clear(); // Clear the LCD display
    
    lcd.setCursor(0, 0); // Set the cursor to the first column of the first row
    lcd.print("Car exited: "); // Print the message on the first row of the display
    lcd.print(carCount); // Print the car count
  }
}