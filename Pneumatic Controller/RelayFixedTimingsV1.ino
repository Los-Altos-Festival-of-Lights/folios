//This Just Has 3 Pin Test Values...Rockband Values In V2

//Explanation: This Is Code To Control Arduino Digital Pins, With Set Times For Toggles
//To Make This Code Work With Your Values, Do The Following:
/*
 * 1.) Update pinTimes" First Number Is Digital Pin Number, Rest Are Times For Toggles
 * 2.) Set Length Of Cout And Value Of pins To Reflect Number o=Of Pins
 * 3.) Set totalTime To Reflect Total Time Length
 */


int pinTimes[3][31] = {{2, 500, 1000, 1500, 2000}, {3, 0, 500, 1000, 1500}, {4, 0, 500, 2000, 3000}};
int count[3];
int pins = 3;
int totalTime = 3000;

void setup() {
  // put your setup code here, to run once:

  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);

  for (int i = 0; i < pins; i++) {
    count[i] = 1 ;
  }

}

void loop() {
  // put your main code here, to run repeatedly:

  for (int i = 0; i < totalTime; i++) {
    for (int n = 0; n < pins; n++) {
      if (pinTimes[n][count[n]] == i) {

        //Toggle
        if (digitalRead(pinTimes[n][0]) == LOW) {
        digitalWrite(pinTimes[n][0], HIGH);
        }
        else {
          digitalWrite(pinTimes[n][0], LOW);
        }

        count[n]++;

      }
    }

    delay(1);
  }

  for (int i = 0; i < pins; i++) {
    count[i] = 1 ;
  }
}
