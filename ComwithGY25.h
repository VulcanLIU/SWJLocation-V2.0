/* 
* ComwithGY25.h
*
* Created: 2018/10/8 19:30:32
* Author: Vulcan
*/


#ifndef __COMWITHGY25_H__
#define __COMWITHGY25_H__

#include "Arduino.h"

class ComwithGY25
{
public:
	float YPR[3];
	unsigned char Re_buf[8],counter=0;
	unsigned char sign=0;
	
	ComwithGY25();
	void begin();
	void autoMode();
	void autoModeASCII();
	void singleMode();
	void correctPitchRow();
	void correctYaw();
	void refresh();
}; //ComwithGY25
extern ComwithGY25 GY25;
#endif //__COMWITHGY25_H__
