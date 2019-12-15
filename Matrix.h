#include <Ticker.h>
#include <PxMatrix.h>
#include <Fonts/Picopixel.h>
#include <Fonts/Tiny3x3a2pt7b.h>

Ticker display_ticker;
Ticker display_seconds;

int prevDisplay = 0; // when the digital clock was displayed

// Pins for LED MATRIX
#define P_LAT 16
#define P_A 5
#define P_B 4
#define P_C 15
#define P_OE 2
PxMATRIX display(32, 16, P_LAT, P_OE, P_A, P_B, P_C);

class myCOLOR
{
public:
  uint16_t red(int r_level = 255)
  {
    constrain(r_level, 0, 255);
    return display.color565(r_level, 0, 0);
  }
  uint16_t green(int g_level = 255)
  {
    constrain(g_level, 0, 255);
    return display.color565(0, g_level, 0);
  }
  uint16_t blue(int b_level = 255)
  {
    constrain(b_level, 0, 255);
    return display.color565(0, 0, b_level);
  }
  uint16_t white(int w_level = 255)
  {
    constrain(w_level, 0, 255);
    return display.color565(w_level, w_level, w_level);
  }
  uint16_t rgb(int r_level = 255, int g_level = 255, int b_level = 255)
  {
    constrain(r_level, 0, 255);
    constrain(g_level, 0, 255);
    constrain(b_level, 0, 255);
    return display.color565(r_level, g_level, b_level);
  }

private:
};
myCOLOR myCOLOR;

// Some standard colors
uint16_t myRED = display.color565(255, 0, 0);
uint16_t myGREEN = display.color565(0, 255, 0);
uint16_t myBLUE = display.color565(0, 0, 255);
uint16_t myWHITE = display.color565(255, 255, 255);
uint16_t myYELLOW = display.color565(255, 255, 0);
uint16_t myCYAN = display.color565(0, 255, 255);
uint16_t myMAGENTA = display.color565(255, 0, 255);
uint16_t myBLACK = display.color565(0, 0, 0);

uint16_t myCOLORS[8] = {myRED, myGREEN, myBLUE, myWHITE, myYELLOW, myCYAN, myMAGENTA, myBLACK};

// ISR for display refresh
int brightness = 2500;
int dimm = 0;

int countOnes(int num)
{
  int count = 0;
  while (num)
  {
    if (((num / 1U) % 10) == 1)
      count++;
    num = num / 10;
  }
  return count;
}

int intLength(int number)
{
  int ones = countOnes(number);
  int len = 0;
  while (number)
  {
    number = number / 10;
    len++;
  }
  len = ((len * 4) - ones);
  return len;
}

void display_updater()
{
  display.display(40);
}

int do_num(int num)
{
}

void drawDate()
{
  int ezMonth = month();
  int ezDay = day();
  int offset = (((ezMonth < 10) ? (4) : (8)) - countOnes(ezMonth));
  display.drawPixel(offset, 13, myWHITE);
  display.setCursor(1, 15);
  display.setTextColor(myCYAN);
  display.printf("%d", ezMonth);
  display.setTextColor(myMAGENTA);
  display.printf("%02d", ezDay);
}

void drawTime()
{
  int ezHour = (hour() > 12) ? (hour() - 12) : ((hour() == 0) ? 12 : hour());
  int ezMin = minute();
  int hOffset = (((ezHour < 10) ? 20 : 16) + countOnes(ezHour) + countOnes(ezMin));
  int mOffset = (23 + countOnes(ezMin));
  if ((second() % 2) == 0)
  {
    display.drawPixel(mOffset, 12, myCOLOR.white(BRIGHT));
    display.drawPixel(mOffset, 14, myCOLOR.white(BRIGHT));
  }
  else
  {
    display.drawPixel(mOffset, 12, myCOLOR.white(DIM));
    display.drawPixel(mOffset, 14, myCOLOR.white(DIM));
  }
  display.setTextColor(myRED);
  display.setCursor(hOffset, 15);
  display.printf("%d%02d", ezHour, ezMin);
  //Serial.printf("Counted %d ones. hOffset = %d\n", countOnes(ezHour), hOffset);
}

void display_time()
{
  if (timeStatus() > 0)
  {
    if (second() != prevDisplay)
    { //update the display only if time has changed
      display.clearDisplay();
      display.setTextWrap(false);
      prevDisplay = second();
      drawWeather();
      drawDate();
      drawTime();
    }
  }
}

void display_IP()
{
  display.clearDisplay();
  display.setFont(&Picopixel);
  display.setCursor(0, 4);
  display.setTextColor(myCOLOR.red(BRIGHT));
  display.print("IP Address");
  display.setTextColor(myCOLOR.blue(BRIGHT));
  display.setCursor(0, 9);
  display.print(ip[0]);
  display.setTextColor(myCOLOR.white(BRIGHT));
  display.print(".");
  display.setTextColor(myCOLOR.blue(BRIGHT));
  display.print(ip[1]);
  display.setCursor((31 - (intLength(ip[2]) + intLength(ip[3]))), 14);
  display.print(ip[2]);
  display.setTextColor(myCOLOR.white(BRIGHT));
  display.print(".");
  display.setTextColor(myCOLOR.blue(BRIGHT));
  display.print(ip[3]);
  display.display(40);
}

void matrix_init()
{
  display.begin();
  display_IP();
  display_ticker.attach(0.002, display_updater);
  display_seconds.attach(1, display_time);
  display.setFont(&Picopixel);
  yield();
  delay(1000);
}

void matrix_loop()
{
  //display_updater();
}
