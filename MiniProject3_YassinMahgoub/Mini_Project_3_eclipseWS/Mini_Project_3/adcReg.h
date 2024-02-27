/*
 * adcReg.h
 *
 *  Created on: Oct 11, 2023
 *      Author: Yassin
 *      Description: header file to define adc registers (admux, adcsra) using bitfields
 */

#ifndef SRC_ADCREG_H_
#define SRC_ADCREG_H_
#include "std_types.h"

// bit-fields for the admux register
typedef union{
	uint8 Byte;
	struct{
		uint8 MUX_Val:5;
		uint8 ADLAR_Val:1;
		uint8 REFS_Val: 2;
	}Bits;

}ADMUX_R_TYPE;

// bit-fields for the adcsra register
typedef union{
	uint8 Byte;
	struct{
		uint8 ADPS_2to0_Val:3;
		uint8 ADIE_Val:1;
		uint8 ADIF_Val:1;
		uint8 ADATE_Val:1;
		uint8 ADSC_Val:1;
		uint8 ADEN_Val:1;
	}Bits;

}ADCSRA_R_TYPE;




#define ADMUX_R (*(ADMUX_R_TYPE* volatile const) 0x27)
#define ADCSRA_R (*(ADCSRA_R_TYPE* volatile const) 0x26)



#endif /* SRC_ADCREG_H_ */
