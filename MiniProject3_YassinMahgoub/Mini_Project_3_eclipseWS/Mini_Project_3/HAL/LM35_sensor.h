/*
 * LM35_sensor.h
 *
 *  Created on: Oct 13, 2023
 *      Author: Yassin Mahgoub
 *      Description: LM35 Temp sensor header file
 */

#ifndef SRC_LM35_SENSOR_H_
#define SRC_LM35_SENSOR_H_

/*
 * Max volt sensor can generate is 1.5v
 * Max temperature sensor can read is 150v
 * sensor is connected to the adc channel 2
 */
#define LM35_MAX_VOLT 1.5
#define LM35_MAX_TEMP 150
#define LM35_CHANNEL_NUM 2

uint8 LM35_getTemperature(void);

#endif /* SRC_LM35_SENSOR_H_ */
