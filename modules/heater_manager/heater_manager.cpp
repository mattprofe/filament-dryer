/**
* @file heater_manager.cpp
* @brief Implementación de las funciones para el manejo del calentador en base al modo de trabajo y temperatura.
* @author Matias Leonardo Baez
* @date 2024
* @contact elmattprofe@gmail.com
*/
//=====[Libraries]======================================================
#include "heater_manager.h"
#include "modules/heater/heater.h"
#include "modules/temperature_sensor/temperature_sensor.h"

//=====[Declaration of private defines]=================================

//=====[Declaration of private data types]==============================

//=====[Declaration and initialization of public global objects]========

//=====[Declaration of external public global variables]================

//=====[Declaration and initialization of public global variables]======

//=====[Declaration and initialization of private global variables]=====

//=====[Declaration (prototypes) of private functions]==================

//=====[Implementations of public functions]============================
/**
* @brief Inicializa el calentador y el sensor de temperatura
*
* Configura el pin del calentador y el del sensor de temperatura
*
* @param heaterPin pin para el calentador
* @param heaterSensor pin para el sensor de temperatura (analog)
*/
void heaterManagerInit(PinName heaterPin, PinName heaterSensorPin){
    temperatureSensorInit(heaterSensorPin);
    heaterInit(heaterPin);
}

/**
* @brief Gestiona el funcionamiento del calentador
*
* Gestiona el encendido/apagado del calentador dependiendo del modo de trabajo y temperatura de trabajo
*
* @param state modo de trabajo
* @param work_temperature temperatura a la cual debe mantener el calentador
*/
void heaterManagerUpdate(systemState_t state, const int work_temperature){

    temperatureSensorUpdate(); // actualiza el estado del sensor de temperatura

    switch (state){
        case SYSTEM_ON:
            heaterSetTemperature(MIN_TEMP);
        break;

        case SYSTEM_WORK:
            heaterSetTemperature(work_temperature);
            heaterUpdate(temperatureSensorReadCelsius());
        break;

        case SYSTEM_STOP:
        case SYSTEM_FINISH:
        case SYSTEM_FINISH_AWAIT:
            heaterOff();
        break;

        default:
        break;
    }    
}

//=====[Implementations of private functions]===========================