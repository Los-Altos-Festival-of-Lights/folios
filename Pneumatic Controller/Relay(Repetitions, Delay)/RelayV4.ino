//This Is A Test Program To Control Multiple Digital Devices With An Arduino
//It Is Meant For Movement Patterns With A Number Of Toggles, And A Set Delay

/*
NOTE: In Order To Utilize This Code:
1.) Update 2D Array With Values, Instructions Listed Above Line
2.) Change Rows Integer To Reflect Number Of Pins
3.) In Setup, Configure Utilized Digital Pins To Serve As Output
*/

//Each Item Is A Digital Pin
//Format: Pin#, Time Between Toggles, Repetitions (Of Toggles, 2x # Of Flashes), Delay
int pins_vals[53][4] = {{2, 100, 8, 500}, {3, 250, 6, 1000}, {4, 500, 4, 2000}};

int rows = 3;
//Note: The Rows Variable Needs To Be Set Because There Is A Noticeable Time Penalty If It Is Just Set To 53
//The Below Array Lengths Can Be 53 Because Never Does The Program GO Through All Of Them, It Only References Specific Adresses
//There Are 53 Pins On The Arduino Mega. If Using A Bigger Or Smaller Board, Change The Array Lengths To Be Accurate

int totals[53];
boolean active[53];
int temp[53];

int cycle;

void setup() {

  //Set Up Pins
  pinMode(2,OUTPUT);
  pinMode(3,OUTPUT);
  pinMode(4, OUTPUT);

  //Set Up Total Times Per Motion (Digital Pin)
  for(int i=0; i<rows; i++){
    totals[i] = (pins_vals[i][1] * pins_vals[i][2]) + pins_vals[i][3];
  }
  //Set Up Temporary Array To Know If Sequence Has Started
  for(int i=0; i<rows; i++){
    active[i] = false;
  }
  //Set Up Timers Per Sequence
  for(int i=0; i<rows; i++){
    temp[i] = 0;
  }

  //Set Up Cycle Length By Making A Number Which Is Divisable By All Individual Pin Increments
  cycle = 1;
  for(int i=0; i<rows; i++){
    cycle = cycle * ((pins_vals[i][1] * pins_vals[i][2]) + pins_vals[i][3]); //Times Totals, Cannot Acces Array Yet
  }
}

void loop() {
  //Interval
  for (int i = 0; i <= cycle; i++) {
    //Check Each Item In 2D Array, Every Millisecond
    for (int r = 0; r < rows; r++) {
      if (i % totals[r] == 0 || active[r]) { //Check If Multiple Of Interval 
             
        //If Sequence Should Start, Trigger Active Array
        active[r] = true;
        
        //If Sequence Has Been Active For Multiple Of Toggle Length, Toggle
        for(int c=0; c<pins_vals[r][2]; c++){
          
          //Checks Multiples Based On Number Of Toggles
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

        //Increase Counter For Sequence
        temp[r]++;

        //If Sequence Complete, Reset Counter, Change To Not Active
        if(temp[r] == totals[r]){
          temp[r] = 0;
          active[r] = false;
        }  
      }
   }
  delay(1);
  }
}

/*
Change Log:
V1: Basic Cycle, On/Off With Timer
V2: Added Number Of Flashes, Flash Length, And Delay
V3: Dynamic Cycle Length, Based On Common Multiple
V4: Made Utilization Easier By Reducing Variables To Change, Added More Comments
*/
