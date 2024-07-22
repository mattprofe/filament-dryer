/**
* @file buzzer.h
* @brief Declaraciones de funciones para el manejo del buzzer.
* @author Matias Leonardo Baez
* @date 2024
* @contact elmattprofe@gmail.com
*/
//=====[#include guards - begin]========================================
#ifndef _BUZZER_H_
#define _BUZZER_H_

#include "mbed.h"

//=====[Declaration of private defines]=================================

//=====[Declaration of private data types]==============================

//=====[Declaration (prototypes) of public functions]===================
/**
 * @brief Inicializa el buzzer.
 * 
 * Configura el pin del buzzer y establece su estado inicial en apagado.
 * 
 * @param buzzerPin Pin que controla el buzzer.
 */
void buzzerInit(PinName buzzerPin);

/**
 * @brief Activa el buzzer.
 * 
 * Configura el buzzer para que esté encendido.
 */
void buzzerOn();

/**
 * @brief Desactiva el buzzer.
 * 
 * Configura el buzzer para que esté apagado.
 */
void buzzerOff();

/**
 * @brief Obtiene el estado actual del buzzer.
 * 
 * @return El estado actual del buzzer, donde 1 significa encendido y 0 apagado.
 */
int buzzerStatus();

/**
 * @brief Obtiene el tiempo configurado para el beep del buzzer.
 * 
 * @return Tiempo en segundos para que el buzzer emita sonido.
 */
int buzzerGetTimeBeep();

/**
 * @brief Configura el tiempo para el beep del buzzer.
 * 
 * @param seconds Tiempo en segundos para el beep del buzzer.
 */
void buzzerSetTimeBeep(int seconds);

/**
 * @brief Actualiza el estado del buzzer basándose en el tiempo configurado.
 * 
 * Controla el encendido y apagado del buzzer de acuerdo con el tiempo configurado y el tiempo transcurrido.
 */
void buzzerUpdate();

//=====[#include guards - end]==========================================
#endif