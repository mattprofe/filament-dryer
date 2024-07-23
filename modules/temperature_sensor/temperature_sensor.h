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
 * @brief Inicializa el sensor de temperatura.
 * 
 * Esta función configura el pin del sensor de temperatura e inicializa 
 * el valor promedio de voltaje del sensor.
 * 
 * @param heaterSensorPin Pin del sensor de temperatura.
 */
void temperatureSensorInit(PinName heaterSensorPin);

/**
 * @brief Lee la temperatura en grados Celsius.
 * 
 * Convierte el valor promedio de voltaje del sensor a grados Celsius.
 * 
 * @return int Temperatura en grados Celsius.
 */
int temperatureSensorReadCelsius();

/**
 * @brief Actualiza los valores de temperatura.
 * 
 * Lee el voltaje del sensor de temperatura, lo almacena en un 
 * arreglo y calcula el promedio de las muestras para obtener una lectura estable.
 */
void temperatureSensorUpdate();

//=====[#include guards - end]==========================================
#endif