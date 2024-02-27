/*
 * LM35_sensor.c
 *
 *  Created on: Oct 13, 2023
 *      Author: Yassin Mahgoub
 *      Description: LM35 Temp sensor source file
 */
#include "../MCAL/adc.h"
#include "LM35_sensor.h"
#include <util/delay.h>

/*
 * receives adc global value (g_adcRefVolt)
 * performs the eqaution
 * returns the temp value
 */
uint8 LM35_getTemperature(void)
{
	uint8 temp_value = 0;
	uint16 adcValue = 0;
	adcValue = ADC_readChannel(LM35_CHANNEL_NUM);
	temp_value = (uint8)(((uint32)adcValue*LM35_MAX_TEMP*g_adcRefVolt)/(ADC_MAX_VALUE*LM35_MAX_VOLT));
	return temp_value;

}
