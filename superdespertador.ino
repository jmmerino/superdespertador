#include <EtherCard.h>

static byte mymac[] = { 0x74,0x69,0x69,0x2D,0x30,0x31 };
byte Ethernet::buffer[700];
BufferFiller bfill;

void setup () {
  Serial.begin(57600);
  Serial.println("\n[testDHCP]");

  Serial.print("MAC: ");
  for (byte i = 0; i < 6; ++i) {
    Serial.print(mymac[i], HEX);
    if (i < 5)
      Serial.print(':');
  }
  Serial.println();

  if (ether.begin(sizeof Ethernet::buffer, mymac) == 0)
    Serial.println( "Failed to access Ethernet controller");

  Serial.println("Setting up DHCP");
  if (!ether.dhcpSetup())
    Serial.println( "DHCP failed");

  ether.printIp("My IP: ", ether.myip);
  ether.printIp("Netmask: ", ether.netmask);
  ether.printIp("GW IP: ", ether.gwip);
  ether.printIp("DNS IP: ", ether.dnsip);
}

void loop() {

  char* response;
  word len = ether.packetReceive();
  word pos = ether.packetLoop(len);


  if(pos) {
    bfill = ether.tcpOffset();

    if(strstr((char *)Ethernet::buffer + pos, "GET /home") != 0) {
      navigateHome();
    }

    if(strstr((char *)Ethernet::buffer + pos, "GET /menu") != 0) {
      navigateMenu();
    }

    // bfill.emit_raw(response, strlen(response));
    ether.httpServerReply(bfill.position());
  }
}

void html() {
  bfill.emit_p(PSTR("<html>"));
  bfill.emit_p(PSTR("<meta name=\"viewport\" content=\"initial-scale=1.0, maximum-scale=1.0, user-scalable=no, minimal-ui\">"));
}
void end_html() {
  bfill.emit_p(PSTR("</html>"));
}


void navigateMenu() {
  html();
  css();
  bfill.emit_p(PSTR("<body>"));
  bfill.emit_p(PSTR("<h1>menu</h1>"));
  bfill.emit_p(PSTR("<li><a href='/home'>home</a></h1>"));
  common_javascript();
  bfill.emit_p(PSTR("</body>"));
  end_html();
}


void navigateHome() {
  html();
  css();
  bfill.emit_p(PSTR("<body>"));
  bfill.emit_p(PSTR("<div class='app-page' data-page='home'>"
                      "<div class='app-topbar blue'>"
                        "<div class='app-title'>"
                          "Superdespertador"
                        "</div>"
                      "</div>"
                      "<div class='app-content'>"
                        "<div class='app-section'>"
                        "Esta es la home"
                        "</div>"
                      "</div>"
                    "</div>"));
  common_javascript();
  bfill.emit_p(PSTR("<script>"
    "try {"
        "App.restore();"
      "} catch (err) {"
        "App.load('home');"
      "}"
    "</script>"));
  bfill.emit_p(PSTR("</body>"));
  end_html();
}

void common_javascript() {
  bfill.emit_p(PSTR("<script src='//zeptojs.com/zepto.min.js'></script>"));
  bfill.emit_p(PSTR("<script src='//cdn.kik.com/app/2.0.1/app.min.js'></script>"));

}
void css() {
  bfill.emit_p(PSTR("<head>"));
  bfill.emit_p(PSTR("<link rel='stylesheet' href='//cdn.kik.com/app/2.0.1/base.css'>"));
  bfill.emit_p(PSTR("<link rel='stylesheet' href='//cdn.kik.com/app/2.0.1/app.min.css'>"));

  bfill.emit_p(PSTR("</head>"));
}
