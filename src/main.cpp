#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
// Set WiFi credentials
#define WIFI_SSID "gsom"
#define WIFI_PASS "qz!813_gg1"
//server addr
#define SRV "192.168.0.146"
//server port
#define UDP_PORT 4210
//buttons pins
#define BUTTON1 2
#define BUTTON2 14
#define BUTTON3 12
#define BUTTON4 13
#define LED 3
//payloads
String PAYLOAD1on = "venton";
String PAYLOAD2on = "svet1on";
String PAYLOAD3on = "Con";
String PAYLOAD4on = "Don";
String PAYLOAD1off = "ventoff";
String PAYLOAD2off = "svet1off";
String PAYLOAD3off = "Coff";
String PAYLOAD4off = "Doff";
bool count1 = false;
bool count2 = false;
bool count3 = false;
bool count4 = false;

// UDP
WiFiUDP UDP;
bool prevState1 = true;
bool prevState2 = true;
bool prevState3 = true;
bool prevState4 = true;
bool State1 = true;
bool State2 = true;
bool State3 = true;
bool State4 = true;
unsigned char udpSend(const char *msg);
void setup()
{
  // Setup serial port
  Serial.begin(115200);
  Serial.println();
  // Begin WiFi
  WiFi.begin(WIFI_SSID, WIFI_PASS);
  // Connecting to WiFi...
  Serial.print("Connecting to ");
  Serial.print(WIFI_SSID);
  // Loop continuously while WiFi is not connected
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(100);
    Serial.print(".");
  }
  // Connected to WiFi
  Serial.println();
  Serial.print("Connected! IP address: ");
  Serial.println(WiFi.localIP());
  pinMode(BUTTON1, INPUT_PULLUP);
  pinMode(BUTTON2, INPUT_PULLUP);
  pinMode(BUTTON3, INPUT_PULLUP);
  pinMode(BUTTON4, INPUT_PULLUP);
  pinMode(LED,OUTPUT);
}

void loop()
{
  State1 = digitalRead(BUTTON1);
  State2 = digitalRead(BUTTON2);
  State3 = digitalRead(BUTTON3);
  State4 = digitalRead(BUTTON4);
  if (State1 == HIGH && prevState1 == LOW)
  {
    count1=!count1;
    Serial.println(udpSend((count1?PAYLOAD1on:PAYLOAD1off).c_str()));
  }
  if (State2 == HIGH && prevState2 == LOW)
  {
    count2=!count2;
    Serial.println(udpSend((count2?PAYLOAD2on:PAYLOAD2off).c_str()));
  }
  if (State3 == HIGH && prevState3 == LOW)
  {
    count3=!count3;
    Serial.println(udpSend((count3?PAYLOAD3on:PAYLOAD3off).c_str()));
  }
  if (State4 == HIGH && prevState4 == LOW)
  {
    count4=!count4;
    Serial.println(udpSend((count4?PAYLOAD4on:PAYLOAD4off).c_str()));
  }
  prevState1 = State1;
  prevState2 = State2;
  prevState3 = State3;
  prevState4 = State4;
  if (count1&&count2&&count3&&count4)
  {
    digitalWrite(LED,LOW);
  }
  else{
    digitalWrite(LED,HIGH);
  }
  
  delay(100);
}

unsigned char udpSend(const char *msg)
{
  UDP.beginPacket(SRV, UDP_PORT);
  Serial.print(msg);
  UDP.write(msg);
  return UDP.endPacket();
}