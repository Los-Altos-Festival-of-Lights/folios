/*
This code is to control multiple digital pins, with a set frequency between toggles. Pins are controlled by adding terms to the array.
 */

int pins_vals[4][2] = {{2, 250}, {3, 500},{4,1000}};
int rows = 3;

void setup() {
  // put your setup code here, to run once:
    pinMode(2,OUTPUT);
    pinMode(3,OUTPUT);
    pinMode(4,OUTPUT);
}
void loop() {
  //10 Second Interval
  for (int i = 0; i < 10000; i++) {
    //Check Each Item In 2D Array, Every Millisecond
    for (int r = 0; r < rows; r++) {
      if (i % pins_vals[r][1] == 0) { //Check If Multiple Of Interval
        //Toggle Pin --> Toggle Relay
        if(digitalRead(pins_vals[r][0]) == LOW){
          digitalWrite(pins_vals[r][0], HIGH);
        }
        else{
          digitalWrite(pins_vals[r][0], LOW);
        }
    }
  }
  delay(1);
  }
}
