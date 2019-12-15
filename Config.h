/*
 *  This file contains settings that may need changed and global prototypes
 */

/************************
      Device Settings
************************/
#define BUTTON D6     // Button wired to this pin and GND (internal pullup)
#define BRIGHT 255    // Highest brightness level
#define DIM 24        // Lowest brightness level

/************************
      OTA Settings
************************/
#define OTA_NAME "MyWeatherClock"   // Device name for OTA and mDNS
// OTA Password - Use https://www.md5hashgenerator.com/ to create a password
// This is used to flash the clock over wifi
// VSCode seems to not support this feature yet, or I just can't find it
//#define OTA_PASSWORD "af5e3c5c0bdbeb1e7c18ad074849bc06"

/************************
      NTP Settings
************************/
#define NTP_SERVER "ntp.ubuntu.com"  // NTP Server
uint8_t ntp_delay = (15, 43200);     // Update NTP every 12 hours
#define TIMEZONE "America/Chicago"   // Timezone http://bit.ly/timeZone

/************************
    Weather Settings
************************/
#define UNITS "imperial"                          // "imerial" or "metric"
#define CITY "Davenport,us"                       // City,country
#define APPID "1613c765d035e2fd68ae398295102e5e"  // Your API Key
#define HOST "api.openweathermap.org"             // This shouldn't change
#define HTTPPORT 80
#define URL "/data/2.5/weather?q=" + CITY + "&units=" + UNITS + "&appid=" + APPID
void drawWeather();
