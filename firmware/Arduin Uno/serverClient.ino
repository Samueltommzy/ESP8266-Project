
#include <ESP8266WiFi.h>
const char* ssid = "";
const char* password = "";
String resp = "";
String ipAddress = "";
IPAddress ip_;
boolean t = false;
WiFiServer server(80);

void setup() {
  Serial.begin(9600);
  Serial.setTimeout(150);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }
  server.begin();
  ip_ = WiFi.localIP();
}

void loop() {
  if(t == false)
  {
    ipAddress += ip_[0];
    ipAddress += ".";
    ipAddress += ip_[1];
    ipAddress += ".";
    ipAddress += ip_[2];
    ipAddress += ".";
    ipAddress += ip_[3];
    ipAddress += "ip";
    Serial.println(ipAddress);
    t = true;
    }
  WiFiClient client = server.available();
  if (!client){
    return;
  }
  while(!client.available()){
    delay(1);
  }
  String req = client.readStringUntil('\r');
  Serial.println(req);
  client.flush();
  while(!Serial.available())
  {
    //do nothing
    }
  while(Serial.available())
  {
    resp = Serial.readString();
    }
  delay(50);
  writeResponse(client, resp);
  resp = "";
}

void writeResponse(WiFiClient& client, String response_text)
{
  client.flush();
  String s = "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\n";
  s += response_text;
  client.println(s);
  s = "";
  }

