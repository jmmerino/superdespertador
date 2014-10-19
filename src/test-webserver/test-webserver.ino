// This is a demo of the RBBB running as webserver with the Ether Card
// 2010-05-28 <jc@wippler.nl> http://opensource.org/licenses/mit-license.php

#include <EtherCard.h>
#include <SD.h>

// ethernet interface mac address, must be unique on the LAN
static byte mymac[] = { 0x74,0x69,0x69,0x2D,0x30,0x31 };
static byte myip[] = { 192,168,0,17 };

byte Ethernet::buffer[500];
BufferFiller bfill;

File myFile;

int ethernetSS = 8;
int sdSS = 4;

void setup () {
  Serial.begin(9600);

  if (ether.begin(sizeof Ethernet::buffer, mymac) == 0)
    Serial.println( "Failed to access Ethernet controller");
  ether.staticSetup(myip);

  configureSDCard();
}


void configureSDCard(){

  if (!SD.begin(4)) {
    Serial.println("initialization failed!");
    return;
  }

  Serial.println("SD OK");

}

void navigateHome(){
  digitalWrite(sdSS, HIGH);
  digitalWrite(ethernetSS, LOW);

  // open the file for reading:
  myFile = SD.open("home.htm");

  digitalWrite(sdSS, LOW);
  digitalWrite(ethernetSS, HIGH);

  if (myFile) {
    Serial.println("home.htm");

    // // read from the file until there's nothing else in it:
    while (myFile.available()) {
      Serial.write(myFile.read());
      // bfill.write( myFile.read() );
    }
    // // close the file:
    // myFile.close();
  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening home.htm");
  }


}

static word homePage() {
  long t = millis() / 1000;
  word h = t / 3600;
  byte m = (t / 60) % 60;
  byte s = t % 60;
  bfill = ether.tcpOffset();

  navigateHome();

  // bfill.emit_p(PSTR(
  //   "HTTP/1.0 200 OK\r\n"
  //   "Content-Type: text/html\r\n"
  //   "Pragma: no-cache\r\n"
  //   "\r\n"
  //   "<meta http-equiv='refresh' content='1'/>"
  //   "<title>RBBB server</title>"
  //   "<h1>$D$D:$D$D:$D$D</h1>"),
  //     h/10, h%10, m/10, m%10, s/10, s%10);
  return bfill.position();
}

void loop () {
  word len = ether.packetReceive();
  word pos = ether.packetLoop(len);

  if (pos)  // check if valid tcp data is received
    ether.httpServerReply(homePage()); // send web page data
}
