#include <ESP8266WiFi.h>
#include <ThingSpeak.h>
WiFiClient client;

String ssid[] = {"Bhatt", "Ashok", "Abhinav", "Rajesh", "itsharsh", "o2iabhinav"};
String password[] = {"password", "password", "password", "password", "password", "password"};
#define API "U8WLF7Z8OF84EFBN"
long channelID = 864933;
byte pin = 5;

void setup()
{
  Serial.begin(9600);
  ThingSpeak.begin(client);
  pinMode(pin, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);
  int i = 0;
  while (1)
  {
    Serial.print("Connecting to ");
    Serial.print(ssid[i]);
    WiFi.begin(ssid[i], password[i]);
    byte count = 0;
    while (WiFi.waitForConnectResult() != WL_CONNECTED)
    {
      Serial.print(".");
      delay(100);
      count++;
      if (count > 30)
      {
        Serial.println("Failed");
        i++;
        break;
      }
    }
    if (i >= sizeof(ssid) / sizeof(ssid[i]))
    {
      ESP.restart();
    }
    else if (WiFi.waitForConnectResult() == WL_CONNECTED)
      break;
  }
  digitalWrite(LED_BUILTIN, LOW);
  Serial.print("\nConnected to ");
  Serial.print(ssid[i]);
}
void loop()
{
  if (client.connect("api.thingspeak.com", 80))
  {
    if ((ThingSpeak.readIntField(channelID, 1, API)) == 1)
    {
      digitalWrite(pin, HIGH);
      Serial.println(ThingSpeak.readIntField(channelID, 1, API));
    }
    else if ((ThingSpeak.readIntField(channelID, 1, API)) == 0)
    {
      digitalWrite(pin, LOW);
      Serial.println(ThingSpeak.readIntField(channelID, 1, API));
    }
  }
}
