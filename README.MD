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
 注意该测试基于STM32H743开启Dcache之后，但是实际使用中并不会开启DCache(为了更加兼容没有Cache的MCU)。在开启DMA后，效率可以达到开启Dcache的85％，不建议同时开启DMA和DCache，具体原因请看[这里](http://www.pchmath.top:1234/index.php/2020/06/22/%e8%ae%b0%e5%bd%95%e4%b8%80%e6%ac%a1stm32h743%e4%b8%b2%e5%8f%a3%e4%b8%8d%e5%ae%9a%e9%95%bfdmacache%e5%90%88%e5%b9%b6%e5%ae%9e%e7%8e%b0%e8%bf%87%e7%a8%8b/)。
## *版本*
* 目前版本v1.0 
## *版本说明*
v0.1初始化工程，确定软件结构，提供几个基本的lcd操作接口  
v1.0提供波形绘制函数  
## *API使用说明*  
* API总览
> ```
> void ILI9341_init(SPI_HandleTypeDef *InSPI);
> //初始化屏幕
> void ILI9341_FillScreen(uint16_t Colour);
> //将整个屏幕填充为colour
> void ILI9341_SetRotation(uint8_t Rotation);
> //设置屏幕方向
>void ILI9341_DrawText(const char *Text, uint8_t X, uint8_t Y, uint16_t Colour, uint16_t Size, uint16_t Background_Colour);
> //绘制text文本，注意目前的字符库非常丑
>void ILI9341_DrawChar(char Character, uint8_t X, uint8_t Y, uint16_t Colour, uint16_t Size, uint16_t Background_Colour);
> //绘制单个字符
>void ILI9341_DrawRectangle(uint16_t X, uint16_t Y, uint16_t Width, uint16_t Height, uint16_t Colour);
> //绘制矩形
>void ILI9341_DrawPixel(uint16_t X, uint16_t Y, uint16_t Colour);
> //绘制颜色为Colour点
>void ILI9341_InitDynamicGraph(uint32_t Max, uint32_t Min);
> //初始化函数绘制窗口
>void ILI9341_UpdateDynamicGraph(void);
> //更新函数绘制窗口
>void ILI9341_AddPointToDynamicGraph(uint16_t Num);
> //添加一个点在波形窗口并与上一个点联想
>void ILI9341_TEST(void);
> //测试函数
>void ILI9341_AppendList(uint8_t * List);
> //添加一行字符，最终产生一种类似于shell的效果
> ```
* 特殊API说明  
  波形绘制功能展示  
> ```
> ILI9341_InitWave(LCD1,320,0); //在屏幕底部产生一个用于绘制的窗口
> for(int i=0;i<110;i++)
>{
>	ILI9341_AddPointToWave(LCD1,i); //加入点i，并连线
>	ILI9341_UpdateWave(LCD1); //更新屏幕
>}
> ```
 注意这里有几个点对于这个功能，首先ILI9341_AddPointToWave所加入的点必须在320和0之间，这个最大和最小值可以在ILI9341_InitWave(LCD1,MAX,MIN)中设置，其次，本函数每次更新屏幕耗时大约在30ms左右，也就是说屏幕帧率在30FPS左右，对于用户而言，如果加入点的时间小于了30ms，会被进行降采样操作，也就是说波形不会1：1的方式反应在屏幕上。