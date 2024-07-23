/**
* @file rtc.cpp
* @brief Implementación de las funciones para el manejo del tiempo.
* @author Matias Leonardo Baez
* @date 2024
* @contact elmattprofe@gmail.com
*/
//=====[Libraries]======================================================

#include "rtc.h"

//=====[Declaration of private defines]=================================
// Si no esta declarado TIME_MS 
#ifndef TIME_MS
#define TIME_MS 10
#endif

#define delay(ms)   thread_sleep_for( ms ) /**< Pseudonimo delay para thread_sleep_for */

//=====[Declaration of private data types]==============================

//=====[Declaration and initialization of public global objects]========

//=====[Declaration of external public global variables]================

//=====[Declaration and initialization of public global variables]======

//=====[Declaration and initialization of private global variables]=====
static rtcTime_t time_module;   /**< Estructura para almacenar el tiempo. */
static int delay_count = 0;    /**< Lleva el conteo de la cantidad de retardos */

//=====[Declaration (prototypes) of private functions]==================

//=====[Implementations of public functions]============================
/**
 * @brief Inicia el contador de tiempo.
 * 
 * Inicializa los contadores de segundos, minutos y horas a cero,
 * y reinicia el contador de retardos.
 */
void rtcInit(){
    time_module.seconds = 0;
    time_module.minutes = 0;
    time_module.hours = 0;
    delay_count = 0;
}

/**
 * @brief Restablece los contadores de tiempo.
 * 
 * Reinicia el contador de tiempo llamando a la función rtcInit().
 */
void rtcRestart(){
    rtcInit();
}

/**
 * @brief Retorna el tiempo transcurrido en horas, minutos y segundos.
 * 
 * @return rtcTime_t Estructura que contiene el tiempo transcurrido.
 */
rtcTime_t rtcRead(){
    return time_module;
}

/**
 * @brief Lleva el control del tiempo.
 * 
 * Actualiza los contadores de tiempo cada vez que se alcanza un retraso de TIME_MS.
 * Incrementa los segundos, minutos y horas según sea necesario.
 */
void rtcUpdate(){
    
    delay(TIME_MS);

    delay_count = delay_count + 1;

    // si se alcanzo 100 retardos de 10 ms paso 1 segundo
    if(delay_count >= 100){
        delay_count = 0;

        if(time_module.seconds<60){
            time_module.seconds = time_module.seconds + 1;
        }else{
            time_module.seconds = 0;

            if(time_module.minutes<59){
                time_module.minutes = time_module.minutes + 1;
            }else{

                time_module.minutes = 0;
                time_module.hours = time_module.hours + 1;
            }
        }
    }
}

//=====[Implementations of private functions]===========================