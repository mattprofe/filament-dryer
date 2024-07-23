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
 * @brief Inicia el contador de tiempo
 */
void rtcInit();

/**
 * @brief Restablece los contadores de tiempo.
 */
void rtcRestart();

/**
 * @brief retorna el tiempo transcurrido hora, minutos, segundos
 */
rtcTime_t rtcRead();

/**
 * @brief Lleva el control del tiempo.
 */
void rtcUpdate();
    

//=====[#include guards - end]==========================================
#endif