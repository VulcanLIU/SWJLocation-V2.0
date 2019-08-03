/* 
* ComwithGY25.cpp
*
* Created: 2018/10/8 19:30:32
* Author: Vulcan
*/

#include "ComwithGY25.h"
//#include "HardwareSerial.h"

// default constructor
ComwithGY25::ComwithGY25()
{
} //ComwithGY25

void ComwithGY25::begin()
{
	Serial2.begin(115200);
	correctYaw();
	delay(3000);
	autoMode();
}

void ComwithGY25::autoMode()
{
	Serial2.write(0XA5);
	Serial2.write(0X52); //鍒濆鍖朑Y25,杩炵画杈撳嚭妯″紡
}

void ComwithGY25::autoModeASCII()
{
	Serial2.write(0XA5);
	Serial2.write(0X53); //鍒濆鍖朑Y25,杩炵画杈撳嚭妯″紡
}

void ComwithGY25::singleMode()
{
	Serial2.write(0XA5);
	Serial2.write(0X51); //鏍℃妯″紡锛屾牎姝ｄ刊浠版í婊氳 0 搴︼紝闇€瑕佷繚鎸佹按骞虫椂鍊欏彂閫?
}

void ComwithGY25::correctPitchRow()
{
	Serial2.write(0XA5);
	Serial2.write(0X54); //鏍℃妯″紡锛屾牎姝ｄ刊浠版í婊氳 0 搴︼紝闇€瑕佷繚鎸佹按骞虫椂鍊欏彂閫?
}

void ComwithGY25::correctYaw()
{
	Serial2.write(0XA5);
	Serial2.write(0X55); //鏍℃妯″紡锛屾牎姝ｈ埅鍚? 0 搴︼紝鑸悜浠绘剰瑙掑害娓呴浂
}

void ComwithGY25::refresh()
{
	while (Serial2.available())
	{
		Re_buf[counter] = (unsigned char)Serial2.read();
		if (counter == 0 && Re_buf[0] != 0xAA)
			return; // 妫€鏌ュ抚澶?
		counter++;
		if (counter == 8) //鎺ユ敹鍒版暟鎹?
		{
			counter = 0; //閲嶆柊璧嬪€硷紝鍑嗗涓嬩竴甯ф暟鎹殑鎺ユ敹
			sign = 1;
		}
	}
	if (sign == 1)
	{
		if (Re_buf[0] == 0xAA && Re_buf[7] == 0x55) //妫€鏌ュ抚澶达紝甯у熬
		{
			YPR[0] = int16_t(Re_buf[1] << 8 | Re_buf[2]) / -100.00; //鍚堟垚鏁版嵁锛屽幓鎺夊皬鏁扮偣鍚?2浣?
			YPR[1] = int16_t(Re_buf[3] << 8 | Re_buf[4]) / 100.00;
			YPR[2] = int16_t(Re_buf[5] << 8 | Re_buf[6]) / 100.00;
			Serial1.print("YPR[0]:");
			Serial1.println(YPR[0]);
		}
		sign = 0;
	}
}
ComwithGY25 GY25 = ComwithGY25();
