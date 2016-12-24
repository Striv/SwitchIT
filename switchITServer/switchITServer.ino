#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266WebServer.h>

ESP8266WiFiMulti wifiMulti;
const char* SSID1 = "Strivelli3";
const char* SSID2 = "Strivelli1";
const char* PASS = "b5aea50a33";

enum command {
  ON, OFF, TOGGLE, BLINK, CURR_STATUS
};

ESP8266WebServer server(80);

const int outlet1 = 13;
const int outlet2 = 12;
const int outlet3 = 14;
const int outlet4 = 16;

void handleRoot() {
  server.send(200, "text/plain", "\n");
}

void handleNotFound(){
  String message = "File not Found";
  server.send(404, "text/plain", message);
}

int currStatus(int outletPin){
  return digitalRead(outletPin);
}

void turnOn(int outletPin){
  digitalWrite(outletPin, HIGH);
}

void turnOff(int outletPin){
  digitalWrite(outletPin, LOW);
}

void toggle(int outletPin){
  digitalWrite(outletPin, !digitalRead(outletPin));
}

void my_blink (int outletPin){
  int d = 500; // ms for delay
  int n = 3; // num times to blink
  
  for(int i = 0; i < n; i++){
    digitalWrite(outletPin, LOW);
    delay(d);
    digitalWrite(outletPin, HIGH);
    delay(d);
  }
}

void all(command c){
  one(outlet1, c);
  one(outlet2, c);
  one(outlet3, c);
  one(outlet4, c);
}

void one(int outletPin, command c){
  switch(c){
    case ON:
      turnOn(outletPin);
      break;
    case OFF:
      turnOff(outletPin);
      break;
    case TOGGLE:
      toggle(outletPin);
      break;
    case BLINK:
      my_blink(outletPin);
      break;
    case CURR_STATUS:
      Serial.println("OUTLET PIN " + String(outletPin) + ": " + currStatus(outletPin));
      break;
  }
}

void setup(void){
  pinMode(outlet1, OUTPUT);
  pinMode(outlet2, OUTPUT);
  pinMode(outlet3, OUTPUT);
  pinMode(outlet4, OUTPUT);
  Serial.begin(115200);
  wifiMulti.addAP(SSID1, PASS);
  wifiMulti.addAP(SSID2, PASS);
   
  Serial.println("");

  // Wait for connection
  while (wifiMulti.run() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  
  if(wifiMulti.run() == WL_CONNECTED) {
        Serial.println("");
        Serial.println("WiFi connected");
        Serial.println("IP address: ");
        Serial.println(WiFi.localIP());
  }

  server.on("/", handleRoot);
  
  server.on("/all/on", [](){
      command c = ON;
      all(c);
      server.send(200, "text/plain", "ALL ON");
   });

  server.on("/all/off", [](){
      command c = OFF;
      all(c);
      server.send(200, "text/plain", "ALL OFF");
   });

  server.on("/all/blink", [](){
      command c = BLINK;
      all(c);
      server.send(200, "text/plain", "ALL BLINK");
   });

  server.on("/all/toggle", [](){
      command c = TOGGLE;
      all(c);
      server.send(200, "text/plain", "ALL TOGGLE");
   });

   server.on("/all/status", [](){
      command c = CURR_STATUS;
      all(c);
      server.send(200, "text/plain", "ALL STATUS");
   });
  
  server.on("/1/off", [](){
    turnOff(outlet1);
    server.send(200, "text/plain", "1 off");
  });
  server.on("/1/on", [](){
    turnOn(outlet1);
    server.send(200, "text/plain", "1 on");
  });
  server.on("/1/blink", [](){
    my_blink(outlet1);
    server.send(200, "text/plain", "1 blink");
  });
  server.on("/1/toggle", [](){
    toggle(outlet1);
    server.send(200, "text/plain", "1 toggle");
  });
  server.on("/1/status", [](){
    server.send(200, "text/plain", "Outlet 1: " + String(currStatus(outlet1)));
  });

  server.on("/2/off", [](){
    turnOff(outlet2);
    server.send(200, "text/plain", "2 off");
  });
  server.on("/2/on", [](){
    turnOn(outlet2);
    server.send(200, "text/plain", "2 on");
  });
  server.on("/2/blink", [](){
    my_blink(outlet2);
    server.send(200, "text/plain", "2 blink");
  });
  server.on("/2/toggle", [](){
    toggle(outlet2);
    server.send(200, "text/plain", "2 toggle");
  });
  server.on("/2/status", [](){
    server.send(200, "text/plain", "Outlet 2: " + String(currStatus(outlet2)));
  });

  server.on("/3/off", [](){
    turnOff(outlet3);
    server.send(200, "text/plain", "3 off");
  });
  server.on("/3/on", [](){
    turnOn(outlet3);
    server.send(200, "text/plain", "3 on");
  });
  server.on("/3/blink", [](){
    my_blink(outlet3);
    server.send(200, "text/plain", "3 blink");
  });
  server.on("/3/toggle", [](){
    toggle(outlet3);
    server.send(200, "text/plain", "3 toggle");
  });
  server.on("/3/status", [](){
    server.send(200, "text/plain", "Outlet 3: " + String(currStatus(outlet3)));
  });

  server.on("/4/off", [](){
    turnOff(outlet4);
    server.send(200, "text/plain", "4 off");
  });
  server.on("/4/on", [](){
    turnOn(outlet4);
    server.send(200, "text/plain", "4 on");
  });
  server.on("/4/blink", [](){
    my_blink(outlet4);
    server.send(200, "text/plain", "4 blink");
  });
  server.on("/4/toggle", [](){
    toggle(outlet4);
    server.send(200, "text/plain", "4 toggle");
  });
  server.on("/4/status", [](){
    server.send(200, "text/plain", "Outlet 4: " + String(currStatus(outlet4)));
  });
  
  server.onNotFound(handleNotFound);

  server.begin();
  Serial.println("HTTP server started");
}

void loop(void){
  server.handleClient();
}
