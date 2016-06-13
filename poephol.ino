
#include <ESP8266WiFi.h>

extern "C" {
  #include "user_interface.h"
}

String alfa = "1234567890qwertyuiopasdfghjkklzxcvbnm QWERTYUIOPASDFGHJKLZXCVBNM_";
String theguy = "stheguy ";
String thedude = "sthedude";
String theman = "stheman";
String thegit = "jeff";
String insult = "";

byte channel;
int i;

// Beacon Packet buffer
uint8_t packet[128] = { 0x80, 0x00, 0x00, 0x00, 
                /*4*/   0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
                /*10*/  0x01, 0x02, 0x03, 0x04, 0x05, 0x06,
                /*16*/  0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 
                /*22*/  0xc0, 0x6c, 
                /*24*/  0x83, 0x51, 0xf7, 0x8f, 0x0f, 0x00, 0x00, 0x00, 
                /*32*/  0x64, 0x00, 
                /*34*/  0x01, 0x04, 
                /* SSID */
                /*45*/  0x00, 0x0f, 0x72, 0x72, 0x72, 0x72, 0x72, 0x72, 0x72, 0x72, 0x72, 0x72, 0x72, 0x72, 0x72, 0x72, 0x72,
                        0x01, 0x08, 0x82, 0x84,
                        0x8b, 0x96, 0x24, 0x30, 0x48, 0x6c, 0x03, 0x01, 
                /*65*/  0x04};                       


void setup() {
  delay(500);
  wifi_set_opmode(STATION_MODE);
  wifi_promiscuous_enable(1); 
}



void loop() {
    // Randomize channel //
   
    channel = random(1,12); 
    wifi_set_channel(channel);

    // Randomize SRC MAC
    packet[10] = packet[16] = random(256);
    packet[11] = packet[17] = random(256);
    packet[12] = packet[18] = random(256);
    packet[13] = packet[19] = random(256);
    packet[14] = packet[20] = random(256);
    packet[15] = packet[21] = random(256);

    // Put our asshole in the start of the SSID
    packet[38] = thegit[0];
    packet[39] = thegit[1];
    packet[40] = thegit[2];
    packet[41] = thegit[3];

    i = random(0,4);
    switch(i){
      case 0:
        insult = theguy;
        break;
      case 1:
        insult = theguy;// For some reason this doesn't get called, I think maybe it's a problem with arduino random on esp8266
      case 2:
        insult = theman;
        break;
      case 3:
        insult = thedude;
        break;
    }
    // Pick a random statement and append our passive aggressive bullshit
    
    packet[42] = insult[0];
    packet[43] = insult[1];
    packet[44] = insult[2];
    packet[45] = insult[3];
    packet[46] = insult[4];
    packet[47] = insult[5];
    packet[48] = insult[6];
    packet[49] = insult[7];

    // Add our identifier to flood the list
    packet[50] = alfa[64];
    packet[51] = alfa[random(65)];
    packet[52] = alfa[random(65)];
    
    packet[65] = channel;
    
    wifi_send_pkt_freedom(packet, 66, 0);
    wifi_send_pkt_freedom(packet, 66, 0);
    wifi_send_pkt_freedom(packet, 66, 0);
    delay(250);
}

