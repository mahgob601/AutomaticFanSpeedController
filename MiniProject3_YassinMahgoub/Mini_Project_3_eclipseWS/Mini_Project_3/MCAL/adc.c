/*
 * adc.c
 *
 *  Created on: Oct 11, 2023
 *      Author: Yassin Mahgoub
 *      Description: Source file for the AVR adc driver
 */


#include "avr/io.h"
#include <avr/interrupt.h>
#include "adc.h"
#include "../std_types.h"



/*
 * global value holding the ref volatge
 * depending on the value coming from the created struct
 * avcc is configured in adc.h as 5v
 *
 */
volatile float32 g_adcRefVolt = 0;

/*
 * configuring the mode of adc
 * including ref voltage, ref mode and prescale value
 *  applied bit fields for the ADMUX, ADCSRA regs in adcReg.h for easier access
 */
void ADC_init(const ADC_ConfigType * Config_Ptr)
{
	switch(Config_Ptr->ref_volt)
	{
	case ADC_AVCC_MODE:
		ADMUX_R.Bits.REFS_Val = ADC_AVCC_MODE_VAL;
		g_adcRefVolt = ADC_AVCC_REF_VOLT;
		break;
	case ADC_INTERNAL_REF_MODE:
		ADMUX_R.Bits.REFS_Val = ADC_INTERNAL_REF_MODE_VAL;
		g_adcRefVolt = ADC_INTERNAL_REF_VOLT;
		break;

	}

	// ADMUX values
	//ADMUX_R.Bits.REFS_Val = Config_Ptr->ref_volt;
	ADMUX_R.Bits.ADLAR_Val = LOGIC_LOW;

	// ADCSRA values
	ADCSRA_R.Bits.ADEN_Val = LOGIC_HIGH;
	ADCSRA_R.Bits.ADPS_2to0_Val = Config_Ptr->prescaler;

}

/*
 * synch function responsible for conversion of
 * analog to digital value
 * and returning the 10-bits value of the adc after conversion
 */
uint16 ADC_readChannel(uint8 channel)
{
	ADMUX_R.Bits.MUX_Val = 0;
	ADMUX_R.Bits.MUX_Val = channel;
	ADCSRA_R.Bits.ADSC_Val = LOGIC_HIGH;
	//Polling and waiting for conversion completion flag
	while(ADCSRA_R.Bits.ADIF_Val != LOGIC_HIGH);
	// clearing the flag after conversion
	ADCSRA_R.Bits.ADIF_Val = LOGIC_HIGH;
	return ADC;
}
