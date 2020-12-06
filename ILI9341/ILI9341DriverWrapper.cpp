#include <ILI9341DriverWrapper.h>
#include <ILI9341Driver.h>
#include "spi.h"
#ifdef __cplusplus
extern "C"
{
#endif
	struct ILI9341DriverK
	{
		ili9341Driver LCDx;
	};
	struct ILI9341DriverK *NewLCDGet(void)
	{
		return new struct ILI9341DriverK;
	}
	void ILI9341SetColor(struct ILI9341DriverK *lcd, uint16_t colour)
	{
		lcd->LCDx.ILI9341_FillScreen(colour);
	}
	void ILI9341Init(struct ILI9341DriverK *lcd, SPI_HandleTypeDef *InSPI)
	{
		lcd->LCDx.ILI9341_init(InSPI);
	}
	void ILI9341_Set_Rotation(struct ILI9341DriverK *lcd, uint8_t Rotation)
	{
		lcd->LCDx.ILI9341_SetRotation(Rotation);
	}
	void ILI9341_ShowText(struct ILI9341DriverK *lcd, const char *Text, uint8_t X, uint8_t Y, uint16_t Colour, uint16_t Size, uint16_t Background_Colour)
	{
		lcd->LCDx.ILI9341_DrawText(Text, X, Y, Colour, Size, Background_Colour);
	}
	void ILI9341_DrawPoint(struct ILI9341DriverK *lcd, uint16_t X, uint16_t Y, uint16_t Colour)
	{
		lcd->LCDx.ILI9341_DrawPixel(X, Y, Colour);
	}
	
	void ILI9341_InitWave(struct ILI9341DriverK *lcd,uint16_t Max,uint16_t Min)
	{
		lcd->LCDx.ILI9341_InitDynamicGraph(Max, Min);
	}
	
	void ILI9341_UpdateWave(struct ILI9341DriverK *lcd)
	{
		lcd->LCDx.ILI9341_UpdateDynamicGraph();
	}
	
	void ILI9341_AddPointToWave(struct ILI9341DriverK *lcd,uint16_t Num)
	{
		lcd->LCDx.ILI9341_AddPointToDynamicGraph(Num);
	}
	void ILI9341_AppendList(struct ILI9341DriverK *lcd,uint8_t *List)
	{
		lcd->LCDx.ILI9341_AppendList(List);
	}
	
	void ILI9341_TEST(struct ILI9341DriverK *lcd)
	{
		lcd->LCDx.ILI9341_TEST();
		lcd->LCDx.ILI9341_UpdateDynamicGraph();
	}

#ifdef __cplusplus
}
#endif