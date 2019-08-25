#include <Arduino.h>
#line 1 "g:\\A-05-过去——I盘拓展\\B-毕业设计\\A-7-28 Version2-Stm32\\E-新程序资料\\SWJLocation-V2.0\\SWJLocation-V2.0.ino"
#line 1 "g:\\A-05-过去——I盘拓展\\B-毕业设计\\A-7-28 Version2-Stm32\\E-新程序资料\\SWJLocation-V2.0\\SWJLocation-V2.0.ino"
#include "ComwithGY25.h"
#include "Display.h"

//#define Serial1_DEBUG 1
//#define POS_DEBUG 1
//#define DATA_OUTPUT 1
#define DATA_OUTPUT_BYTES 1

double x = 0; //涓偣浣嶇疆提供给过过过
double y = 0;
double p = 0;

long int L_step = 0;
long int R_step = 0;

long int L_step_total = 0;
long int R_step_total = 0;

//鎺ョ嚎淇℃伅
static const int INT0A = PB0; //INT0
static const int INT0B = PB1;
static const int INT1A = PA6; //INT1
static const int INT1B = PA7;

//鐗╃悊淇℃伅
const double wheel_d = 38; //杞洿寰?38mm
const int x_line = 1000;
const int y_line = 1000;

//鐢ㄤ簬涓插彛杈撳嚭
double L = 0;
double R = 0;

double x2 = 0;
double y2 = 0;
int a = 0;

void blinkL();
void blinkR();

//void POS_begin();
//void POS_clear();
//void POS_refresh();

long int _millis = 0;

// The setup() function runs once each time the micro-controller starts
#line 48 "g:\\A-05-过去——I盘拓展\\B-毕业设计\\A-7-28 Version2-Stm32\\E-新程序资料\\SWJLocation-V2.0\\SWJLocation-V2.0.ino"
void setup();
#line 56 "g:\\A-05-过去——I盘拓展\\B-毕业设计\\A-7-28 Version2-Stm32\\E-新程序资料\\SWJLocation-V2.0\\SWJLocation-V2.0.ino"
void loop();
#line 150 "g:\\A-05-过去——I盘拓展\\B-毕业设计\\A-7-28 Version2-Stm32\\E-新程序资料\\SWJLocation-V2.0\\SWJLocation-V2.0.ino"
void POS_begin();
#line 162 "g:\\A-05-过去——I盘拓展\\B-毕业设计\\A-7-28 Version2-Stm32\\E-新程序资料\\SWJLocation-V2.0\\SWJLocation-V2.0.ino"
void POS_clear();
#line 172 "g:\\A-05-过去——I盘拓展\\B-毕业设计\\A-7-28 Version2-Stm32\\E-新程序资料\\SWJLocation-V2.0\\SWJLocation-V2.0.ino"
void POS_refresh();
#line 198 "g:\\A-05-过去——I盘拓展\\B-毕业设计\\A-7-28 Version2-Stm32\\E-新程序资料\\SWJLocation-V2.0\\SWJLocation-V2.0.ino"
void Serial1Event();
#line 48 "g:\\A-05-过去——I盘拓展\\B-毕业设计\\A-7-28 Version2-Stm32\\E-新程序资料\\SWJLocation-V2.0\\SWJLocation-V2.0.ino"
void setup()
{
  GY25.begin();
  dp.begin();
  POS_begin();
  Serial1.begin(115200);
}
// Add the main program code into the continuous loop() function
void loop()
{
  GY25.refresh();

  if (millis() - _millis >= 5)
  {
    POS_refresh();

    dp.displayXYP(x, y, p);

#ifdef DATA_OUTPUT
    Serial1.print("x:");
    Serial1.print(x);
    Serial1.print("y:");
    Serial1.print(y);
    Serial1.print("p:");
    Serial1.print(p);
#endif

#ifdef DATA_OUTPUT_BYTES
    int32_t x0 = x * 100;
    byte x1 = x0 & 0xff;
    byte x2 = (x0 >> 8) & 0xff;
    byte x3 = (x0 >> 16) & 0xff;
    byte x4 = (x0 >> 24) & 0xff;

    int32_t y0 = y * 100;
    byte y1 = y0 & 0xff;
    byte y2 = (y0 >> 8) & 0xff;
    byte y3 = (y0 >> 16) & 0xff;
    byte y4 = (y0 >> 24) & 0xff;

    int16_t p0 = p * 100;
    byte p1 = p0 & 0xff;
    byte p2 = (p0 >> 8) & 0xff;

    Serial1.write(0x55);
    Serial1.write(x1);
    Serial1.write(x2);
    Serial1.write(x3);
    Serial1.write(x4);
    Serial1.write(y1);
    Serial1.write(y2);
    Serial1.write(y3);
    Serial1.write(y4);
    Serial1.write(p1);
    Serial1.write(p2);
    Serial1.write(0xAA);
#endif

#ifdef Serial_DEBUG
    Serial1.print("L_step:");
    Serial1.print(L_step_total);
    Serial1.print("R_step:");
    Serial1.print(R_step_total);
#endif

    Serial1.println();

    _millis = millis();
  }
  Serial1Event();
}

void blinkL()
{
  int Lstate = digitalRead(INT0B);
  if (Lstate == HIGH)
  {
    L_step++;
    L_step_total++;
  }
  else
  {
    L_step--;
    L_step_total--;
  }
}

void blinkR()
{
  int Rstate = digitalRead(INT1B);
  if (Rstate == HIGH)
  {
    R_step++;
    R_step_total++;
  }
  else
  {
    R_step--;
    R_step_total--;
  }
}

void POS_begin()
{
  pinMode(INT0A, INPUT_PULLUP);
  pinMode(INT1A, INPUT);

  pinMode(INT0B, INPUT_PULLUP);
  pinMode(INT1B, INPUT);

  attachInterrupt(digitalPinToInterrupt(INT0A), blinkL, FALLING);
  attachInterrupt(digitalPinToInterrupt(INT1A), blinkR, FALLING);
}

void POS_clear()
{
  L_step = 0;
  R_step = 0;

  x = 0;
  y = 0;
  p = 0;
}

void POS_refresh()
{
  L = double(L_step) / x_line * PI * wheel_d;
  L_step = 0;                                 //琛岃蛋鐨勮窛绂? 鍗曚綅mm锛?
  R = double(R_step) / y_line * PI * wheel_d; //琛岃蛋鐨勮窛绂? 鍗曚綅mm锛?
  R_step = 0;
  p = double(GY25.YPR[0]) / 180.00 * PI;

  //鍒樺睍楣忕殑绠楁硶
  x2 -= (R)*cos(p - PI / 4) - (L)*sin(p - PI / 4);
  y2 += (L)*cos(p - PI / 4) + (R)*sin(p - PI / 4);

  x = x2;
  y = y2;
  p = p / PI * 180;

#ifdef POS_DEBUG
  Serial1.print("L_step_total:");
  Serial1.print(L_step_total);
  Serial1.print("R_step_total:");
  Serial1.print(R_step_total);

  Serial1.println();
#endif
}

void Serial1Event()
{
  if (Serial1.available() > 0)
  {
    String str = Serial1.readStringUntil('\n');
    str.toLowerCase();
    str = str.substring(0, str.length() - 1);
    Serial1.println(str);
    Serial1.println(str.length());

    if (str == "clear")
    {
      GY25.correctYaw();
      delay(3000);
      GY25.autoMode();
    }
    else
    {
      //Serial1.println("1");
    }
    if (str == "clearall")
    {
      GY25.correctYaw();
      delay(3000);
      GY25.autoMode();
      x2 = 0;
      y2 = 0;
    }
    else
    {
      //Serial1.println("2");
    }
  }
}

