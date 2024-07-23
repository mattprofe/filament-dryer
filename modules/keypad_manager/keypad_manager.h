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
#include "modules/filament_dryer_system/filament_dryer_system.h"

//=====[Declaration of private defines]=================================

//=====[Declaration of private data types]==============================

//=====[Declaration (prototypes) of public functions]===================
/**
 * @brief Inicializa el gestor del teclado con los pines especificados.
 * 
 * Esta función configura e inicializa los pines utilizados para los botones
 * del teclado, preparando el sistema para la gestión de las entradas del usuario.
 * 
 * @param runButtonPin PinName del botón de inicio/parada.
 * @param modeButtonPin PinName del botón de modo.
 * @param downButtonPin PinName del botón de decremento.
 * @param upButtonPin PinName del botón de incremento
 */
void keypadManagerInit(PinName runButtonPin, PinName modeButtonPin, PinName downButtonPin, PinName upButtonPin);

/**
 * @brief Actualiza el estado del gestor del teclado.
 * 
 * Esta función actualiza el estado del teclado y ejecuta las acciones correspondientes
 * en función de las entradas del usuario y el estado actual del sistema.
 * 
 * @param state Puntero al estado actual del sistema.
 * @param activity_time Puntero al tiempo de actividad (secado) en horas.
 * @param work_temperature Puntero a la temperatura de trabajo en grados Celsius.
 */
void keypadManagerUpdate(systemState_t *state, int *activity_time, int *work_temperature);

//=====[#include guards - end]==========================================
#endif