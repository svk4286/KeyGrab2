

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __VCARD_H
#define __VCARD_H

#ifdef __cplusplus
extern "C" {
#endif


#include "stm32f1xx_hal.h"

#define BUFFER_SIZE  64
#define BUFFER_PAR   (BUFFER_SIZE/2)
#define FRAME_SIZE	40

uint8_t VirtCard();
void InitVirtCard();
void conv(uint32_t *a, uint8_t *d);
uint8_t InitPN532_2zero();
void iso14443a_crc_append(uint8_t *pbtData, size_t szLen);
void vc();
void InitPN532_1();
uint8_t InitPN532_2(uint8_t *uid, uint8_t *nuid);
void deInitReg();
void InitReg();
void conv(uint32_t *a, uint8_t *d);

#ifdef __cplusplus
}
#endif

#endif /* __VCARD_H */


