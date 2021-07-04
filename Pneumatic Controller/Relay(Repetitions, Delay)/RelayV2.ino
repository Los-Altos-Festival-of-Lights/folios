//This Is A Test Program To Control Multiple Digital Devices With An Arduino
//It Is Meant For Movement Patterns With A Number Of Toggles, And A Set Delay
/*
NOTE: In Order To Utilize This Code:
1.) Update 2D Array With Values, Instructions Listed Above Line
2.) Change pins_vals Dimension (First Number) To Refect Number Of Pins
3.) Change Rows, Totals, Active, And Temp Dimesnions (Except For Rows, Which Is An Int) To Reflect Number Of Terms
*/

//Each Item Is A Digital Pin
//Format: Pin#, Time Between Toggles, Repetitions (Of Toggles, 2x # Of Flashes), Delay
int pins_vals[2][4] = {{2, 250, 6, 1000}, {3, 500, 4, 2000}};
int rows = 2;

int totals[2];
boolean active[2];
int temp[2];

void setup() {
  //Set Up Pins
  pinMode(2,OUTPUT);
  pinMode(3,OUTPUT);

  //Set Up Total Times Per Motion (Digital Pin)
  for(int i=0; i<rows; i++){
    totals[i] = (pins_vals[i][1] * pins_vals[i][2]) + pins_vals[i][3];
  }
  for(int i=0; i<rows; i++){
    active[i] = false;
  }
  for(int i=0; i<rows; i++){
    temp[i] = 0;
  }
}

void loop() {
  //10 Second Interval
  for (int i = 0; i < 10000; i++) {
    //Check Each Item In 2D Array, Every Millisecond
    for (int r = 0; r < rows; r++) {
      if (i % totals[r] == 0 || active[r]) { //Check If Multiple Of Interval
        
//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//

        active[r] = true;
  
        for(int c=0; c<pins_vals[r][2]; c++){
          if(temp[r] == c*pins_vals[r][1]){
            //Toggle Pin --> Toggle Relay
            if(digitalRead(pins_vals[r][0]) == LOW){
              digitalWrite(pins_vals[r][0], HIGH);
            }
            else{
              digitalWrite(pins_vals[r][0], LOW);
            }            
          }
        }

        temp[r]++;
        if(temp[r] == totals[r]){
          temp[r] = 0;
          active[r] = false;
        }
        
//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//
      
    }
  }
  delay(1);
  }
}
