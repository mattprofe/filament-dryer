/**
* @file uart_manager.h
* @brief Declaraciones de funciones para el manejo de XXXXX.
* @author Matias Leonardo Baez
* @date 2024
* @contact elmattprofe@gmail.com
*/
//=====[#include guards - begin]========================================

#ifndef _UART_MANAGER_H_
#define _UART_MANAGER_H_

#include "mbed.h"
#include "modules/filament_dryer_system/filament_dryer_system.h"

//=====[Declaration of private defines]=================================

//=====[Declaration of private data types]==============================

//=====[Declaration (prototypes) of public functions]===================
void uartManagerInit(PinName rxPin, PinName txPin, const int bauds);
void uartManagerUpdate(systemState_t state, adjustState_t mode, const int activity_time);

//=====[#include guards - end]==========================================
#endif