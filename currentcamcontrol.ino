
#include <Servo.h>

// Create the two servo objects
Servo servo1;
Servo servo2;

// Joystick analog input pins
const int joyX = A0;
const int joyY = A1;

// Servo signal pins
const int servo1Pin = 9;
const int servo2Pin = 10;

// Joystick pushbutton pin
const int joyButton = 2;

// Servo positions
const int neutralAngle = 90;
int angle1 = neutralAngle;
int angle2 = neutralAngle;

// Joystick center and dead zone
const int joystickCenter = 512;
const int deadZone = 40;

// Button state tracking
int lastButtonState = HIGH;

void setup() {
  servo1.attach(servo1Pin);
  servo2.attach(servo2Pin);

  // Start both servos at neutral
  servo1.write(angle1);
  servo2.write(angle2);

  // Most joystick buttons connect to GND when pressed
  pinMode(joyButton, INPUT_PULLUP);

  Serial.begin(9600);
}

void loop() {
  int xValue = analogRead(joyX);
  int yValue = analogRead(joyY);
  int buttonState = digitalRead(joyButton);

  // Reset both servos only when the button is pressed
  if (buttonState == LOW && lastButtonState == HIGH) {
    angle1 = neutralAngle;
    angle2 = neutralAngle;
  } else {
    // Update Servo 1 only when the horizontal joystick moves
    if (abs(xValue - joystickCenter) > deadZone) {
      angle1 = map(xValue, 0, 1023, 0, 180);
    }

    // Update Servo 2 only when the vertical joystick moves
    if (abs(yValue - joystickCenter) > deadZone) {
      angle2 = map(yValue, 0, 1023, 0, 180);
    }
  }

  // Keep the servos at their stored positions
  servo1.write(constrain(angle1, 0, 180));
  servo2.write(constrain(angle2, 0, 180));

  lastButtonState = buttonState;

  delay(15);
}
