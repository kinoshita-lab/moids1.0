/*

	main.c ���悢��v���g�ŏI�o�[�W�����I

	�d�l�@�����f�[�^��8�r�b�g/31250Hz
	      �A�i���O���͂ɔ������ĉ������ł�




*/
//WinAVR
#include <avr/io.h>
#include <avr/signal.h>		// include "signal" names (interrupt names)
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <avr/sleep.h>
#include <inttypes.h>
#include <avr/delay.h>

//AVRlib
#include "avrlibdefs.h"
#include "avrlibtypes.h"
#include "timer.h"
#include "a2d.h"

//MyLib
#include "defs.h"

//Myincldes
#include "global.h"

#define CLK_CALIB_DATA (FLASHEND - 3) // for 8MHz
#define ADC_THRES 35

void init(void);
void calib_adc();

uint8_t adc_zero;

int main(void){
	
	uint8_t val;
	
	cli();
	
	init();
	calib_adc();
	sei();
	fWait = 1;

	//timer
	timerInit();	// initialize pulse library
	timer1PWMInit(8); //default 8  bit init
	timer1PWMInitICR(0xff);
	OCR1AL = 0x80;//Analog zero;
	timer1PWMAOn();
	


	//���g���ݒ�
	freq_idx = 1;	

	//�t���O����
	fSnd = 0;
	

	//�ŏ����炷
	fSnd = 2; //������ �f�B���C���[�h�ɓ˓�

	for(; ;){
			//PRINT("fSnd %x, %x\n", fSnd);

			//���i��AD�݂Ă�
			val = a2dConvert8bit(ADC_CH_ADC0); 
			//PRINT("val = %x\n", val);
			//臒l���������莞�ԉ����Ȃ�
			if ( (!(fSnd & 0x03)) && (val <= (adc_zero - ADC_THRES)) ){

				fWait = 0;
				//��莞�ԉ����ł�
				//PRINT(" gotcha %x, %x\n", freq_idx, val);
				fSnd = 2; //������ �f�B���C���[�h�ɓ˓�
			}
			
	}
	

	return 0;
}
 
void init()
{	
	//calib clock @ 8MHz
	uint8_t osccal_data = pgm_read_byte(CLK_CALIB_DATA);
	if (osccal_data != 0xff) OSCCAL = osccal_data;

	//adc
	a2dInit();
	
	fSnd = 0;
	fReset = 0;

	//port 
	DDRB = 0xff;
	DDRD = 0xff;


	return;
}

void calib_adc(void)
{
	//PRINT(" caliblating adc... \n", 0);

	uint8_t i;
	uint16_t sval = 0;
	
	for (i=0; i<100; i++){
		sval += a2dConvert8bit(ADC_CH_ADC0);
	}

	adc_zero = sval / 100;
	//PRINT(" adczero = %x\n", adc_zero);
	wait = 303;

	return;
}



