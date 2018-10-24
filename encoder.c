/*
 * encoder.c
 *
 *  Created on: 24 paü 2018
 *      Author: HorochovPL
 */

#include <avr/interrupt.h>
#include <avr/io.h>
#include "../avrElapsedTime/elapsedTime.h"
#include "encoder.h"

volatile int encStep;

#define PORT(x) __PORT(x)
#define __PORT(x) (PORT##x)

#define PIN(x) __PIN(x)
#define __PIN(x) (PIN##x)

#define DDR(x) __DDR(x)
#define __DDR(x) (DDR##x)

//typedef struct
//{
//	uint8_t pin;
//	uint8_t *PORT;
//}pinout;
//
//#define DDR(port)	(*(port - PORTB + DDRB))
//#define PIN(port)	(*(port - PORTB + PINB))




void encoder_init(void)
{
/*
 * Interrupt attacher
 */
#if _ENC_INTERRUPT_TYPE == _ENC_PCINT
	PCICR|=(1<<_ENC_PCIEx);
	#define PCMSKx __CONCAT(PCMSK, _ENC_PCIEx)
		PCMSKx |= (1<<_ENC_PCINTx);
	#if _ENC_PCIEx>2 || _ENC_PCIEx<0
		#error unsupported interrupt PCIEx!
	#endif
#else
	#if _ENC_INTx==0
		EICRA|=(1<<ISC01);//|(1<<ISC00);	//falling edge trigger
		EIMSK|=(1<<INT0);
	#elif _ENC_INTx==1
		EICRA|=(1<<ISC11);	//falling edge trigger
		EIMSK|=(1<<INT1);
	#else
		#error unsupported interrupt number!
	#endif
#endif
	//in
	DDR(_ENC_PORT_P1)&=~(1<<_ENC_PIN_P1);

	DDR(_ENC_PORT_P2)&=~(1<<_ENC_PIN_P2);
	//pullup
	PORT(_ENC_PORT_P2)|=(1<<_ENC_PIN_P2);
	PORT(_ENC_PORT_P1)|=(1<<_ENC_PIN_P1);

}

#if _ENC_INTERRUPT_TYPE == _ENC_HW_INT
#if _ENC_INTx == 0
	ISR(INT0_vect)
#else
	ISR(INT1_vect)
#endif
{
	//filter
	static uint16_t time;
	if( (uint16_t) (timer_getMs()-time) < 10)
		return;
	time=timer_getMs();
	if(PIN(_ENC_PORT_P2)&(1<<_ENC_PIN_P2))
		++encStep;
	else
		--encStep;
}
#else

	void encoder_pcintIsrCall(void)
{
	static uint16_t time;
	//filter
	if(!(PIN(_ENC_PORT_P1)&(1<<_ENC_PIN_P1)))
	{
		if( (uint16_t) (timer_getMs()-time) < 10)
			return;
		time=timer_getMs();
		if(PIN(_ENC_PORT_P2)&(1<<_ENC_PIN_P2))
			++encStep;
		else
			--encStep;
	}
}
#endif

int encoder_status(void)
{
	return encStep;
}
