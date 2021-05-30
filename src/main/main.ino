const int inPin = 10;
const int stepPin = 8; 
const int dirPin = 9; 
const int enablePin = 2;

int switchState;
int prevState;
// LOW is open, HIGH is closed.
// We want LOW to correspond to an open curtain, and HIGH to a closed curtain.

long time = 0;
long debounceMilli = 200;  // milliseconds
int delayMicro = 2000;     // microseconds

/*
 * The number of steps to run will depend on the diameter of your cog,
 * the type of timing belt you use, and the width of your curtain.
 * My rough calculations were:
 * 
 * 
 * 2mm between timing belt teeth (GT2)
 * 36 teeth on motor cog
 * --> 72mm per full rotation
 * 
 * 850mm of travel to open or close curtain
 * --> 12 full rotations
 * 
 * 200 steps per rotation for my NEMA 17 motor.
 * 
 * 12 * 200 = 2400 steps
 */
int numSteps = 2400;

void setup() {
  pinMode(inPin, INPUT);
  pinMode(stepPin, OUTPUT); 
  pinMode(dirPin, OUTPUT);
  pinMode(enablePin, OUTPUT);

  prevState = digitalRead(inPin);

  // motor is inactive to start
  sleepStepper();
}

void loop() {
  // Did the switch state just change?
  switchState = digitalRead(inPin);

  // debounce ensures that we don't get any quick on/off toggling when moving the switch
  if (switchState != prevState && millis() - time > debounceMilli) {
    // move
    driveStepper();

    // update time and state
    time = millis();
    prevState = switchState;
  }
}

void wakeStepper() {
  digitalWrite(enablePin, LOW);
}

void sleepStepper() {
  digitalWrite(enablePin, HIGH);
}

void driveStepper() {
  // which direction do we step in? Just follow the switch.
  digitalWrite(dirPin, switchState);

  wakeStepper();

  // step
  for(int x=0; x<numSteps; x++) {
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(delayMicro);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(delayMicro);
  }
  
  delay(3000);  // 3 second delay to allow curtain to settle before releasing motor.
  sleepStepper();
}