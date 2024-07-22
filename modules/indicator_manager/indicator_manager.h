/**
* @file indicator_manager.h
* @brief Declaraciones de funciones para el manejo de los indicadores LED y Buzzer del sistema dependiendo del modo de trabajo.
* @author Matias Leonardo Baez
* @date 2024
* @contact elmattprofe@gmail.com
*/
//=====[#include guards - begin]========================================
#ifndef _INDICATOR_MANAGER_H_
#define _INDICATOR_MANAGER_H_

#include "mbed.h"
#include "modules/led/led.h"
#include "modules/buzzer/buzzer.h"
#include "modules/filament_dryer_system/filament_dryer_system.h"

//=====[Declaration of private defines]=================================

//=====[Declaration of private data types]==============================

//=====[Declaration (prototypes) of public functions]===================
/**
 * @brief Inicializa los indicadores LED y el Buzzer
 * 
 * @param runLedPin Pin del LED de encendido.
 * @param activityLedPin Pin del LED de actividad.
 * @param buzzerPin Pin del Buzzer fin de secado
 * @param beepEverySeconds Segundos de demora para emitir el pitido de fin de secado
 */
void indicatorManagerInit(PinName activityLedPin, PinName runLedPin, PinName buzzerPin);

/**
 * @brief Actualiza el estado de los indicadores LED y Buzzer basado en el estado del sistema.
 * 
 * @param state Estado actual del sistema.
 */
void indicatorManagerUpdate(systemState_t state);

//=====[#include guards - end]==========================================
#endif