/**
* @file led.cpp
* @brief Implementación de las funciones para el manejo de leds de la secadora de filamento.
* @author Matias Leonardo Baez
* @date 2024
* @contact elmattprofe@gmail.com
*/
//=====[Libraries]======================================================
#include "led.h"

//=====[Declaration of private defines]=================================
#ifndef TIME_MS
#define TIME_MS 10
#endif

#define ON   1   /**< Valor con el que el led enciende */
#define OFF  !ON  /**< Valor para apagar el led */

#define BLINK_EVERY_SECONDS 1 /**< Cada cuantos segundos parpadea el led*/

//=====[Declaration of private data types]==============================

//=====[Declaration and initialization of public global objects]========
DigitalOut* activityLed; /** Objeto para el LED de máquina en actividad o secado finalizado */
DigitalOut* runLed;   /** Objeto para el LED de máquina encendida */

//=====[Declaration of external public global variables]================

//=====[Declaration and initialization of public global variables]======

//=====[Declaration and initialization of private global variables]=====
static int elapsed_seconds = 0;
static int previous_second = 0;
static int count_seconds = 0;
static int delay_count = 0;

//=====[Declaration (prototypes) of private functions]==================
static void runLedOn();
static void runLedOff();
static void activityLedOn();
static void activityLedOff();
static void activityLedBlink(int seconds_to_blink);

//=====[Implementations of public functions]============================
void ledsInit( PinName activityLedPin, PinName runLedPin ){
    activityLed = new DigitalOut(activityLedPin);
    runLed = new DigitalOut(runLedPin);

    ledsStop();
}

void ledsRun(){
    runLedOn();
}

void ledsWorking(){
    activityLedBlink(BLINK_EVERY_SECONDS);
}

void ledsStop(){
    activityLedOff();

    elapsed_seconds = 0;
    previous_second = 0;
    count_seconds = 0;
    delay_count = 0;
}

void ledsEndWorking(){
    activityLedOn();
}

//=====[Implementations of private functions]===========================
static void runLedOn(){
    *runLed = ON;
}

static void runLedOff(){
    *runLed = OFF;
}

static void activityLedOn(){
    *activityLed = ON;
}

static void activityLedOff(){
    *activityLed = OFF;
}

static void activityLedBlink(int seconds_to_blink){
    
    delay_count = delay_count + 1;

    // si se alcanzo 100 retardos de 10 ms paso 1 segundo
    if(delay_count >= 100){
        delay_count = 0;
        
        if(elapsed_seconds<60){
            elapsed_seconds = elapsed_seconds + 1;
        }else{
            elapsed_seconds = 0;
        }
    }

    // si ya paso 1 segundo
    if(previous_second != elapsed_seconds){
        previous_second = elapsed_seconds;
        
        count_seconds = count_seconds + 1;
        
        //alcanzo los seconds_to_blink
        if(count_seconds >= seconds_to_blink){
            count_seconds = 0;
            activityLedOn(); // enciende el led de actividad
        }
    }else{ // aún no paso 1 segundo
        activityLedOff(); // apaga el led de actividad
    }
}