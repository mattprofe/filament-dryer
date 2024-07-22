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
void ledsInit( PinName activityLedPin, PinName runLedPin );

void ledsRun();
void ledsWorking();
void ledsStop();
void ledsEndWorking();

//=====[#include guards - end]==========================================
#endif