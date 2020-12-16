#ifndef __FONT_H
#define __FONT_H
#ifdef __cplusplus
 extern "C" {
#endif


#include "stm32h7xx_hal.h"

#define USE_ONCHIP_FLASH_FONT 1
#define hz16_num   50
#define hz24_num   20

struct typFNT_GB162
{
       uint8_t Index[2];	
       int8_t Msk[32];
};

struct typFNT_GB242
{
       uint8_t Index[2];	
       int8_t Msk[72];
};

extern const uint8_t asc16[];
extern const uint8_t sz32[];
extern const struct typFNT_GB162 hz16[];
extern const struct typFNT_GB242 hz24[];

#ifdef __cplusplus
}
#endif
#endif /*__FONT_H */
