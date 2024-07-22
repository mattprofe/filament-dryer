/**
* @file temperature_sensor.h
* @brief Declaraciones de funciones para el manejo del sensor de temperatura.
* @author Matias Leonardo Baez
* @date 2024
* @contact elmattprofe@gmail.com
*/
//=====[#include guards - begin]========================================

#ifndef _TEMPERATURE_SENSOR_H_
#define _TEMPERATURE_SENSOR_H_

#include "mbed.h"

//=====[Declaration of private defines]=================================

//=====[Declaration of private data types]==============================

//=====[Declaration (prototypes) of public functions]===================

/**
 * @brief Inicializa el sensor de temperatura
 *
 */
void temperatureSensorInit(PinName heaterSensorPin);

/**
 * @brief Retorna la temperatura del sensor en grados
 *
 */
int temperatureSensorReadCelsius();

/**
 * @brief Lee la temperatura del sensor de temperatura
 *
 */
void temperatureSensorUpdate();

//=====[#include guards - end]==========================================
#endif