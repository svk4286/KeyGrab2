#ifndef __PUT_B_H
#define __PUT_B_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"
  
void InitTim3(void);
void PutStream_B(uint8_t *bits, uint8_t n);



#endif      //__PUT_B_H
