/*
 * encoder.h
 *
 *  Created on: 24 paü 2018
 *      Author: HorochovPL
 */

#ifndef _ENCODER_ENCODER_H_
#define _ENCODER_ENCODER_H_
#define _ENC_HW_INT	0
#define _ENC_PCINT	1

/*
 * Connect it like this:
 * left and right pin to uC, where P1 is interrupt one
 * mid pin goes to GND.
 * Consider putting 1,5nF caps between P1<>GND and P2<>GND
 */

#define _ENC_PIN_P1 PD2
#define _ENC_PORT_P1 D
#define _ENC_PIN_P2 PD3
#define _ENC_PORT_P2 D

#define _ENC_INTERRUPT_TYPE	_ENC_PCINT


#if _ENC_INTERRUPT_TYPE==_ENC_PCINT
/*
 * First, check if your uC does have this functionality
 * m328:
 * PCIE0: PCINT[7:0]
 * PCIE1: PCINT[14:8]	//wait.. No 15?
 * PCIE2: PCINT[23:16]
 */
#define _ENC_PCIEx	2		//check in datasheet
#define _ENC_PCINTx (18-16)	//set it to desired PCINT minus first element from the same PCIEx
/*
 * Insert this into PCINTx_vect interrupt vector!
 */
void encoder_pcintIsrCall(void);

#else

#define _ENC_INTx 0

#endif


void encoder_init(void);
int encoder_status(void);


#endif /* ENCODER_ENCODER_H_ */
