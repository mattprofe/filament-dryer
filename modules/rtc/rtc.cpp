/**
* @file rtc.cpp
* @brief Implementación de las funciones para el manejo del tiempo.
* @author Matias Leonardo Baez
* @date 2024
* @contact elmattprofe@gmail.com
*/
//=====[Libraries]======================================================
#include "mbed.h"
#include "rtc.h"

//=====[Declaration of private defines]=================================
// Si no esta declarado TIME_MS 
#ifndef TIME_MS
#define TIME_MS 10
#endif

#define delay(ms)   thread_sleep_for( ms ) /**< Pseudonimo delay para thread_sleep_fo */

//=====[Declaration of private data types]==============================

//=====[Declaration and initialization of public global objects]========

//=====[Declaration of external public global variables]================

//=====[Declaration and initialization of public global variables]======

//=====[Declaration and initialization of private global variables]=====
static rtcTime_t time_module;
static int delay_count = 0;    /**< Lleva el conteo de la cantidad de retardos */

//=====[Declaration (prototypes) of private functions]==================

//=====[Implementations of public functions]============================
void rtcInit(){
    time_module.seconds = 0;
    time_module.minutes = 0;
    time_module.hours = 0;
    delay_count = 0;
}

void rtcRestart(){
    rtcInit();
}

rtcTime_t rtcRead(){
    return time_module;
}

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