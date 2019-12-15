#include "Config.h"
#include "WiFi.h"
//#include "NTP.h"
#include "ezNTP.h"
#include "Matrix.h"
#include "Weather.h"
#include "OTA.h"
#include "Plasma.h"
#include "button.h"

void setup()
{
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

void loop()
{
  wifi_loop();
  ezNTP_loop();
  ota_loop();
  button_loop();

  switch (display_mode)
  {
  case 0:
    matrix_loop();
    weather_loop();
    break;
  case 1:
    display_IP();
    delay(100);
    break;
  case 2:
    plasma_loop();
    break;
  default:
    display_mode = 0;
    break;
  }
}
