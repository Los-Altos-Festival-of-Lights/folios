byte stepPin = 2;
byte directionPin = 3;


int slowStepsPerSec = 400;
int fastStepsPerSec = 3500;
int numAccelSteps = 1300;


unsigned long curMicros;
unsigned long prevStepMicros = 0;

int numSteps;
int stepsToGo;
byte direction = 1;

long slowMicrosBetweenSteps;
long fastMicrosBetweenSteps;

long stepIntervalMicros;
long stepAdjustmentMicros;











void setup() {

    Serial.begin(115200);

    slowMicrosBetweenSteps = (long)((1.0/slowStepsPerSec)*1000000);
    fastMicrosBetweenSteps = (long)((1.0/fastStepsPerSec)*1000000);

    numSteps = 2*numAccelSteps;
   

    pinMode(directionPin, OUTPUT);
    pinMode(stepPin, OUTPUT);

    stepAdjustmentMicros = (slowMicrosBetweenSteps - fastMicrosBetweenSteps) / numAccelSteps; //Speed Difference / Steps
    stepIntervalMicros = slowMicrosBetweenSteps;
    stepsToGo = numSteps;
    digitalWrite(directionPin, direction);
}

void loop() {

    moveMotor();

}

void moveMotor() {
    if (stepsToGo > 0) {
        if (micros() - prevStepMicros >= stepIntervalMicros) {
            prevStepMicros += stepIntervalMicros;
            singleStep();
            stepsToGo --;
            if (stepsToGo <= numAccelSteps) {
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
        direction = ! direction;
        digitalWrite(directionPin, direction);
            // next two lines just for the demo
        delay(50);
        Serial.println("Changing direction");
        stepsToGo = numSteps;
        prevStepMicros = micros();
    }
}

void singleStep() {
    digitalWrite(stepPin, HIGH);
    digitalWrite(stepPin, LOW);

}
