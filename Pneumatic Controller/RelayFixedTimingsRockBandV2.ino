//Explanation: This Is Code To Control Arduino Digital Pins, With Set Times For Toggles
//To Make This Code Work With Your Values, Do The Following:
/*
 * 1.) Update pinNumber to reflect number of used pins.
 * 2.) Update choreographyLegth to reflect length of choreography in milliseconds.
 */

//Variables To Modify Below

#define pinNumber 18
#define choregographyLength 12000


int pinTimes[pinNumber][50] = {
  
{1, 500, 1000, 1500, 2000}, //Singer Foot
{2, 0, 500, 1000, 1500}, //Singer Mic
{3, 0, 6733}, //Singer Head Left
//{4,}, //Singer Head Right
{5, 1701, 2602, 3602, 4170, 5405, 6339, 7339, 7907, 9075, 10010, 11010, 11578}, //Singer Body Right
{6, 0, 666, 1233, 1434, 1701, 2602, 3602, 4170, 6733, 7907, 8641, 8842, 9075, 10010, 11010, 11578}, //Singer Mouth
{7, 0, 500, 1234, 1434, 1701, 2602, 3602, 4170, 4971, 5171, 5405, 6339, 7339, 7907, 8641, 8842, 9075, 10010, 11010, 11578}, //Guitar On Floor Arn
//{8,}, //Guitar On Floor Head Left
//{9,}, //Guitar On Floor Head Right
{10, 1701, 2602, 3602, 4170, 5405, 6339, 7339, 7907, 9075, 10010, 11010, 11578}, //Floor Guitar Body
{11, 1701, 2602, 3602, 4170, 9075, 10010, 11010, 11578}, //Guiar On Floor Mouth
{12, 0, 1553, 1966, 2399, 2832, 3265, 3698, 4131, 4564, 4997, 5430, 5863, 6296, 6729, 7162, 7595, 8028, 8461, 8894, 9327, 9760, 10193, 10626, 11059, 11492, 11925}, //Drummer Left Hand, Drum
{13, 0, 500, 1000, 4170, 4670, 7907, 8407}, //Drummer Right Hand, Cymbal
{14, 1701, 2602, 3602, 4170, 5405, 6339, 7339, 7907, 9075, 10010, 11010, 11578}, //Drummer Mouth
{15, 1701, 2602, 3602, 4170, 9075, 10010, 11010, 11578}, //Drummer Mouth
{16, 0, 500, 1234, 1434, 1701, 2602, 3602, 4170, 4971, 5171, 5405, 6339, 7339, 7907, 8641, 8842, 9075, 10010, 11010, 11578}, //Guitar On Stand Arm
{17, 1701, 2602, 3602, 4170, 5405, 6339, 7339, 7907, 9075, 10010, 11010, 11578}, //Guitar On Stand Body
{18, 1701, 2602, 3602, 4170, 9075, 10010, 11010, 11578} //Stand Guitar Mouth

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
