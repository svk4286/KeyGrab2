
#ifndef __PN532_H
#define __PN532_H

#include "stm32f1xx_hal.h"


#define CS_LOW(__SPI__)    if((__SPI__) == &hspi1)\
                    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_RESET); \
                  else\
                    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, GPIO_PIN_RESET);\
                      HAL_Delay(0)
                      
#define CS_HIGH(__SPI__)    if((__SPI__) == &hspi1)\
                    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_SET); \
                  else\
                    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, GPIO_PIN_SET)

#define true 1
#define false 0

#define PN532_PREAMBLE                      (0x00)
#define PN532_STARTCODE1                    (0x00)
#define PN532_STARTCODE2                    (0xFF)
#define PN532_POSTAMBLE                     (0x00)

#define PN532_HOSTTOPN532                   (0xD4)
#define PN532_PN532TOHOST                   (0xD5)

// PN532 Commands
#define PN532_COMMAND_DIAGNOSE              (0x00)
#define PN532_COMMAND_GETFIRMWAREVERSION    (0x02)
#define PN532_COMMAND_GETGENERALSTATUS      (0x04)
#define PN532_COMMAND_READREGISTER          (0x06)
#define PN532_COMMAND_WRITEREGISTER         (0x08)
#define PN532_COMMAND_READGPIO              (0x0C)
#define PN532_COMMAND_WRITEGPIO             (0x0E)
#define PN532_COMMAND_SETSERIALBAUDRATE     (0x10)
#define PN532_COMMAND_SETPARAMETERS         (0x12)
#define PN532_COMMAND_SAMCONFIGURATION      (0x14)
#define PN532_COMMAND_POWERDOWN             (0x16)
#define PN532_COMMAND_RFCONFIGURATION       (0x32)
#define PN532_COMMAND_RFREGULATIONTEST      (0x58)
#define PN532_COMMAND_INJUMPFORDEP          (0x56)
#define PN532_COMMAND_INJUMPFORPSL          (0x46)
#define PN532_COMMAND_INLISTPASSIVETARGET   (0x4A)
#define PN532_COMMAND_INATR                 (0x50)
#define PN532_COMMAND_INPSL                 (0x4E)
#define PN532_COMMAND_INDATAEXCHANGE        (0x40)
#define PN532_COMMAND_INCOMMUNICATETHRU     (0x42)
#define PN532_COMMAND_INDESELECT            (0x44)
#define PN532_COMMAND_INRELEASE             (0x52)
#define PN532_COMMAND_INSELECT              (0x54)
#define PN532_COMMAND_INAUTOPOLL            (0x60)
#define PN532_COMMAND_TGINITASTARGET        (0x8C)
#define PN532_COMMAND_TGSETGENERALBYTES     (0x92)
#define PN532_COMMAND_TGGETDATA             (0x86)
#define PN532_COMMAND_TGSETDATA             (0x8E)
#define PN532_COMMAND_TGSETMETADATA         (0x94)
#define PN532_COMMAND_TGGETINITIATORCOMMAND (0x88)
#define PN532_COMMAND_TGRESPONSETOINITIATOR (0x90)
#define PN532_COMMAND_TGGETTARGETSTATUS     (0x8A)

#define PN532_RESPONSE_INDATAEXCHANGE       (0x41)
#define PN532_RESPONSE_INLISTPASSIVETARGET  (0x4B)

#define PN532_WAKEUP                        (0x55)

#define PN532_SPI_STATREAD                  (0x02)
#define PN532_SPI_DATAWRITE                 (0x01)
#define PN532_SPI_DATAREAD                  (0x03)
#define PN532_SPI_READY                     (0x01)

#define PN532_I2C_ADDRESS                   (0x48 >> 1)
#define PN532_I2C_READBIT                   (0x01)
#define PN532_I2C_BUSY                      (0x00)
#define PN532_I2C_READY                     (0x01)
#define PN532_I2C_READYTIMEOUT              (20)

#define PN532_MIFARE_ISO14443A              (0x00)

// Mifare Commands
#define MIFARE_CMD_AUTH_A                   (0x60)
#define MIFARE_CMD_AUTH_B                   (0x61)
#define MIFARE_CMD_READ                     (0x30)
#define MIFARE_CMD_WRITE                    (0xA0)
#define MIFARE_CMD_TRANSFER                 (0xB0)
#define MIFARE_CMD_DECREMENT                (0xC0)
#define MIFARE_CMD_INCREMENT                (0xC1)
#define MIFARE_CMD_STORE                    (0xC2)
#define MIFARE_ULTRALIGHT_CMD_WRITE         (0xA2)

// Prefixes for NDEF Records (to identify record type)
#define NDEF_URIPREFIX_NONE                 (0x00)
#define NDEF_URIPREFIX_HTTP_WWWDOT          (0x01)
#define NDEF_URIPREFIX_HTTPS_WWWDOT         (0x02)
#define NDEF_URIPREFIX_HTTP                 (0x03)
#define NDEF_URIPREFIX_HTTPS                (0x04)
#define NDEF_URIPREFIX_TEL                  (0x05)
#define NDEF_URIPREFIX_MAILTO               (0x06)
#define NDEF_URIPREFIX_FTP_ANONAT           (0x07)
#define NDEF_URIPREFIX_FTP_FTPDOT           (0x08)
#define NDEF_URIPREFIX_FTPS                 (0x09)
#define NDEF_URIPREFIX_SFTP                 (0x0A)
#define NDEF_URIPREFIX_SMB                  (0x0B)
#define NDEF_URIPREFIX_NFS                  (0x0C)
#define NDEF_URIPREFIX_FTP                  (0x0D)
#define NDEF_URIPREFIX_DAV                  (0x0E)
#define NDEF_URIPREFIX_NEWS                 (0x0F)
#define NDEF_URIPREFIX_TELNET               (0x10)
#define NDEF_URIPREFIX_IMAP                 (0x11)
#define NDEF_URIPREFIX_RTSP                 (0x12)
#define NDEF_URIPREFIX_URN                  (0x13)
#define NDEF_URIPREFIX_POP                  (0x14)
#define NDEF_URIPREFIX_SIP                  (0x15)
#define NDEF_URIPREFIX_SIPS                 (0x16)
#define NDEF_URIPREFIX_TFTP                 (0x17)
#define NDEF_URIPREFIX_BTSPP                (0x18)
#define NDEF_URIPREFIX_BTL2CAP              (0x19)
#define NDEF_URIPREFIX_BTGOEP               (0x1A)
#define NDEF_URIPREFIX_TCPOBEX              (0x1B)
#define NDEF_URIPREFIX_IRDAOBEX             (0x1C)
#define NDEF_URIPREFIX_FILE                 (0x1D)
#define NDEF_URIPREFIX_URN_EPC_ID           (0x1E)
#define NDEF_URIPREFIX_URN_EPC_TAG          (0x1F)
#define NDEF_URIPREFIX_URN_EPC_PAT          (0x20)
#define NDEF_URIPREFIX_URN_EPC_RAW          (0x21)
#define NDEF_URIPREFIX_URN_EPC              (0x22)
#define NDEF_URIPREFIX_URN_NFC              (0x23)

#define PN532_GPIO_VALIDATIONBIT            (0x80)
#define PN532_GPIO_P30                      (0)
#define PN532_GPIO_P31                      (1)
#define PN532_GPIO_P32                      (2)
#define PN532_GPIO_P33                      (3)
#define PN532_GPIO_P34                      (4)
#define PN532_GPIO_P35                      (5)

#define RF_field                            (0x01)
#define Setting_for_A                       (0x0A)
#define RF_ON                               (0x01)
#define RF_OFF                              (0x00)

  uint8_t     SAM_Config(SPI_HandleTypeDef *hspi);
  uint8_t     SAM_VirtualCard(SPI_HandleTypeDef *hspi);
  uint32_t    getFirmwareVersion(SPI_HandleTypeDef *hspi);
  uint8_t     inDataExchange( SPI_HandleTypeDef *hspi, uint8_t * send, uint8_t sendLength, uint8_t * response, uint8_t * responseLength );
  uint8_t     readPassiveTargetID( SPI_HandleTypeDef *hspi, uint8_t cardbaudrate, uint8_t * uid, uint8_t * uidLength);
  
  uint8_t     sendCommandCheckAck(SPI_HandleTypeDef *hspi, uint8_t *cmd, uint8_t cmdlen, uint16_t timeout );  
  uint8_t     writeGPIO(SPI_HandleTypeDef *hspi, uint8_t pinstate);
  uint8_t     readGPIO(SPI_HandleTypeDef *hspi );
  uint8_t     setPassiveActivationRetries(SPI_HandleTypeDef *hspi, uint8_t maxRetries);

  uint8_t readRegister(SPI_HandleTypeDef *hspi, uint16_t *Adr,uint8_t *rd, uint8_t n);
  uint8_t     writeRegister(SPI_HandleTypeDef *hspi, uint16_t ADR,uint8_t d);
  uint8_t     RFConfiguration_A(SPI_HandleTypeDef *hspi);
  uint8_t     RFfield(SPI_HandleTypeDef *hspi, uint8_t rf);
  
  void        readdata(SPI_HandleTypeDef *hspi, uint8_t* buff, uint8_t n, uint16_t timeout);
  HAL_StatusTypeDef          writecommand(SPI_HandleTypeDef *hspi, uint8_t* cmd, uint8_t cmdlen, uint16_t timeout);
  uint8_t       isready(SPI_HandleTypeDef *hspi );
  uint8_t       waitready(SPI_HandleTypeDef *hspi, uint16_t timeout);
  uint8_t       readack(SPI_HandleTypeDef *hspi );
  
  uint8_t   Transceive(SPI_HandleTypeDef *hspi, uint8_t *tr, uint8_t ntr, uint8_t *rec, uint8_t *nrec);

  void InitPN532_1(void);
  uint8_t InitPN532_2(uint8_t *uid, uint8_t *nuid);
#endif
