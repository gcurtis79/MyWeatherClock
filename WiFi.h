#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266mDNS.h>

ESP8266WiFiMulti wifiMulti;

IPAddress ip;

void wifi_init()
{ // Add another line for each WiFi network you might need
  wifiMulti.addAP("Pixel", "pr0sper0");
  wifiMulti.addAP("QC Co-Lab", "hackerspace");
  wifiMulti.addAP("HomeNet", "pito10digits");

  Serial.print("Connecting.");
  while (wifiMulti.run() != WL_CONNECTED)
  {
    delay(1000);
    Serial.print('.');
  }
  Serial.println('\n');
  Serial.print("Connected to:\t");
  Serial.println(WiFi.SSID());
  Serial.print("IP address:\t");
  Serial.println(WiFi.localIP());

  ip = WiFi.localIP();

  MDNS.begin(OTA_NAME);
}

void wifi_loop()
{
  // unused so far
}