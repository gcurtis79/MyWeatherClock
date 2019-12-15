#include <ezTime.h>

Timezone myTZ;

const char * ntp_server = NTP_SERVER; // NTP Server

void ezNTP_init() {
  //setDebug(INFO);
  waitForSync();
  myTZ.setLocation(TIMEZONE);
  myTZ.setDefault();
}

void ezNTP_loop() {
  events();
}
