#include <ILI9341Driver.h>
#include "5x5_font.h"
#include <cstring>
uint16_t temp1,temp2;
void ili9341Driver::ILI9341_init(SPI_HandleTypeDef *InSPI)
{
	this->UsedSPI = InSPI;
	this->ILI9341Enable();
	//ILI9341_SPI_Init();
	this->ILI9341Reset();

	//SOFTWARE RESET
	this->ILI9341_WriteCmd(0x01);
	HAL_Delay(1000);

	//POWER CONTROL A
	this->ILI9341_WriteCmd(0xCB);
	this->ILI9341_WriteData(0x39);
	this->ILI9341_WriteData(0x2C);
	this->ILI9341_WriteData(0x00);
	this->ILI9341_WriteData(0x34);
	this->ILI9341_WriteData(0x02);

	//POWER CONTROL B
	this->ILI9341_WriteCmd(0xCF);
	this->ILI9341_WriteData(0x00);
	this->ILI9341_WriteData(0xC1);
	this->ILI9341_WriteData(0x30);

	//DRIVER TIMING CONTROL A
	this->ILI9341_WriteCmd(0xE8);
	this->ILI9341_WriteData(0x85);
	this->ILI9341_WriteData(0x00);
	this->ILI9341_WriteData(0x78);

	//DRIVER TIMING CONTROL B
	this->ILI9341_WriteCmd(0xEA);
	this->ILI9341_WriteData(0x00);
	this->ILI9341_WriteData(0x00);

	//POWER ON SEQUENCE CONTROL
	this->ILI9341_WriteCmd(0xED);
	this->ILI9341_WriteData(0x64);
	this->ILI9341_WriteData(0x03);
	this->ILI9341_WriteData(0x12);
	this->ILI9341_WriteData(0x81);

	//PUMP RATIO CONTROL
	this->ILI9341_WriteCmd(0xF7);
	this->ILI9341_WriteData(0x20);

	//POWER CONTROL,VRH[5:0]
	this->ILI9341_WriteCmd(0xC0);
	this->ILI9341_WriteData(0x23);

	//POWER CONTROL,SAP[2:0];BT[3:0]
	this->ILI9341_WriteCmd(0xC1);
	this->ILI9341_WriteData(0x10);

	//VCM CONTROL
	this->ILI9341_WriteCmd(0xC5);
	this->ILI9341_WriteData(0x3E);
	this->ILI9341_WriteData(0x28);

	//VCM CONTROL 2
	this->ILI9341_WriteCmd(0xC7);
	this->ILI9341_WriteData(0x86);

	//MEMORY ACCESS CONTROL
	this->ILI9341_WriteCmd(0x36);
	this->ILI9341_WriteData(0x48);

	//PIXEL FORMAT
	this->ILI9341_WriteCmd(0x3A);
	this->ILI9341_WriteData(0x55);

	//FRAME RATIO CONTROL, STANDARD RGB COLOR
	this->ILI9341_WriteCmd(0xB1);
	this->ILI9341_WriteData(0x00);
	this->ILI9341_WriteData(0x18);

	//DISPLAY FUNCTION CONTROL
	this->ILI9341_WriteCmd(0xB6);
	this->ILI9341_WriteData(0x08);
	this->ILI9341_WriteData(0x82);
	this->ILI9341_WriteData(0x27);

	//3GAMMA FUNCTION DISABLE
	this->ILI9341_WriteCmd(0xF2);
	this->ILI9341_WriteData(0x00);

	//GAMMA CURVE SELECTED
	this->ILI9341_WriteCmd(0x26);
	this->ILI9341_WriteData(0x01);

	//POSITIVE GAMMA CORRECTION
	this->ILI9341_WriteCmd(0xE0);
	this->ILI9341_WriteData(0x0F);
	this->ILI9341_WriteData(0x31);
	this->ILI9341_WriteData(0x2B);
	this->ILI9341_WriteData(0x0C);
	this->ILI9341_WriteData(0x0E);
	this->ILI9341_WriteData(0x08);
	this->ILI9341_WriteData(0x4E);
	this->ILI9341_WriteData(0xF1);
	this->ILI9341_WriteData(0x37);
	this->ILI9341_WriteData(0x07);
	this->ILI9341_WriteData(0x10);
	this->ILI9341_WriteData(0x03);
	this->ILI9341_WriteData(0x0E);
	this->ILI9341_WriteData(0x09);
	this->ILI9341_WriteData(0x00);

	//NEGATIVE GAMMA CORRECTION
	this->ILI9341_WriteCmd(0xE1);
	this->ILI9341_WriteData(0x00);
	this->ILI9341_WriteData(0x0E);
	this->ILI9341_WriteData(0x14);
	this->ILI9341_WriteData(0x03);
	this->ILI9341_WriteData(0x11);
	this->ILI9341_WriteData(0x07);
	this->ILI9341_WriteData(0x31);
	this->ILI9341_WriteData(0xC1);
	this->ILI9341_WriteData(0x48);
	this->ILI9341_WriteData(0x08);
	this->ILI9341_WriteData(0x0F);
	this->ILI9341_WriteData(0x0C);
	this->ILI9341_WriteData(0x31);
	this->ILI9341_WriteData(0x36);
	this->ILI9341_WriteData(0x0F);

	//EXIT SLEEP
	this->ILI9341_WriteCmd(0x11);
	HAL_Delay(120);

	//TURN ON DISPLAY
	this->ILI9341_WriteCmd(0x29);

	//STARTING ROTATION
	this->ILI9341_SetRotation(SCREEN_VERTICAL_1);
}
void ili9341Driver::ILI9341Enable(void)
{
	HAL_GPIO_WritePin(LCD_RST_GPIO_Port, LCD_RST_Pin, GPIO_PIN_SET);
}
void ili9341Driver::ILI9341Reset(void)
{
	HAL_GPIO_WritePin(LCD_RST_GPIO_Port, LCD_RST_Pin, GPIO_PIN_RESET);
	HAL_Delay(200);
	HAL_GPIO_WritePin(LCD_RST_GPIO_Port, LCD_RST_Pin, GPIO_PIN_SET);
}
void ili9341Driver::ILI9341_WriteData(uint8_t Data)
{
	HAL_GPIO_WritePin(LCD_DC_GPIO_Port, LCD_DC_Pin, GPIO_PIN_SET);
	this->ILI9341_SPI_Send(Data);
}
void ili9341Driver::ILI9341_WriteCmd(uint8_t CMD)
{
	HAL_GPIO_WritePin(LCD_DC_GPIO_Port, LCD_DC_Pin, GPIO_PIN_RESET);
	this->ILI9341_SPI_Send(CMD);
}
void inline ili9341Driver::ILI9341_SPI_Send(uint8_t SPI_Data)
{

	while (this->UsedSPI->State != HAL_SPI_STATE_READY)
	{
	}
#ifdef CacheEnable
	SCB_CleanDCache();
#endif
	HAL_SPI_Transmit_DMA(this->UsedSPI, &SPI_Data, 1);
}
void ili9341Driver::ILI9341_SetRotation(uint8_t Rotation)
{
	uint8_t screen_rotation = Rotation;

	this->ILI9341_WriteCmd(0x36);
	HAL_Delay(1);

	switch (screen_rotation)
	{
	case SCREEN_VERTICAL_1:
		this->ILI9341_WriteData(0x40 | 0x08);
		this->LCD_WIDTH = 240;
		this->LCD_HEIGHT = 320;
		break;
	case SCREEN_HORIZONTAL_1:
		this->ILI9341_WriteData(0x20 | 0x08);
		this->LCD_WIDTH = 320;
		this->LCD_HEIGHT = 240;
		break;
	case SCREEN_VERTICAL_2:
		this->ILI9341_WriteData(0x80 | 0x08);
		this->LCD_WIDTH = 240;
		this->LCD_HEIGHT = 320;
		break;
	case SCREEN_HORIZONTAL_2:
		this->ILI9341_WriteData(0x40 | 0x80 | 0x20 | 0x08);
		this->LCD_WIDTH = 320;
		this->LCD_HEIGHT = 240;
		break;
	default:
		//EXIT IF SCREEN ROTATION NOT VALID!
		break;
	}
}
void ili9341Driver::ILI9341_FillScreen(uint16_t Colour)
{
	this->ILI9341_SetAddress(0, 0, LCD_WIDTH, LCD_HEIGHT);
	this->ILI9341_DrawColourBurst(Colour, LCD_WIDTH * LCD_HEIGHT);
}
void ili9341Driver::ILI9341_SetAddress(uint16_t X1, uint16_t Y1, uint16_t X2, uint16_t Y2)
{
	this->ILI9341_WriteCmd(0x2A);
	this->ILI9341_WriteData(X1 >> 8);
	this->ILI9341_WriteData(X1);
	this->ILI9341_WriteData(X2 >> 8);
	this->ILI9341_WriteData(X2);

	this->ILI9341_WriteCmd(0x2B);
	this->ILI9341_WriteData(Y1 >> 8);
	this->ILI9341_WriteData(Y1);
	this->ILI9341_WriteData(Y2 >> 8);
	this->ILI9341_WriteData(Y2);

	this->ILI9341_WriteCmd(0x2C);
}
void ili9341Driver::ILI9341_DrawColourBurst(uint16_t Colour, uint32_t Size)
{
	//SENDS COLOUR
	uint32_t Buffer_Size = 0;
	if ((Size * 2) < BURST_MAX_SIZE)
	{
		Buffer_Size = Size;
	}
	else
	{
		Buffer_Size = BURST_MAX_SIZE;
	}

	HAL_GPIO_WritePin(LCD_DC_GPIO_Port, LCD_DC_Pin, GPIO_PIN_SET);

	unsigned char chifted = Colour >> 8;
	;
	unsigned char burst_buffer[Buffer_Size];
	for (uint32_t j = 0; j < Buffer_Size; j += 2)
	{
		burst_buffer[j] = chifted;
		burst_buffer[j + 1] = Colour;
	}

	uint32_t Sending_Size = Size * 2;
	uint32_t Sending_in_Block = Sending_Size / Buffer_Size;
	uint32_t Remainder_from_block = Sending_Size % Buffer_Size;

	if (Sending_in_Block != 0)
	{
		for (uint32_t j = 0; j < (Sending_in_Block); j++)
		{
			while (this->UsedSPI->State != HAL_SPI_STATE_READY)
			{
			}
#ifdef CacheEnable
			SCB_CleanDCache();
#endif
			HAL_SPI_Transmit_DMA(this->UsedSPI, (unsigned char *)burst_buffer, Buffer_Size);
			//OwnDelay(100);
			//if(j%100==0)
			//HAL_Delay(1);
			//this->LCDdelay();
		}
	}

	//REMAINDER!
	while (this->UsedSPI->State != HAL_SPI_STATE_READY)
	{
	}
#ifdef CacheEnable
	SCB_CleanDCache();
#endif
	HAL_SPI_Transmit_DMA(this->UsedSPI, (unsigned char *)burst_buffer, Remainder_from_block);
}

void ili9341Driver::ILI9341_DrawText(const char *Text, uint8_t X, uint8_t Y, uint16_t Colour, uint16_t Size, uint16_t Background_Colour)
{
	while (*Text)
	{
		this->ILI9341_DrawChar(*Text++, X, Y, Colour, Size, Background_Colour);
		X += CHAR_WIDTH * Size;
	}
}
void ili9341Driver::ILI9341_DrawChar(char Character, uint8_t X, uint8_t Y, uint16_t Colour, uint16_t Size, uint16_t Background_Colour)
{
	uint8_t function_char;
	uint8_t i, j;

	function_char = Character;

	if (function_char < ' ')
	{
		Character = 0;
	}
	else
	{
		function_char -= 32;
	}

	char temp[CHAR_WIDTH];
	for (uint8_t k = 0; k < CHAR_WIDTH; k++)
	{
		temp[k] = font[function_char][k];
	}

	// Draw pixels
	this->ILI9341_DrawRectangle(X, Y, CHAR_WIDTH * Size, CHAR_HEIGHT * Size, Background_Colour);
	for (j = 0; j < CHAR_WIDTH; j++)
	{
		for (i = 0; i < CHAR_HEIGHT; i++)
		{
			if (temp[j] & (1 << i))
			{
				if (Size == 1)
				{
					this->ILI9341_DrawPixel(X + j, Y + i, Colour);
				}
				else
				{
					this->ILI9341_DrawRectangle(X + (j * Size), Y + (i * Size), Size, Size, Colour);
				}
			}
		}
	}
}
void ili9341Driver::ILI9341_DrawRectangle(uint16_t X, uint16_t Y, uint16_t Width, uint16_t Height, uint16_t Colour)
{
	if ((X >= this->LCD_WIDTH) || (Y >= this->LCD_HEIGHT))
		return;
	if ((X + Width - 1) >= this->LCD_WIDTH)
	{
		Width = this->LCD_WIDTH - X;
	}
	if ((Y + Height - 1) >= this->LCD_HEIGHT)
	{
		Height = this->LCD_HEIGHT - Y;
	}
	this->ILI9341_SetAddress(X, Y, X + Width - 1, Y + Height - 1);
	this->ILI9341_DrawColourBurst(Colour, Height * Width);
}
void ili9341Driver::ILI9341_DrawPixel(uint16_t X, uint16_t Y, uint16_t Colour)
{
	if ((X >= this->LCD_WIDTH) || (Y >= this->LCD_HEIGHT))
		return; //OUT OF BOUNDS!

	//ADDRESS
	HAL_GPIO_WritePin(LCD_DC_GPIO_Port, LCD_DC_Pin, GPIO_PIN_RESET);
	ILI9341_SPI_Send(0x2A);
	HAL_GPIO_WritePin(LCD_DC_GPIO_Port, LCD_DC_Pin, GPIO_PIN_SET);

	//XDATA
	unsigned char Temp_Buffer[4] = {(uint8_t)(X >> 8), (uint8_t)X, (uint8_t)((X + 1) >> 8), (uint8_t)(X + 1)};
	while (this->UsedSPI->State != HAL_SPI_STATE_READY)
	{
	}
#ifdef CacheEnable
	SCB_CleanDCache();
#endif
	HAL_SPI_Transmit_DMA(this->UsedSPI, Temp_Buffer, 4);

	//ADDRESS
	HAL_GPIO_WritePin(LCD_DC_GPIO_Port, LCD_DC_Pin, GPIO_PIN_RESET);
	ILI9341_SPI_Send(0x2B);
	HAL_GPIO_WritePin(LCD_DC_GPIO_Port, LCD_DC_Pin, GPIO_PIN_SET);

	//YDATA
	unsigned char Temp_Buffer1[4] = {(uint8_t)(Y >> 8), (uint8_t)Y, (uint8_t)((Y + 1) >> 8), (uint8_t)(Y + 1)};
	while (this->UsedSPI->State != HAL_SPI_STATE_READY)
	{
	}
#ifdef CacheEnable
	SCB_CleanDCache();
#endif
	HAL_SPI_Transmit_DMA(this->UsedSPI, Temp_Buffer1, 4);

	//ADDRESS
	HAL_GPIO_WritePin(LCD_DC_GPIO_Port, LCD_DC_Pin, GPIO_PIN_RESET);
	ILI9341_SPI_Send(0x2C);
	HAL_GPIO_WritePin(LCD_DC_GPIO_Port, LCD_DC_Pin, GPIO_PIN_SET);

	//COLOUR
	unsigned char Temp_Buffer2[2] = {(uint8_t)(Colour >> 8), (uint8_t)Colour};
	while (this->UsedSPI->State != HAL_SPI_STATE_READY)
	{
	}
#ifdef CacheEnable
	SCB_CleanDCache();
#endif
	HAL_SPI_Transmit_DMA(this->UsedSPI, Temp_Buffer2, 2);
}
void ili9341Driver::ILI9341_InitDynamicGraph(uint32_t Max, uint32_t Min)
{
	this->DynamicGraphMax = Max;
	this->DynamicGraphMin = Min;
	memset(this->DynamicGraphRAM,BLACK,100*320*2);
//	for (int i = 0; i < 100; i++)
//	{
//		for (int j = 0; j < 320; j++)
//		{
//			this->DynamicGraphRAM[i][j] = BLACK;
//		}
//	}
	for(int i=0;i<320;i++)
	{
		this->DynamicLine[i]=10;
	}

	//ILI9341_DrawLineToMEM(0,0,100,320);
}
void ili9341Driver::ILI9341_AddLineToDynamicGraph(void)
{
//	uint16_t Range=((this->DynamicGraphMax)-(this->DynamicGraphMin));
//	
//	for(int i=0;i<320;i++)
//	{
//		temp1=(uint16_t)((this->DynamicLine[i]*1.0/Range)*100);
//		this->ILI9341_DrawPointToMEM(temp1,i);
//	}
	uint16_t Range=((this->DynamicGraphMax)-(this->DynamicGraphMin));
	for(int i=0;i<319;i++)
	{
		temp1=(uint16_t)((this->DynamicLine[i]*1.0/Range)*100);
		temp2=(uint16_t)((this->DynamicLine[i+1]*1.0/Range)*100);
		ILI9341_DrawLineToMEM(temp1,i,temp2,(i+1));
	}
}
void ili9341Driver::ILI9341_AddPointToDynamicGraph(uint16_t Num)
{
//	if(Num>this->DynamicGraphMax)
//	Num=this->DynamicGraphMax;
//	else if(Num<this->DynamicGraphMin)
//	Num=this->DynamicGraphMin;
	for(uint16_t i=0;i<=318;i++)
	{
		this->DynamicLine[i]=this->DynamicLine[i+1];
	}
	this->DynamicLine[319]=Num;
}
void ili9341Driver::ILI9341_UpdateDynamicGraph(void)
{
	//SCB_EnableDCache();
	static uint32_t count = 0;
	uint32_t counter = 0;
	uint8_t *Point = (unsigned char *)this->DynamicGraphRAM;
	uint8_t temp = 0;
	unsigned char Temp_small_buffer[BURST_MAX_SIZE];
	memset(this->DynamicGraphRAM,BLACK,100*320*2);
	
	this->ILI9341_AddLineToDynamicGraph();
	
	this->ILI9341_SetAddress(0, 140, LCD_WIDTH, LCD_HEIGHT);
	HAL_GPIO_WritePin(LCD_DC_GPIO_Port, LCD_DC_Pin, GPIO_PIN_SET);
//	while (this->UsedSPI->State != HAL_SPI_STATE_READY)
//	{
//	}
//	#ifdef CacheEnable
//	SCB_CleanDCache();
//	#endif
//	HAL_SPI_Transmit_DMA(this->UsedSPI, &temp, 1);
	for (uint32_t i = 0; i < 100 * 320 * 2 / BURST_MAX_SIZE; i++)
	{
		memcpy(Temp_small_buffer,&Point[counter],BURST_MAX_SIZE);
		while (this->UsedSPI->State == HAL_SPI_STATE_BUSY_TX)
		//while (((DMA_Stream_TypeDef *)this->UsedSPI->Instance)->NDTR!=1)
		{
		}
		#ifdef CacheEnable
		SCB_CleanDCache();
		#endif
		//HAL_SPI_Transmit_DMA(this->UsedSPI, Temp_small_buffer, BURST_MAX_SIZE);
		HAL_SPI_Transmit(this->UsedSPI, Temp_small_buffer, BURST_MAX_SIZE,1);
		counter += BURST_MAX_SIZE;
	}
	//SCB_DisableDCache();
	
}
void ili9341Driver::ILI9341_DrawPointToMEM(uint16_t x, uint16_t y)
{
	this->DynamicGraphRAM[x][y]=WHITE;
}
void ili9341Driver::ILI9341_TEST(void)
{
		static int i,j;
	
			this->ILI9341_DrawPointToMEM(i,j);

	if(j<320)
	{
		j++;
	}
	else
	{
		if(i<100)
		{
		i++;
			j=0;
		}
		else
		{
		i=0;
		j=0;
		}
	}
}
void ili9341Driver::ILI9341_DrawLineToMEM(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1)
{
	int32_t dx,
		dy,
		dx2,
		dy2,
		x_inc,
		y_inc,
		error,
		index;
	dx = x1 - x0;
	dy = y1 - y0;

	if (dx >= 0)
	{
		x_inc = 1;
	}
	else
	{
		x_inc = -1;
		dx = -dx;
	}

	if (dy >= 0)
	{
		y_inc = 1;
	}
	else
	{
		y_inc = -1;
		dy = -dy;
	}

	dx2 = dx << 1;
	dy2 = dy << 1;
	if (dx > dy)
	{
		error = dy2 - dx;

		for (index = 0; index <= dx; index++)
		{
			this->ILI9341_DrawPointToMEM(x0, y0);
			if (error >= 0)
			{
				error -= dx2;
				y0 += y_inc;
			}
			error += dy2;
			x0 += x_inc;
		}
	}

	else
	{
		error = dx2 - dy;

		for (index = 0; index <= dy; index++)
		{
			this->ILI9341_DrawPointToMEM(x0, y0);
			if (error >= 0)
			{
				error -= dy2;
				x0 += x_inc;
			}
			error += dx2;
			y0 += y_inc;
		}
	}
}
void inline ili9341Driver::ILI9341_SetXY(uint16_t Xpos, uint16_t Ypos)
{
	this->ILI9341_WriteCmd(0x2a);
	this->ILI9341_Write16BitData(Xpos);
	this->ILI9341_WriteCmd(0x2b);
	this->ILI9341_Write16BitData(Ypos);
	this->ILI9341_WriteCmd(0x2c);
	HAL_GPIO_WritePin(LCD_DC_GPIO_Port, LCD_DC_Pin, GPIO_PIN_SET);
}
void inline ili9341Driver::ILI9341_Write16BitData(uint16_t Data)
{
	this->ILI9341_WriteData(Data >> 8);
	this->ILI9341_WriteData(Data);
}
void ili9341Driver::ILI9341_AppendList(uint8_t * List)
{
	static int AppendListNum;
	static uint8_t* ListGet[15];
	if(AppendListNum<=14)
	{
		this->ILI9341_DrawText((const char*)List,0,AppendListNum*16,BLACK,2,WHITE);
		ListGet[AppendListNum]=List;
		AppendListNum++;
	}
	else
	{
		for(int i=0;i<=13;i++)
		{
			//Gui_DrawFont_GBK16(0,i*16,BLACK,WHITE,ListGet[i+1]);
			//ListGet[i]=NULL;
			
			ListGet[i]=ListGet[i+1];
		}
		//ListGet[14]=NULL;
		ListGet[14]=List;
		//this->ILI9341_FillScreen(WHITE);
		for(int i=0;i<=14;i++)
		{
			this->ILI9341_ClearReaginSet(0,i*16,240,16*(i+1));
		//Gui_DrawFont_GBK16(0,i*16,BLACK,WHITE,ListGet[i]);
			this->ILI9341_DrawText((const char*)ListGet[i],0,i*16,BLACK,2,WHITE);
		}
	}
		
}
void ili9341Driver::ILI9341_ClearReaginSet(int Bx,int By,int Ex,int Ey)
{
//	static int Y;
//	Y=By;
//	while(Y<=Ey)
//	{
//		for(int X=Bx;X<=Ex;X++)
//		{
//			this->ILI9341_DrawPixel(X,Y,WHITE);
//		}
//		Y++;
//	}
	this->ILI9341_SetAddress(Bx, By, Ex, Ey);
	this->ILI9341_DrawColourBurst(WHITE, (Ex-Bx)*(Ey-By));
}