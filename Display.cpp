/*
  Display.cpp

  Created: 2018/8/20 1:57:09
  Author: Vulcan
*/


#include "Display.h"
#include <Wire.h>
#include "Adafruit_SSD1306.h"
#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);
// default constructor
Display::Display()
{

}

void Display::begin()
{
  display.begin(SSD1306_SWITCHCAPVCC, 0x3c);
  display.display();
  delay(1000);

  display.clearDisplay();
}

void Display::displayTime(long int _time)
{
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 5);
  display.clearDisplay();
  display.print("Time:");
  display.println(_time);
  display.display();
}

void Display::displayStr(String str)
{
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 5);
  display.clearDisplay();
  display.print("Time:");
  display.println(str);
  display.display();
}

void Display::refresh(int L1_speed, int L2_speed, int R1_speed, int R2_speed, double pos_x, double pos_y, double pos_p, String state, double Yaw, double Pitch, double Row)
{
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.clearDisplay();
  //闂佽法鍠愰弸濠氬箯妞嬪簺浠涚紒顖濆吹缁椽鏌ㄩ悢鍛婄伄闁归鍏橀弫鎾诲棘閵堝棗顏堕柡鍐ㄧ埣閺佹捇寮妶鍡楊伓
  display.print("Time:");
  display.print(millis());

  //闂佽法鍠愰弸濠氬箯妞嬪簺浠涢梺璺ㄥ枑閺嬪骞忛悜鑺ユ櫢闁哄倶鍊栫€氱瓎WM
  display.setCursor(PWML1_x, PWML1_y);
  display.print("L1:");
  display.print(L1_speed);
  display.setCursor(PWMR1_x, PWMR1_y);
  display.print("R1:");
  display.print(R1_speed);

  display.setCursor(PWML2_x, PWML2_y);
  display.print("L2:");
  display.print(L2_speed);
  display.setCursor(PWMR2_x, PWMR2_y);
  display.print("R2:");
  display.print(R2_speed);

  //闂佽法鍠愰弸濠氬箯妞嬪簺浠涢梺璺ㄥ枑閺嬪骞忛悜鑺ユ櫢闁哄倶鍊栫€氬綊鏌ㄩ悢鍛婄伄闁归鍏橀弫鎾诲棘閵堝棗顏堕梺璺ㄥ櫐閹凤拷
  display.setCursor(X_encode_x, X_encode_y);
  display.print("X_mm:");
  display.print(pos_x);
  display.setCursor(Y_encode_x, Y_encode_y);
  display.print("Y_mm:");
  display.print(pos_y);
  display.setCursor(P_encode_x, P_encode_y);
  display.print("P_mm:");
  display.print(pos_p);

  // 	//闂佽法鍠愰弸濠氬箯妞嬪簺浠涢梺顑惧劦閺佹捇寮妶鍡楊伓闂佽法鍠愰弸濠氬箯妞嬪骸笑闁诡剨鎷�
  // 	display.setCursor(X_real_x,X_encode_y);
  // 	display.print("PS2:");
  // 	display.print(state);
  //闂佽法鍠愰弸濠氬箯妞嬪簺浠涢梺璺ㄥ枑閺嬪骞忛悜鑺ユ櫢闁哄倶鍊栫€氬綊鏌ㄩ悢娲绘健閻犱浇顫夌€氾拷
  display.setCursor(Yaw_x, Yaw_y);
  display.print("Yaw:");
  display.print(Yaw);

  display.setCursor(Pitch_x, Pitch_y);
  display.print("Pitch:");
  display.print(Pitch);

  display.setCursor(Row_x, Row_y);
  display.print("Row:");
  display.print(Row);

  display.display();
}
void Display::displayXYP(double X, double Y, double P)
{
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.clearDisplay();
  
  display.setCursor(PWML1_x, PWML1_y+5);
  display.print("X:");
  display.print(X);

  display.setCursor(PWMR1_x, PWMR1_y+5);
  display.print("Y:");
  display.print(Y);

  display.setCursor(PWML2_x, PWML2_y+5);
  display.print("P:");
  display.print(P);

  display.display();
}
Display dp = Display();
