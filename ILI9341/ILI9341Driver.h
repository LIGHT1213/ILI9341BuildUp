#ifndef ILI9341_DRIVER
#define ILI9341_DRIVER
#define SCREEN_VERTICAL_1 0
#define SCREEN_HORIZONTAL_1 1
#define SCREEN_VERTICAL_2 2
#define SCREEN_HORIZONTAL_2 3

#define BURST_MAX_SIZE 1000

#define BLACK 0x0000
#define NAVY 0x000F
#define DARKGREEN 0x03E0
#define DARKCYAN 0x03EF
#define MAROON 0x7800
#define PURPLE 0x780F
#define OLIVE 0x7BE0
#define LIGHTGREY 0xC618
#define DARKGREY 0x7BEF
#define BLUE 0x001F
#define GREEN 0x07E0
#define CYAN 0x07FF
#define RED 0xF800
#define MAGENTA 0xF81F
#define YELLOW 0xFFE0
#define WHITE 0xFFFF
#define ORANGE 0xFD20
#define GREENYELLOW 0xAFE5
#define PINK 0xF81F
#ifdef __cplusplus
extern "C"
{

#include "main.h"

	class ili9341Driver
	{
	public:
		void ILI9341_init(SPI_HandleTypeDef *InSPI);
		void ILI9341_FillScreen(uint16_t Colour);
		void ILI9341_SetRotation(uint8_t Rotation);
		void ILI9341_DrawText(const char *Text, uint8_t X, uint8_t Y, uint16_t Colour, uint16_t Size, uint16_t Background_Colour);
		void ILI9341_DrawChar(char Character, uint8_t X, uint8_t Y, uint16_t Colour, uint16_t Size, uint16_t Background_Colour);
		void ILI9341_DrawRectangle(uint16_t X, uint16_t Y, uint16_t Width, uint16_t Height, uint16_t Colour);
		void ILI9341_DrawPixel(uint16_t X, uint16_t Y, uint16_t Colour);
		void ILI9341_InitDynamicGraph(uint32_t Max, uint32_t Min);
		void ILI9341_UpdateDynamicGraph(void);
		void ILI9341_AddPointToDynamicGraph(uint16_t Num);
		void ILI9341_TEST(void);
		void ILI9341_AppendList(uint8_t * List);
		int LCD_HEIGHT;
		int LCD_WIDTH;

	private:
		void ILI9341_AddLineToDynamicGraph(void);
		void ILI9341_DrawPointToMEM(uint16_t x, uint16_t y);
		void ILI9341_DrawLineToMEM(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1);
		void inline ILI9341_Write16BitData(uint16_t Data);
		void inline ILI9341_SetXY(uint16_t Xpos, uint16_t Ypos);
		void inline ILI9341_WriteData(uint8_t Data);
		void inline ILI9341_WriteCmd(uint8_t CMD);
		void inline ILI9341_SPI_Send(uint8_t SPI_Data);
		void ILI9341_SetAddress(uint16_t X1, uint16_t Y1, uint16_t X2, uint16_t Y2);
		void ILI9341_DrawColourBurst(uint16_t Colour, uint32_t Size);
		void inline ILI9341Enable(void);
		void inline ILI9341Reset(void);
		void inline LCDdelay(void);
		void ILI9341_ClearReaginSet(int Bx,int By,int Ex,int Ey);

		SPI_HandleTypeDef *UsedSPI;
		uint32_t DynamicGraphMax, DynamicGraphMin;
		uint16_t DynamicGraphRAM[100][320];
		uint16_t DynamicLine[320];
	};
};
#endif

#endif