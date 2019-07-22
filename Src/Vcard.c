// master

#include <stdlib.h>
#include "Vcard.h"
#include "Get_A.h"
#include "Put_A.h"
#include "pn532.h"
#include "MifClass.h"
#include "Macros.h"

#define AUT_MAX 10

extern TIM_HandleTypeDef htim1;
extern TIM_HandleTypeDef htim2;
extern SPI_HandleTypeDef hspi1;
extern UART_HandleTypeDef huart1;
extern __IO uint32_t uwTick;

uint8_t Filter[] = {"ZERO OR OTP FILTER AVAILABLE  !\n\r"};
uint8_t razd[] = {"______________________________\n\r"};
uint32_t TagChal[AUT_MAX], AB1[AUT_MAX], AB2[AUT_MAX];
uint8_t j_aut, ZeroFilter, GrabOK, EndOfFrame, KeyAB[AUT_MAX], BlockNumber[AUT_MAX];
extern uint8_t UidCL1[];

uint16_t streamB[900],nstrB;
uint16_t streamB_1[900],nstrB_1;
uint16_t streamNAK[] = {763,83,83,83,423,83,83,83,83,83,83,83,763,83,83,83,83}, nstrNAK = 17;

uint8_t data_A[FRAME_SIZE][BUFFER_SIZE], data_B[FRAME_SIZE][BUFFER_SIZE];
uint8_t ndata_A[FRAME_SIZE], ndata_B[FRAME_SIZE];
uint8_t nd;
uint8_t uidLength = 4,nuid;  //  UID
uint8_t Tx[512];
uint16_t  fv_1;



void InitPN532_1(){

	uint16_t Adr;
	uint8_t r1;
	static uint8_t r2 =0x13;

	CS_LOW(&hspi1);
	HAL_Delay(1);
	CS_HIGH(&hspi1);
	while (!(fv_1 = getFirmwareVersion(&hspi1)));
	SAM_VirtualCard(&hspi1);
	HAL_Delay(1000);
	Adr = 0x6106;
	readRegister(&hspi1, &Adr, &r1, 1);
	r1 = r2;
	writeRegister(&hspi1, Adr, r1);

}


void InitVirtCard(){
  
  HAL_TIM_OC_Start  ( &htim1, TIM_CHANNEL_4 );
  HAL_TIM_PWM_Start  ( &htim2, TIM_CHANNEL_4 );

}


void conv(uint32_t *a, uint8_t *d){
	*a = d[0];
	for(int i = 1; i < 4; i++){
		*a <<= 8;
		*a += d[i];
	}
}


void prndata(){

//	return;
	uint8_t t, i, j;
	uint8_t *p;
	for(i = 0; i < (nd); i++){
		p = Tx;
		t = sprintf((char *)p,"\n\rReader  ");
		p += t;
		for(j = 0; j < ndata_A[i]; j++){
			t = sprintf((char *)p," %2.2X",data_A[i][j]);
			p += t;
		}
		HAL_UART_Transmit(&huart1, Tx, (p - Tx), 1000);

		p = Tx;
		t = sprintf((char *)p,"\n\rTAG     ");
		p += t;
		for(j = 0; j < ndata_B[i]; j++){
			t = sprintf((char *)p," %2.2X",data_B[i][j]);
			p += t;
		}
		HAL_UART_Transmit(&huart1, Tx, (p - Tx), 1000);
	}
}


uint8_t EmulCard(void){

	uint8_t w = 0;
	uint16_t inbit, outbit;
	uint8_t k[] = {'A','B'};
	uint8_t tmp;
	uint8_t cnt[170], ncnt;
	uint8_t  lastbit = 0;
	uint8_t scs, t;
	static uint8_t AuthNumber = 0;

	nd = 0;
	ZeroFilter = 0;
	GrabOK = 0;
	EndOfFrame = 0;
	j_aut = 0;

	__HAL_TIM_SET_COUNTER(&htim1, 0);
	srand(uwTick);

	while(!(scs = getStream_A(cnt, &ncnt, 1000)) || !ncnt){			// ќжидаем 1-й посылки от ридера
		if(!w){
			t = sprintf((char *)Tx,"\n\rWaiting for  Reader");
			HAL_UART_Transmit(&huart1,(uint8_t *)Tx,t,1000);
			w = 1;
		}
		else{
			tmp = ',';
			HAL_UART_Transmit(&huart1,&tmp,1,1000);
		}
	}

	while(1){
		inbit = ConvertStream_A(cnt, ncnt, data_A[nd], &ndata_A[nd], &lastbit);
		for(uint8_t i = 0; i < ndata_A[nd]; i++){
			data_B[nd][i] = data_A[nd][i];
		}
		outbit = MifareClassicAppProcess( data_B[nd], inbit);
		if(EndOfFrame){
			break;
		}
		if(GrabOK){
			GrabOK = 0;
			if(!ZeroFilter || (j_aut >= AUT_MAX)){
				break;
			}
		}

		ndata_B[nd] = 0;
		if(outbit == 4){
			SendBits_A(data_B[nd][0], 4, lastbit);
			ndata_B[nd] = 1;
		}
		else if(outbit >= 8){
			ndata_B[nd] = outbit  >> 3;
			PutData_A(data_B[nd], ndata_B[nd], lastbit);
		}
		nd++;
		do{
			scs = getStream_A(cnt, &ncnt, 1000);
			if(!scs){
				return 1;
			}
		}while(!ncnt);

		if(nd >= FRAME_SIZE){
			return 2;
		}

	}

//	prndata();

	AuthNumber++;
	t = sprintf((char *) Tx,"\n\r%s\n\rAuthentication Number  %d\n\r\
UID                 0x%2.2X%2.2X%2.2X%2.2X\n\r",razd, AuthNumber,\
UidCL1[0],UidCL1[1],UidCL1[2],UidCL1[3]);
	HAL_UART_Transmit(&huart1, Tx, t, 1000);

	if(ZeroFilter){
		HAL_UART_Transmit(&huart1,Filter,(sizeof(Filter) - 1),1000);
	}

	for(uint8_t i = 0; i <j_aut; i++){
		t = sprintf((char *)Tx,"\n\r\
KeyNumber  %d        Block %d   Key %c\n\r\
Tag Challenge       0x%8.8X\n\r\
Reader Challenge    0x%8.8X\n\r\
Reader Response     0x%8.8X\n\r", i+1, BlockNumber[i],\
	k[KeyAB[i]], TagChal[i], AB1[i], AB2[i]);
		HAL_UART_Transmit(&huart1, Tx, t, 1000);
	}

    return 0;
}


void vc(){

	uint8_t err,t;

	if((err = EmulCard())){
		if(err == 1){
			t = sprintf((char *)Tx,"\n\rTimeout !\n\r");
			HAL_UART_Transmit(&huart1, Tx, t, 1000);
		}else if(err == 2){
			t = sprintf((char *)Tx,"\n\rBuffer overflowed !\n\r");
			HAL_UART_Transmit(&huart1, Tx, t, 1000);
		}

//		prndata();
	}
	HAL_Delay(1000);
}

