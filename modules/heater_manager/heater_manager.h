/**
* @file heater_manager.h
* @brief Declaraciones de funciones para el manejo del calentador en base al modo de trabajo y temperatura.
* @author Matias Leonardo Baez
* @date 2024
* @contact elmattprofe@gmail.com
*/
//=====[#include guards - begin]========================================
#ifndef _HEATER_MANAGER_H_
#define _HEATER_MANAGER_H_

#include "mbed.h"
#include "modules/filament_dryer_system/filament_dryer_system.h"

//=====[Declaration of private defines]=================================

//=====[Declaration of private data types]==============================

//=====[Declaration (prototypes) of public functions]===================

/**
* @brief Inicializa el calentador y el sensor de temperatura
*
* Configura el pin del calentador y el del sensor de temperatura
*
* @param heaterPin pin para el calentador
* @param heaterSensor pin para el sensor de temperatura (analog)
*/
void heaterManagerInit(PinName heaterPin, PinName heaterSensorPin);

/**
* @brief Gestiona el funcionamiento del calentador
*
* Gestiona el encendido/apagado del calentador dependiendo del modo de trabajo y temperatura de trabajo
*
* @param state modo de trabajo
* @param work_temperature temperatura a la cual debe mantener el calentador
*/
void heaterManagerUpdate(systemState_t state, const int work_temperature);

//=====[#include guards - end]==========================================
#endif