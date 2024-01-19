#include <DHT.h>  // Including library for dht
 
#include <ESP8266WiFi.h>
 
String apiKey = "TMGSV7U5CQIK5BKU";     //  Enter your Write API key from ThingSpeak
 
//const char *ssid =  "DELAROSA";     // replace with your wifi ssid and wpa2 key
//const char *pass =  "$Dtd50djfA";
const char *ssid =  "willington";     // replace with your wifi ssid and wpa2 key
const char *pass =  "Prueba01";

const char* server = "api.thingspeak.com";
 
#define DHTPIN D2          //pin where the dht11 is connected
 
DHT dht(DHTPIN, DHT22);
 
WiFiClient client;

int sen_1 = D5;
int sen_2 = D6;
int sen_3 = D7;
int sen_4 = 9;
int sen_5 = 10;

int val_1,val_2, val_3, val_4, val_5 = 0;

int led_1 = D0;//default led nodemcu

void setup() 
{
  Serial.begin(115200);
  delay(10);
  dht.begin();

  Serial.println("Connecting to ");
  Serial.println(ssid);

  pinMode(sen_1,INPUT_PULLUP);
  pinMode(sen_2,INPUT_PULLUP);
  pinMode(sen_3,INPUT_PULLUP);
  pinMode(sen_4,INPUT_PULLUP);  
  pinMode(sen_5,INPUT_PULLUP);  
  pinMode(led_1,OUTPUT);

  WiFi.begin(ssid, pass);

  while (WiFi.status() != WL_CONNECTED) 
  {
        delay(500);
        Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");

}
 
void loop() 
{
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  val_1 = digitalRead(sen_1);
  val_2 = digitalRead(sen_2);
  val_3 = digitalRead(sen_3);
  val_4 = digitalRead(sen_4);
  val_5 = digitalRead(sen_5);
  delay(500);
  
  if (client.connect(server,80))   //   "184.106.153.149" or api.thingspeak.com
  {  
    String postStr = apiKey;
    postStr +="&field1=";
    postStr += String(t);
    postStr +="&field2=";
    postStr += String(h);
    postStr +="&field3=";
    postStr += String(val_1);
    postStr +="&field4=";
    postStr += String(val_2);
    postStr +="&field5=";
    postStr += String(val_3);
    postStr +="&field6=";
    postStr += String(val_4);
    postStr +="&field7=";
    postStr += String(val_5);
    postStr += "\r\n\r\n";

    client.print("POST /update HTTP/1.1\n");
    client.print("Host: api.thingspeak.com\n");
    client.print("Connection: close\n");
    client.print("X-THINGSPEAKAPIKEY: "+apiKey+"\n");
    client.print("Content-Type: application/x-www-form-urlencoded\n");
    client.print("Content-Length: ");
    client.print(postStr.length());
    client.print("\n\n");
    client.print(postStr);

    Serial.print("Temperatura: ");
    Serial.print(t);
    Serial.print(" Celcius, Humidad: ");
    Serial.print(h);
    Serial.print(" Nivel1: ");
    Serial.print(val_1);
    Serial.print(" Nivel2: ");
    Serial.print(val_2);
    Serial.print(" Nivel3: ");
    Serial.print(val_3);
    Serial.print(" Nivel4: ");
    Serial.print(val_4);
    Serial.print(" Nivel5: ");
    Serial.print(val_5);
    Serial.println("");
    Serial.println("%. Send to Thingspeak.");
  }
  client.stop();
  Serial.println("Waiting...");
  
  // thingspeak needs minimum 15 sec delay between updates
  delay(1000);
}
