#include <SPI.h>
#include <Ethernet.h>
#include <E131.h>
E131 e131;

//Ethernet Configuration
byte mac[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED};
uint8_t ip[] = {192, 168, 2, 253};
uint8_t subnet[] = {255, 255, 255, 0};
uint8_t gateway[] = {192, 168, 2, 69};
uint8_t dns[] = {0, 0, 0, 0};

//Number Of Digital Output Pins Being Used
#define pins 18

//{Digital_Output_Pin, E1.31 Channel}
int ports[pins][2] = {

  {1, 0},
  {2, 1},
  {3, 2},
  {5, 3},
  {6, 4},
  {7, 5},
  {8, 5},
  {9, 6},
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

boolean active[pins];


void setup() {

  for (int i = 0; i < pins; i++) {
    pinMode(ports[i][0], OUTPUT);
    active[i] = false;
  }

  //Set Up Printing
  Serial.begin(9600);
  Serial.println("");
  Serial.println("Initialized Serial Printing (9600)");

  //Startup Sequence To Test Relays, Should Just Flash Going Down The Line
  Serial.println("Testing Relays");
  for (int i = 0; i < pins; i++) {
    digitalWrite(ports[i][0], HIGH);
    delay(1000);
    digitalWrite(ports[i][0], LOW);
    delay(1000);
  }

  //Disable SD Card
  pinMode(4, OUTPUT);
  digitalWrite(4, HIGH);
  Serial.println("Disabled SD Card On Ethernet Shield");

  //Initalize E1.31
  e131.begin(mac, ip, gateway, subnet, dns);
  Serial.println("\nSucsesfully Initialized E1.31\n");
}

void loop() {

  //Parse A Packet
  uint16_t num_channels = e131.parsePacket();
  /*Serial.print("NUMCHANNELS: ");
    Serial.println(num_channels);*/

  //Print Channel Data
  if (num_channels) {

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
  else {
    Serial.println("No E1.31 Data");
  }

  Serial.println("");

  //Updating E1.31 Values
  for (int i = 0; i < pins; i++) {
    if (e131.data[ports[i][1]] < 127) {
      active[i] = true;
    }
    else {
      active[i] = false;
    }
  }

  //Refelcting E1.31 Values To Pins
  for (int i = 0; i < pins; i++) {
    if (active[i]) {
      digitalWrite(ports[i][0], HIGH);
    }
    else {
      digitalWrite(ports[i][1], LOW);
    }
  }

  delay(5);
}
