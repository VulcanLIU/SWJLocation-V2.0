# SWJLocation-V2.0
平面定位系统Version1-Stm32duino版
========
一.介绍
--------
      这是一种基于航位推算原理设计的平面定位装置，属于相对定位方式，存在积分误差且误差随时间增大。前一版本使用Arduino nano写，这一版本使用Stm32duino（F103c8t6）。  
      
 二.使用准备
 --------
   ### 1.安装Arduino core support for STM32 based boards  
      详见https://github.com/stm32duino/Arduino_Core_STM32  

   ### 2.安装Adafruit_SSD1306
      * 详见https://github.com/adafruit/Adafruit_SSD1306
      * 按照Adafruit官方说明，还需要安装Adafruit GFX library，详见https://github.com/adafruit/Adafruit-GFX-Library  

   ### 3.修改stm32duino的variant.h文件以开启相应外设
      我电脑中该文件的路径在C:\Users\Vulcan\AppData\Local\Arduino15\packages\STM32\hardware\stm32\1.5.0\variants\BLUEPILL_F103XX\variant.h 以供参考，appdata文件夹为隐藏文件夹注意寻找方法。
-----
#### 修改方法
1.将
``` c++ 
// UART Definitions
#define SERIAL_UART_INSTANCE    1
// Default pin used for 'Serial' instance
// Mandatory for Firmata
#define PIN_SERIAL_RX           PA10
#define PIN_SERIAL_TX           PA9
```
改为
``` c++ 
// UART Definitions
#define SERIAL_UART_INSTANCE    1
// Default pin used for 'Serial' instance
// Mandatory for Firmata
#define PIN_SERIAL_RX           PB7
#define PIN_SERIAL_TX           PB6

#define ENABLE_HWSERIAL2
#define PIN_SERIAL2_RX           PA3
#define PIN_SERIAL2_TX           PA2
```
+ 使用 Serial 的 PB6作为TX引脚 PB7作为RX引脚
+ 打开 Serial2 RX--PA3 TX--PA2  

2.将
```c++
// I2C Definitions
#define PIN_WIRE_SDA            PB7
#define PIN_WIRE_SCL            PB6
```
改为
```c++
// I2C Definitions
#define PIN_WIRE_SDA            PB11
#define PIN_WIRE_SCL            PB10
```
+ 更改SDA1使用的引脚
-------------
三.编译下载
------
  1.板子选择  
  
  2.开始烧录


