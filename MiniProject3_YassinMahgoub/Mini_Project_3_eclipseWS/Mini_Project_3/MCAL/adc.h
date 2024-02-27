/*
 * adc.h
 *
 *  Created on: Oct 11, 2023
 *      Author: Yassin
 *      Description: Header file for the AVR adc driver
 */

#ifndef SRC_ADC_H_
#define SRC_ADC_H_
#include "../adcReg.h"

/*
 * stores ref volt whether in case of avcc(5v)
 * or INTERNAL_MODE (2.56v)
 */
extern volatile float32 g_adcRefVolt;


/*
 * Two modes of ref volt and their corrspondig configured value
 */
#define ADC_INTERNAL_REF_VOLT 2.56
#define ADC_AVCC_REF_VOLT 5



//#define ADC_REF_VOLT 2.56
#define ADC_MAX_VALUE 1023


/*
 * Vref modes
 * each mode is defined by
 *  the corresponding
 */

#define ADC_AREF_MODE_VAL 0
#define ADC_AVCC_MODE_VAL 1
#define ADC_RESERVED_MODE_VAL 2
#define ADC_INTERNAL_REF_MODE_VAL 3




/*
 * Typedef description:
 * Type Defining ADC_ReferenceVolatge as enumeration
 * to allow for choosing between different modes of reference voltages easily
 */
typedef enum
{
	ADC_AREF_MODE = 0,ADC_AVCC_MODE, ADC_RESERVED_MODE ,ADC_INTERNAL_REF_MODE
}ADC_ReferenceVolatge;

/*
 * Typedef description:
 * Type Defining ADC_Prescaler as enumeration
 * to allow for choosing between different pre-scalers
 * each member corresponds to the config value in the ADCSRA register ADPS[2:0]
 */
typedef enum
{
	FCPU0 = 0,FCPU2,FCPU4,FCPU8,FCPU16,FCPU32,FCPU64,FCPU128
}ADC_Prescaler;


typedef struct{
	ADC_ReferenceVolatge ref_volt;
	ADC_Prescaler prescaler;
}ADC_ConfigType;

/*
 * Description:
 * init function for the adc
 */
void ADC_init(const ADC_ConfigType * Config_Ptr);

/*
 * Description:
 * function to read from specific channel and
 */
uint16 ADC_readChannel(uint8 channel);


#endif /* SRC_ADC_H_ */
