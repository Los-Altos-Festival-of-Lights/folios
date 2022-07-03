class StepperMotor {

  private:

    //Stuff To Set In COnstructor
    byte stepPin;
    byte directionPin;
    byte direction; //In Current Configuration, 1 Is Clockwise
    int slowStepsPerSec;
    int fastStepsPerSec;
    int numAccelSteps; //Steps To Get To Top Speed, Or 1/2 of Total Distance
    int delayMillis;


    //Other Variables
    unsigned long curMicros;
    unsigned long prevStepMicros = 0;
    int numSteps;
    int stepsLeft;
    long slowMicrosBetweenSteps;
    long fastMicrosBetweenSteps;
    long stepIntervalMicros;
    long stepAdjustmentMicros;

  public:
    //Contructor
    StepperMotor(byte stepPin, byte directionPin, byte direction, int slowStepsPerSec, int fastStepsPerSec, int numAccelSteps, int delayMillis, int startDelay) {
      this->stepPin = stepPin;
      this->directionPin = directionPin;
      this->direction = direction;
      this->slowStepsPerSec = slowStepsPerSec;
      this->fastStepsPerSec = fastStepsPerSec;
      this->numAccelSteps = numAccelSteps;
      this->delayMillis = delayMillis;

      pinMode(directionPin, OUTPUT);
      pinMode(stepPin, OUTPUT);
      
      numSteps = 2 * numAccelSteps;
      slowMicrosBetweenSteps = (long)((1.0 / slowStepsPerSec) * 1000000);
      fastMicrosBetweenSteps = (long)((1.0 / fastStepsPerSec) * 1000000);
      
      stepAdjustmentMicros = (slowMicrosBetweenSteps - fastMicrosBetweenSteps) / numAccelSteps; //Speed Difference / Steps
      stepIntervalMicros = slowMicrosBetweenSteps;
      stepsLeft = numSteps;
      digitalWrite(directionPin, direction);
  
      delay(startDelay);
    }

    void moveMotor() {
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

    void flipReset() {
      direction = ! direction;
      digitalWrite(directionPin, direction);
      delay(delayMillis);
      Serial.println("Changing direction");
      stepsLeft = numSteps;
      prevStepMicros = micros();
    }

};


//StepperMotor stepper# (stepPin, dirPin, direction, slowSteps/Sec, fastSteps/sec, numAccelSteps, delayMillis, startDelay)
StepperMotor stepper1 (2, 3, 1, 400, 3500, 1300, 50, 0);

void setup(){ }
void loop(){
  stepper1.moveMotor();
}
