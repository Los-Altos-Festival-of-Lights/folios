//Explanation: This Is Code To Control Arduino Digital Pins, With Set Times For Toggles
//To Make This Code Work With Your Values, Do The Following:
/*
 * 1.) Update pinNumber to reflect number of used pins.
 * 2.) Update choreographyLegth to reflect length of choreography in milliseconds.
 * 3.) Input Values Into Array (First Value Is Pin#, Rest Are Toggles (Milliseconds)
 * 4.) Set Slaves COnstant To Reflect Number of Slave Cylinders
 * 5.) Input Slave Cylinder Numbers Into slaveArray, In The Format Of Master, Slave
 *     ex:) Pin 1 Switches At 500, 750, 1000  --> {1, 500, 750, 1000}
 */

//Variables To Modify Below

#define pinNumber 18
#define choregographyLength 1000
#define slaves 2


int pinTimes[pinNumber][50] = {
  
{1, 0}, //Singer Foot
{2, 0}, //Singer Mic
{3, 0}, //Singer Head Left
//{4,}, //Singer Head Right
{5, 0}, //Singer Body Right
{6, 0}, //Singer Mouth
{7, 0}, //Guitar On Floor Arn
{8,}, //Guitar On Floor Head Left
//{9,}, //Guitar On Floor Head Right
{10, 0}, //Floor Guitar Body
{11, 0}, //Floor Guitar Mouth
{12, 0}, //Drummer Left Hand, Drum
{13, 0}, //Drummer Right Hand, Cymbal
{14, 0}, //Drummer Mouth
{15, 0}, //Drummer Mouth
{16, 0}, //Guitar On Stand Arm
{17, 0}, //Guitar On Stand Body
{18, 0} //Stand Guitar Mouth

};

int slaveArray[slaves][2] = {

  {3, 4},
  {8, 9}
};

//Variables To Modify Above

int count[pinNumber];
int pins = pinNumber;
int totalTime = choregographyLength;

void setup() {
  // put your setup code here, to run once:

  for(int i=1; i<= pins; i++){
    pinMode(i, OUTPUT);
  }

  for (int i = 0; i < pins; i++) {
    count[i] = 1 ;
  }

}

void loop() {
  //Regular Pins:

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

    //Slaves:
    for(int i = 0; i < slaves; i++){
      if(digitalRead(slaveArray[i][0]) == LOW){
        digitalWrite(slaveArray[i][1], HIGH);
      }
      else{
        digitalWrite(slaveArray[i][1], LOW);
      }
    }
    delay(1);
  }

  for (int i = 0; i < pins; i++) {
    count[i] = 1 ;
  }
}

/*
 * Change Log:
 * V2: Added Master Slave Comatibility
 * /
 */
