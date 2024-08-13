// Define stepper motor connections:
#define dirPin 5
#define stepPin 6

// Variable to store the current direction of the motor
int motorDirection = 1; // 1 for clockwise, -1 for counterclockwise

void setup() {
  // Start the serial communication
  Serial.begin(9600);

  // Declare pins as output:
  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);

  // Set the spinning direction CW/CCW:
  digitalWrite(dirPin, HIGH);
}

void loop() {
  // Check for serial input
  if (Serial.available() > 0) {
    char command = Serial.read();
    executeCommand(command);
  }

  // These four lines result in 1 step:
  digitalWrite(stepPin, HIGH);
  delayMicroseconds(500);
  digitalWrite(stepPin, LOW);
  delayMicroseconds(500);
}

void executeCommand(char command) {
  switch (command) {
    case 's': // Start motor
      // Set the spinning direction CW/CCW:
      digitalWrite(dirPin, (motorDirection == 1) ? HIGH : LOW);
      break;

    case 't': // Stop motor
      digitalWrite(stepPin, LOW);
      break;

    case 'c': // Change direction
      motorDirection *= -1;
      digitalWrite(dirPin, (motorDirection == 1) ? HIGH : LOW);
      break;

    default:
      // Unknown command
      Serial.println("Unknown command");
  }
}
