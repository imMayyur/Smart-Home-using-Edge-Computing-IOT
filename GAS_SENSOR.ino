#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

WiFiClient client;

String thingSpeakAddress = "http://api.thingspeak.com/update?";
String writeAPIKey;
String tsfield1Name;
String request_string;

HTTPClient http;

int redLed = D4;
int greenLed = D6;
int buzzer = D7;
int smokeA0 = A0;
// Your threshold value
int sensorThres = 660;

void setup() {
  pinMode(redLed, OUTPUT);
  pinMode(greenLed, OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(smokeA0, INPUT);
  Serial.begin(115200);
  WiFi.disconnect();
  WiFi.begin("Mayur", "mayurpatel123");
  while ((!(WiFi.status() == WL_CONNECTED)))
  {
    Serial.print("Not Connect");
    delay(300);
  }
  Serial.print("Connect");
}

void loop() {
  int analogSensor = analogRead(smokeA0);

if (client.connect("api.thingspeak.com",80)) {
      request_string = thingSpeakAddress;
      request_string += "key=";
      request_string += "RBBRH2J0MWV08FNG";
      request_string += "&";
      request_string += "field1";
      request_string += "=";
      request_string += analogSensor;
      http.begin(request_string);
      http.GET();
      http.end();

    }  
     
  Serial.print("-Pin A0: ");
  Serial.println(analogSensor);
  // Checks if it has reached the threshold value
  if (analogSensor > sensorThres)
  {
    digitalWrite(redLed, HIGH);
    digitalWrite(greenLed, LOW);
    tone(buzzer, 1000, 200);
    delay(100);
  }
  else
  {
    digitalWrite(redLed, LOW);
    digitalWrite(greenLed, HIGH);
    noTone(buzzer);
  }
  delay(100);
}
