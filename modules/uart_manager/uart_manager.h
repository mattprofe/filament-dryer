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
/**
 * @brief Inicializa la comunicación UART.
 * 
 * Configura los pines y la velocidad de la comunicación UART.
 * 
 * @param rxPin El pin de recepción UART.
 * @param txPin El pin de transmisión UART.
 * @param bauds La velocidad de baudios para la comunicación UART.
 */
void uartManagerInit(PinName rxPin, PinName txPin, const int bauds);

/**
 * @brief Informa el estado del sistema a través de UART.
 * 
 * Envía el estado actual del sistema, el modo de ajuste, y el tiempo de actividad 
 * a través de la comunicación UART.
 * 
 * @param state El estado actual del sistema.
 * @param mode El modo de ajuste actual (temperatura o tiempo).
 * @param activity_time El tiempo de actividad configurado para el sistema.
 */
void uartManagerUpdate(systemState_t state, adjustState_t mode, const int activity_time);

//=====[#include guards - end]==========================================
#endif