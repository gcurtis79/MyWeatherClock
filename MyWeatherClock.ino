#include "Config.h"
#include "WiFi.h"
//#include "NTP.h"
#include "ezNTP.h"
#include "Matrix.h"
#include "Weather.h"
#include "OTA.h"
#include "button.h"

void setup() {
  Serial.begin(115200);
  delay(100);
  Serial.println("");
  wifi_init();
  ezNTP_init();
  matrix_init();
  weather_init();
  ota_init();
  button_init();
}

void loop() {
  wifi_loop();
  ezNTP_loop();
  matrix_loop();
  weather_loop();
  ota_loop();
  button_loop();
}
