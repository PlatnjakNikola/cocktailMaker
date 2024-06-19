#include <AccelStepper.h>

const int opticCount = 8;      // how many optic stations there are
const int parameterCount = 3;  //number of seeting to be stored in array for each optic

// Define stepper motor connections and motor interface type. Motor interface type must be set to 1 when using a driver:
#define dirPin 2
#define stepPin 3
#define dirPinPlatform 4
#define stepPinPlatform 5
#define motorInterfaceType 1
//---------------------

// Create a new instance of the AccelStepper class:
AccelStepper stepper = AccelStepper(motorInterfaceType, stepPin, dirPin);
AccelStepper platformSteppers = AccelStepper(motorInterfaceType, stepPinPlatform, dirPinPlatform);
//---------------------

//matric has 3 number for each dispenser:
// first number is how far away is dispenser from its neighbour
// second is delay for how long mechanisam for dispensing shuold be pressed
// third number is how many times should value be pressed
// First number is always the same and numbers that go to serial are second and third
//(0,0,0, 460,0,0, 340,0,0, 0,0,0, 0,0,0, 0,0,0, 380,0,0, 470,0,0)
//u serial, ali bez razmaka ide npr.(10,1, 10,1, 10,1, 10,1, 10,1, 10,1, 10,1, 10,1)
int drinkMatrix[opticCount][parameterCount] = {
  0, 0, 0,
  460, 0, 0,
  350, 0, 0,
  0, 0, 0,
  0, 0, 0,
  0, 0, 0,
  340, 0, 0,
  460, 0, 0
};
//---------------------

//The below is for the contact switch.
const int buttonPin = 7;  // the pin that the pushbutton is attached to
int buttonState = 0;      // current state of the button
int lastButtonState = 0;  // previous state of the button
//---------------------

// Below is for the RGB LED
const int redPin = A0;
const int greenPin = A1;
const int bluePin = A2;
//---------------------

//Below is for the water pumps
const int pump1 = 6;
const int pump2 = 8;
const int pump3 = 12;
const int pump4 = 13;
//---------------------

const int motorRelay = 9;

//The below are for running the machine:
int raftFound = false;
int drinkRequested = false;
//---------------------

void setup() {
  // initialize serial communication:
  Serial.begin(9600);
  //--------------------------------

  // for the contact switch
  // initialize the button pin as a input:
  pinMode(buttonPin, INPUT);
  //--------------------------------

  //  For the stepper motors
  stepper.setMaxSpeed(1000);
  platformSteppers.setMaxSpeed(1000);
  //--------------------------------

  // For LED
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  //-------------------------------

  // For pumps
  pinMode(pump1, OUTPUT);
  pinMode(pump2, OUTPUT);
  pinMode(pump3, OUTPUT);
  pinMode(pump4, OUTPUT);
  //-------------------------------
  pinMode(motorRelay, OUTPUT);
}


void loop() {
  //turn off all the pumps
  //why on HIGH?
  //ha ha, because I connect pump so they work on when signal is LOW and stop when signal is high.
  digitalWrite(pump1, HIGH);
  digitalWrite(pump2, HIGH);
  digitalWrite(pump3, HIGH);
  digitalWrite(pump4, HIGH);
  digitalWrite(motorRelay, LOW);

  //Lets find the location of the platform:
  if (raftFound == false) {

    Serial.println("Raft location not known yet");
    setColor(255, 0, 0);  // red
    delay(1000);
    Serial.print("Looking for the raft...");

    //returning platform to starting position
    returnToStart();

    raftFound = true;
    Serial.println("There it is! :)");
    setColor(0, 0, 255);  // blue
    delay(500);           // Delay a little bit to calm everything down
  }


  //working through the dispensing instructions until drink is complete and paddle is at last optic position:
  if (drinkRequested == true) {

    for (int optic = 0; optic < opticCount; optic++) {
      //Move to pump
      //platform is always at first dispenser so in matric first value to move is always 0
      stepper.setCurrentPosition(0);
      while (stepper.currentPosition() != -drinkMatrix[optic][0]) {
        stepper.setSpeed(-300);
        stepper.runSpeed();
      }
      delay(200);

      if (drinkMatrix[optic][2] > 0 && raftFound == true) {
        switch (optic) {
          case 2:
            //pump 1 is working
            motorPumpstart(pump1, drinkMatrix[optic][1] * 100);
            break;

          case 3:
            //pump 2 is working
            motorPumpstart(pump2, drinkMatrix[optic][1] * 100);
            break;

          case 4:
            //pump 3 is working
            motorPumpstart(pump3, drinkMatrix[optic][1] * 100);
            break;

          case 5:
            //pump 4 is working
            motorPumpstart(pump4, drinkMatrix[optic][1] * 100);
            break;

          default:
            //dispense what is required then resume moving to the next position:
            while (drinkMatrix[optic][2] > 0) {
              startDispensing(drinkMatrix[optic][1] * 100);
              drinkMatrix[optic][2] -= 1;
            }
            break;
        }
      }
    }

    //Drink complete
    Serial.println("Drinks ready, enjoy.");
    setColor(0, 255, 0);  // green
    drinkRequested = false;
    raftFound = false;
  }

  while (drinkRequested == false) {

    if (Serial.available()) {

      for (int optic = 0; optic < opticCount; optic++) {
        for (int parameter = 1; parameter < parameterCount; parameter++) {
          readParameter(drinkMatrix[optic][parameter]);
        }
      }
      CheckArray();
      Serial.println("Done loading");
      drinkRequested = true;
    }
  }
}


void CheckArray() {
  //print out the array to check it:
  for (int i = 0; i < opticCount; i++) {
    for (int j = 0; j < parameterCount; j++) {
      Serial.print(drinkMatrix[i][j]);
      Serial.print(",");
    }
    Serial.println();
  }
}


void setColor(int red, int green, int blue) {
  analogWrite(redPin, red);
  analogWrite(greenPin, green);
  analogWrite(bluePin, blue);
}


void startDispensing(int vrijeme) {
  platformSteppers.setCurrentPosition(0);
  while (platformSteppers.currentPosition() != -1900) {
    platformSteppers.setSpeed(-500);
    platformSteppers.runSpeed();
  }
  //time of dispenser being pressed
  delay(vrijeme);

  platformSteppers.setCurrentPosition(0);
  while (platformSteppers.currentPosition() != 1900) {
    platformSteppers.setSpeed(500);
    platformSteppers.runSpeed();
  }

  platformSteppers.setCurrentPosition(0);
  while (platformSteppers.currentPosition() != -1100) {
    platformSteppers.setSpeed(-500);
    platformSteppers.runSpeed();
  }
  platformSteppers.setCurrentPosition(0);
  while (platformSteppers.currentPosition() != 1100) {
    platformSteppers.setSpeed(500);
    platformSteppers.runSpeed();
  }
  delay(500);
}


void returnToStart() {
  stepper.setCurrentPosition(0);
  while ((buttonState = digitalRead(buttonPin)) != 0 && raftFound == false) {
    stepper.setSpeed(300);
    stepper.runSpeed();
  }
  //moving plaform to first dispenser
  stepper.setCurrentPosition(0);
  while (stepper.currentPosition() != -20) {
    stepper.setSpeed(-300);
    stepper.runSpeed();
  }
}

void motorPumpstart(int pump, int vrijeme) {
  digitalWrite(motorRelay, HIGH);
  digitalWrite(pump, LOW);
  //time of pump working
  delay(vrijeme);
  digitalWrite(pump, HIGH);
  digitalWrite(motorRelay, LOW);
  delay(500);
}


void readParameter(int& parameter) {
  String inputString = Serial.readStringUntil(',');
  parameter = inputString.toInt();
}