/**
* @file rtc.h
* @brief Declaraciones de funciones para el manejo del tiempo.
* @author Matias Leonardo Baez
* @date 2024
* @contact elmattprofe@gmail.com
*/
//=====[#include guards - begin]========================================

#ifndef _RTC_H_
#define _RTC_H_

#include "mbed.h"

//=====[Declaration of private defines]=================================

//=====[Declaration of private data types]==============================
typedef struct{
    int seconds;
    int minutes;
    int hours;
}rtcTime_t;

//=====[Declaration (prototypes) of public functions]===================
/**
 * @brief Inicia el contador de tiempo.
 * 
 * Inicializa los contadores de segundos, minutos y horas a cero,
 * y reinicia el contador de retardos.
 */
void rtcInit();

/**
 * @brief Restablece los contadores de tiempo.
 * 
 * Reinicia el contador de tiempo llamando a la función rtcInit().
 */
void rtcRestart();

/**
 * @brief Retorna el tiempo transcurrido en horas, minutos y segundos.
 * 
 * @return rtcTime_t Estructura que contiene el tiempo transcurrido.
 */
rtcTime_t rtcRead();

/**
 * @brief Lleva el control del tiempo.
 * 
 * Actualiza los contadores de tiempo cada vez que se alcanza un retraso de TIME_MS.
 * Incrementa los segundos, minutos y horas según sea necesario.
 */
void rtcUpdate();
    

//=====[#include guards - end]==========================================
#endif