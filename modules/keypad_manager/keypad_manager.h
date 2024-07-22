/**
* @file keypad_manager.h
* @brief Declaraciones de funciones para el manejo del teclado de la secadora de filamento.
* @author Matias Leonardo Baez
* @date 2024
* @contact elmattprofe@gmail.com
*/
//=====[#include guards - begin]========================================
#ifndef _KEYPAD_MANAGER_H_
#define _KEYPAD_MANAGER_H_

#include "mbed.h"
#include "modules/keypad/keypad.h"
#include "modules/filament_dryer_system/filament_dryer_system.h"

//=====[Declaration of private defines]=================================

//=====[Declaration of private data types]==============================

//=====[Declaration (prototypes) of public functions]===================
void keypadManagerInit(PinName runButtonPin, PinName modeButtonPin, PinName downButtonPin, PinName upButtonPin);
void keypadManagerUpdate(systemState_t *state, int *activity_time, int *work_temperature);

//=====[#include guards - end]==========================================
#endif