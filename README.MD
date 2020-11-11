# <font face="微软雅黑">ILI9341驱动 STM32HAL 库版本
* 驱动说明  
由于之前使用的驱动文件刷新屏幕过慢，所以根据ILI9341手册重新调整了相关的数据的传输方式。
* 使用方式  
 此驱动基于c++编写，在使用时将此工程中的ILI9341Driver.cpp，ILI9341Driver.hpp,ILI9341DriverWrapper.cpp,ILI9341DriverWrapper.h总计4个文件加入到工程中，在代码中加入代码后便可通过才做ILI9341DriverWrapper文件中的相关接口函数操作lcd。 
> ```
> //这是一个把lcd初始化并且刷红的实例
> struct ILI9341DriverK *LCD1;//申请一个lcd操作strcut  
> LCD1=NewLCDGet();//通过c++函数new一个class类  
> ILI9341Init(LCD1,&hspi2); //选择spi2连接lcd屏幕
> ILI9341SetColor(LCD1,RED); //将lcd刷红
> ```
* STM32CubeMX初始化说明  
 在STM32CubeMx中的设置有以下几点需要注意，首先spi速率不得超过60M，data size 8bit，cpol LOW,CPHA 1edge  
 同时应当注意mosi，miso，sck三个io的speed应当设置为最高速率（<font color=#DC143C size=3 face="黑体">这点在使用STM32H7时必须注意</font>，cubemx在初始化H7的SPI相关时会变成LOW）,NSS信号应当开启硬件控制,其次在<font color=#DC143C size=3 face="黑体">RST,DC应当命名为LCD_RST和LCD_DC </font>。
 * 性能测试  
 通过初始化TIM1来计时，计算FPS
 ![FPS测试](https://raw.githubusercontent.com/LIGHT1213/picture/master/FPS.gif)
##  版本
* 目前版本v0.1 
### 版本说明
初始化工程，确定软件结构，提供几个基本的lcd操作接口  
2020年11月11日开始命运2第四年首周开荒＋原神1.1剧情首通，停更几天  
咕咕咕
 