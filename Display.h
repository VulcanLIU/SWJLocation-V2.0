/* 
* Display.h
*
* Created: 2018/8/20 1:57:09
* Author: Vulcan
*/


#ifndef __DISPLAY_H__
#define __DISPLAY_H__

#include "WString.h"

class Display
{
public:
	Display();
	void begin();
	void displayTime(long int);
	void displayStr(String str);
	void refresh(int L1_speed,int L2_speed,int R1_speed,int R2_speed,double pos_x,double pos_y,double pos_p,String state,double Yaw,double Pitch,double Row);
  void displayXYP(double,double,double);
protected:
private:
	const int time_x = 0;const int time_y = 0;
	//line 8
	//++++++++
	//++++++++
	//line10
	const int PWML1_x = 0;const int PWML1_y = 10; const int PWMR1_x = 64;const int PWMR1_y = 10;
	const int PWML2_x = 0;const int PWML2_y = 18; const int PWMR2_x = 64;const int PWMR2_y = 18;
	//line 26
	//++++++++
	//++++++++
	//line28
	const int X_encode_x = 0;const int X_encode_y = 28;const int Y_encode_x = 64;const int Y_encode_y = 28;
	const int P_encode_x = 0;const int P_encode_y = 36;
	//line 44
	//++++++++
	//++++++++
	//line 46
	const int X_real_x = 0;const int X_real_y = 46;const int Y_real_x = 64;const int Y_real_y = 46;
	const int P_real_x = 0;const int P_real_y = 54;
	//line 62
	//+++++++++
	//+++++++++
	//line 64
	const int Yaw_x = 0;const int Yaw_y = 46;const int Pitch_x = 64,Pitch_y = 46;
	const int Row_x = 0,Row_y = 54;
	
}; //Display
extern Display dp;

#endif //__DISPLAY_H__
