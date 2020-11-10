#include <ILI9341DriverWrapper.h>
#include <ILI9341Driver.h>
#include "spi.h"
#ifdef __cplusplus
extern "C" {
#endif
struct ILI9341DriverK
{
	ili9341Driver LCDx;
};
struct ILI9341DriverK *NewLCDGet(void)
{
	return new struct ILI9341DriverK;
}
void 	ILI9341SetColor(struct ILI9341DriverK *lcd,uint16_t colour)
{
	lcd->LCDx.ILI9341_FillScreen(colour);
}
void ILI9341Init(struct ILI9341DriverK *lcd,SPI_HandleTypeDef *InSPI)
{
	lcd->LCDx.ILI9341_init(InSPI);
}
void ILI9341_Set_Rotation(struct ILI9341DriverK *lcd,uint8_t Rotation)
{
	lcd->LCDx.ILI9341_SetRotation(Rotation);
}
void ILI9341_ShowText
(struct ILI9341DriverK *lcd,const char* Text, uint8_t X, uint8_t Y, uint16_t Colour, uint16_t Size, uint16_t Background_Colour)
{
	lcd->LCDx.ILI9341_DrawText(Text,X,Y,Colour,Size,Background_Colour);
}
#ifdef __cplusplus
}
#endif