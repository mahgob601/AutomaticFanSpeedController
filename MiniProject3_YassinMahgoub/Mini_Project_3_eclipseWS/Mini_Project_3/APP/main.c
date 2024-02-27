
/*
 * main.c
 *
 *  Created on: Oct 13, 2023
 *      Author: Yassin
 *      Description: APP layer source file to control our app
 */
#include "../MCAL/adc.h"
#include "../HAL/LCD.h"
#include "../HAL/lm35_sensor.h"
#include "../std_types.h"
#include <util/delay.h>
#include "../HAL/DCMOTOR.h"

int main(void)
{
	uint8 temp;

	// creating a struct instance to be passed by ref to ADC_init()
	ADC_ConfigType ADC1;
	ADC1.prescaler = FCPU8;
	ADC1.ref_volt = ADC_INTERNAL_REF_MODE;
	ADC_init(&ADC1);

	//LCD initialization
	LCD_init();

	//dc motor initialization
	DcMotor_Init();

	// initial state is off (enum member value = 0)
	DcMotor_State dcState = OFF;
	uint8 dcSpeed = 0;



	LCD_displayStringRowColumn(0,3,"FAN IS ");
	LCD_displayStringRowColumn(1,3,"Temp =     C");


	while(1)
	{

		temp = LM35_getTemperature();

		if(temp >= 100)
		{
			// duty cycle 75% case (0.75 of motor speed)
			if(temp >= 100 && temp < 120)
			{
				dcState = CW;
				dcSpeed = 75;
			}
			// duty cycle 50% case
			else{
				dcState = CW;
				dcSpeed = 100;
			}
			LCD_moveCursor(0,10);
			if(dcState == CW)
			{
				LCD_displayString("ON ");
			}
			else
			{
				LCD_displayString("OFF");

			}
			LCD_moveCursor(1,10);
			//Display the temperature value every time at same position
			LCD_integerToString(temp);
		}
		else
		{
			// duty cycle 0% case
			if(temp < 30)
			{
				dcState = OFF;
				dcSpeed = 0;
			}
			// duty cycle 25% case
			else if (temp >= 30 && temp < 60)
			{
				dcState = CW;
				dcSpeed = 25;

			}
			else if (temp>=60 && temp<90)
			{
				dcState = CW;
				dcSpeed = 50;
			}
			else if (temp >= 90 && temp < 100)
			{
				dcState = CW;
				dcSpeed = 75;
			}

			LCD_moveCursor(0,10);
			if(dcState == CW)
			{

				LCD_displayString("ON ");
			}
			else
			{
				LCD_displayString("OFF");

			}
			LCD_moveCursor(1,10);
			LCD_integerToString(temp);
			 //In case the digital value is two or one digits print space in the next digit place
			LCD_displayCharacter('  ');
		}
		DcMotor_Rotate(dcState,dcSpeed);
		// delay applied in order to allow motor spin
		_delay_ms(60);
	}

}
