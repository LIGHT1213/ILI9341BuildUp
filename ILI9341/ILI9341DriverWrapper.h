#ifndef _ILI9341_WRAPPER
#define _ILI9341_WRAPPER
//#include <ILI9341Driver.hpp>
#include "main.h"
#ifdef __cplusplus
extern "C" {
#endif
struct ILI9341DriverK;
struct ILI9341DriverK *NewLCDGet(void);
void ILI9341Init(struct ILI9341DriverK *lcd,SPI_HandleTypeDef *InSPI);
void ILI9341SetColor(struct ILI9341DriverK *lcd,uint16_t colour);
void ILI9341_Set_Rotation(struct ILI9341DriverK *lcd,uint8_t Rotation);

void ILI9341_ShowText
(struct ILI9341DriverK *lcd,const char* Text, uint8_t X, uint8_t Y, uint16_t Colour, uint16_t Size, uint16_t Background_Colour);


#ifdef __cplusplus
}
#endif
#endif