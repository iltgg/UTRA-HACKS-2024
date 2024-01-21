#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClientSecure.h>
#include <Wire.h>

const char* ssid = "SM-SAT";
const char* password = "kfcsus56";
String id = "";
int dataCounter = 0;
String json;
ESP8266WebServer server(80);

void setup() {
  Serial.begin(9600);
  delay(100);
  Serial.println("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  //check wi-fi is connected to wi-fi network
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected..!");
  Serial.print("Got IP: ");
  Serial.println(WiFi.localIP());

  Wire.begin(4);                // join i2c bus with address #4
  Wire.onReceive(dataReceive);  // register event

  json.reserve(10000);
  json = "";
  resetData();
  setID();
}

// int stop = 0;

void loop() {
  delay(1000);
  // if (stop == 1) { return; }
  // for (int i = 0; i < 106; i++) {
  //   addData((short)i);
  //   if (dataCounter == 99) {
  //     flushData();
  //     resetData();
  //   }
  // }
  // flushData();
  // stop = 1;
}


void resetData() {
  json = "{\"app\":\"2\",\"records\": [";
  dataCounter = 0;
}

void addData(short distance) {
  json += "{\"distance\":{\"value\":";
  json += String(distance);
  json += "},";
  // json += "\"angle\":{\"value\":";
  // json += String(angle);
  // json += "},";
  json += "\"uuid\":{\"value\":\"";
  json += id;
  json += "\"}},";
  dataCounter++;
}

void flushData() {
  Serial.println("trying post...");
  json.remove(json.length() - 1);
  json += "]}";
  // Serial.println(json);
  dataCounter = 0;

  WiFiClientSecure client;
  HTTPClient http;
  String URL = "https://sus.kintone.com/k/v1/records.json?app=2";
  int responseCode = 0;

  client.setInsecure();
  http.begin(client, URL);
  http.addHeader("X-Cybozu-API-Token", "OwnOyYnQp6uosz9qC0Sb88Rn4aZwpvSGtbm31RRc");
  http.addHeader("Content-type", "application/json");
  responseCode = http.POST(json);
  Serial.printf("http Response Code = %d \n", responseCode);
  // String payload = http.getString();
  // Serial.println(payload);
  client.stop();
  http.end();
}

void setID() {
  randomSeed(analogRead(0));
  id += String(random(999999));
  id += String(random(999999));
  Serial.println(id);
}


// function that executes whenever data is received from master
// this function is registered as an event, see setup()
void dataReceive(int num_bytes) {
  short distance = -100;
  while (0 < Wire.available())  // loop through all but the last
  {
    char a = Wire.read();
    char b = Wire.read();
    distance = (((short)a) << 8) | b;
  }

  Serial.print("D: ");
  Serial.print(distance);

  if (distance == -99) {
    setID();
    resetData();
  } else if (distance == -300)
    flushData();
  else if (dataCounter <= 99) {
    addData(distance);
  } else {
    addData(distance);
    flushData();
    resetData();
  }
}