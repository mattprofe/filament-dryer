/**
* @file led.h
* @brief Declaraciones de funciones para el manejo de leds de la secadora de filamento.
* @author Matias Leonardo Baez
* @date 2024
* @contact elmattprofe@gmail.com
*/
//=====[#include guards - begin]========================================
#ifndef _LED_H_
#define _LED_H_

#include "mbed.h"

//=====[Declaration of private defines]=================================

//=====[Declaration of private data types]==============================

//=====[Declaration (prototypes) of public functions]===================
/**
 * @brief Inicializa los LEDs con los pines especificados.
 * 
 * Configura e inicializa los pines utilizados para los LEDs de actividad
 * y encendido.
 * 
 * @param activityLedPin PinName del LED de actividad.
 * @param runLedPin PinName del LED de encendido.
 */
void ledsInit( PinName activityLedPin, PinName runLedPin );

/**
 * @brief Secuencia de LEDs que indican sistema encendido.
 * 
 * Enciende LEDs para indicar que el sistema está encendido.
 */
void ledsRun();

/**
 * @brief Secuencia de LEDs que indican sistema trabajando.
 * 
 * Enciende LEDs para indicar que el sistema está trabajando.
 */
void ledsWorking();

/**
 * @brief Secuencia de LEDs que indican sistema detenido.
 * 
 * Enciende LEDs para indicar que el sistema esta detenido.
 */
void ledsStop();

/**
 * @brief Secuencia de LEDs que indican sistema termino de trabajar.
 * 
 * Enciende LEDs para indicar que el sistema termino de trabajar.
 */
void ledsEndWorking();

//=====[#include guards - end]==========================================
#endif