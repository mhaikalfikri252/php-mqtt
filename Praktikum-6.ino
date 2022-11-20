#include <EEPROM.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <Wire.h>
// #include <Adafruit_INA219.h>
#include <stdlib.h>
// Connect to the WiFi
const char* ssid = "TP-Link_60DA";
const char* password = "h1ced3948b5";
const char* mqtt_server = "riset.revolusi-it.com";

const char* topik = "iot/kendali";
WiFiClient espClient;
PubSubClient client(espClient);
String messages, messages2;

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
  Serial.print("Menghubungkan diri ke MQTT Server : "+(String)mqtt_server);
  // Attempt to connect
  if (client.connect("G.241.21.0007")) {
    Serial.println("connected");
    // ... and subscribe to topic
    client.subscribe(topik);
  } else {
    Serial.print("failed, rc=");
    Serial.print(client.state());
    Serial.println(" coba lagi dalam 5 detik...");
    // Wait 5 seconds before retrying
    delay(5000);
  }
  }
}


void konek_wifi()
{
WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  } 
  Serial.println("");
  Serial.println("WiFi connected");
}

// ------------------------------- begin --------------------------------------- //
void setup()
{
  Serial.begin(9600);
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);

  pinMode(D1, OUTPUT);
  pinMode(D2, OUTPUT);
  pinMode(D3, OUTPUT);
}

void loop()
{
  if(WiFi.status() != WL_CONNECTED) { konek_wifi(); } // jika tidak konek wifi maka di reconnect
  if (!client.connected()) { reconnect(); } // reconnect apabila belum konek

  client.loop();
}

void callback(char* topic, byte* payload, unsigned int length) {
Serial.print("Pesan dari MQTT [");
Serial.print(topic);
Serial.print("] ");
messages="";
for (int i=0;i<length;i++) { // susun jadi string saja...
  char receivedChar = (char)payload[i];
  messages=messages+(char)payload[i]; // ambil pesannya masukkan dalam string
  }
  Serial.println(messages);

  if(messages=="D1=1"){ digitalWrite(D1, 1);}
  if(messages=="D2=1"){ digitalWrite(D2, 1);}
  if(messages=="D3=1"){ digitalWrite(D3, 1);}

  if(messages=="D1=0"){ digitalWrite(D1, 0);}
  if(messages=="D2=0"){ digitalWrite(D2, 0);}
  if(messages=="D3=0"){ digitalWrite(D3, 0);}

// kirim pesan ke mqtt server
// messages2="Pesan dari Client";
// Serial.println(messages2);
// perhatikan cara ngirim variabel string lewat client.publish ini gak bisa langsung...
char attributes[100];
// messages2.toCharArray(attributes, 100);
// client.publish(topik,attributes,true);
// Serial.println("messages : "+messages2+" terkirim...");
// delay(3000);
}