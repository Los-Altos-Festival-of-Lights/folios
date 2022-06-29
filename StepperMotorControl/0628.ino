//Stuff To Adjust
byte stepPin = 2;
byte directionPin = 3;
byte direction = 1; //In Current Configuration, 1 Is Clockwise
int slowStepsPerSec = 400;
int fastStepsPerSec = 3500;
int numAccelSteps = 1300; //Steps To Get To Top Speed, Or 1/2 of Total Distance
int delayMillis = 50;


//Other Variables
unsigned long curMicros;
unsigned long prevStepMicros = 0;
int numSteps;
int stepsLeft;
long slowMicrosBetweenSteps;
long fastMicrosBetweenSteps;
long stepIntervalMicros;
long stepAdjustmentMicros;


void setup() {
  
  pinMode(directionPin, OUTPUT);
  pinMode(stepPin, OUTPUT);
  
  numSteps = 2 * numAccelSteps;
  slowMicrosBetweenSteps = (long)((1.0 / slowStepsPerSec) * 1000000);
  fastMicrosBetweenSteps = (long)((1.0 / fastStepsPerSec) * 1000000);

  
  stepAdjustmentMicros = (slowMicrosBetweenSteps - fastMicrosBetweenSteps) / numAccelSteps; //Speed Difference / Steps
  stepIntervalMicros = slowMicrosBetweenSteps;
  stepsLeft = numSteps;
  digitalWrite(directionPin, direction);
}

void loop() {

  if (stepsLeft > 0) {
    if (micros() - prevStepMicros >= stepIntervalMicros) {
      prevStepMicros += stepIntervalMicros;
      moveStep();
      stepsLeft --;
      if (stepsLeft <= numAccelSteps) {
        if (stepIntervalMicros < slowMicrosBetweenSteps) {
          stepIntervalMicros += stepAdjustmentMicros;
        }
      }
      else {
        if (stepIntervalMicros > fastMicrosBetweenSteps) {
          stepIntervalMicros -= stepAdjustmentMicros;
        }
      }
    }
  }
  else {
    flipReset();
  }
}

void moveStep() {
  digitalWrite(stepPin, HIGH);
  digitalWrite(stepPin, LOW);
}

void flipReset(){
  direction = ! direction;
    digitalWrite(directionPin, direction);
    delay(delayMillis);
    Serial.println("Changing direction");
    stepsLeft = numSteps;
    prevStepMicros = micros();
}
