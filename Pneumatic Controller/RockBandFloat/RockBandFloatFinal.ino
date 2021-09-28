//This Is Our "Final" Relay Code, Which Is Tested And Working.
//How To Use: Update Values Shown Below Lines With "CONFIGURE"

#include <SPI.h>
#include <Ethernet.h>
#include <E131.h>

byte mac[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED};

//CONFIGURE: Make These Values Reflect The Network The Falcon Player Is On
uint8_t ip[] = {192, 168, 2, 253};
IPAddress ipAdd(192, 168, 2, 253);
uint8_t subnet[] = {255, 255, 255, 0};
uint8_t gateway[] = {192, 168, 2, 69};
uint8_t dns[] = {0, 0, 0, 0};

E131 e131;

//CONFIGURE: This Is The Number Of Digital Pins Being Used (Same As Number of Relays)
int pins = 18;

//CONFIGURE: Set Rows Parameter In Array To Same As "pins" (Above)
//CONFIGURE: Update Values In Array With Format Below

//Format: {Arduino Digital Output Pin, xLights Sequence Channel}
//Note: This Code Defaults To Using Universe 1
//Note: The Arduino Ethernet Shield Uses Pins 1, 4, and 10-13 For Communication To The Arduino. You Cannot Use These Pins For Relays

int ports[18][2] = {

  {48, 0},
  {2, 1},
  {3, 2},
  {5, 3},
  {6, 4},
  {7, 5},
  {8, 6},
  {9, 7},
  {30, 8},
  {31, 9},
  {32, 10},
  {33, 11},
  {34, 12},
  {35, 13},
  {36, 14},
  {37, 15},
  {38, 16},
  {39, 17}

};

/*
1: Singer Foot
2: Singer Mic
3: Singer Head Left
4: Singer Head Right
5: Singer Body  Right
6: Singer Mouth
7: Floor Guitar Arm
8: Floor Guitar Head Left
9: Floor Guitar Head Right
10: Floor Guitar Body
11: Floor Guitar Mouth
12: Drummer Left Hand (Drum)
13: Drummer Right Hand (Cymbal)
14: Drummer Mouth
15: Drummer Body
16: Guitar On Stand Arm
17: Guitar On Stand Body
18: Guitar On Stand Mouth
Note: Numbers 4&5, and Numbers 8&9, Can Never Be Active At The Same Time Because They Contradict Each Other
*/


void setup() {

  for (int i = 0; i < pins; i++) {
    pinMode(ports[i][0], OUTPUT);
  }


  //Disable SD Card
  pinMode(4, OUTPUT);
  digitalWrite(4, HIGH);

  //Set Up Printing
  Serial.begin(9600);
  Serial.println("");
  Serial.println("Initialized Serial Printing (9600)");

  //Initalize E1.31
  e131.begin(mac, ip, gateway, subnet, dns);
  Serial.println("\nSucsesfully Initialized E1.31\n");
}

void loop() {

  //Reset Ethernet Connection If Dropped
  if(Ethernet.localIP() != ipAdd){
    e131.begin(mac, ip, gateway, subnet, dns);
  }

  //Parse A Packet
  uint16_t num_channels = e131.parsePacket();
  
  //For Troubleshooting You Can Uncomment These Blocks To View E1.31 Data
  
  /*Serial.print("NUMCHANNELS: ");
  Serial.println(num_channels);*/

  //Print Channel Data
  /*if (num_channels) {
    Serial.print(F("Universe: "));
    Serial.println(e131.universe);
    Serial.print("Num Channels: ");
    Serial.println(num_channels);
    Serial.print("Errors: ");
    Serial.println(e131.stats.packet_errors);
    for (int i = 0; i < num_channels; i++) {
      Serial.print("Channel ");
      Serial.print(i + 1);
      Serial.print(": ");
      Serial.println(e131.data[i]);
    }
  }
  Serial.println("");*/

  for(int i=0; i<pins; i++){
    if(e131.data[ports[i][1]] < 200){
      digitalWrite(ports[i][0], HIGH);     
    }
    else{
      digitalWrite(ports[i][0], LOW);
    }
  }

  delay(1);  
}
