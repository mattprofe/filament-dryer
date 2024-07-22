/**
* @file keypad_manager.cpp
* @brief Implementación de las funciones para el manejo del teclado de la secadora de filamento.
* @author Matias Leonardo Baez
* @date 2024
* @contact elmattprofe@gmail.com
*/
//=====[Libraries]======================================================
#include "keypad_manager.h"

//=====[Declaration of private defines]=================================

//=====[Declaration of private data types]==============================

//=====[Declaration and initialization of public global objects]========

//=====[Declaration of external public global variables]================

//=====[Declaration and initialization of public global variables]======

//=====[Declaration and initialization of private global variables]=====
static adjustState_t adjust_mode; // modo temperatura o tiempo

//=====[Declaration (prototypes) of private functions]==================
static void keypadTask(systemState_t *state, int *actity_time, int *work_temperature);
static void adjustButtonUp(int *actualValue, const int incrementValue, const int limitValue);
static void adjustButtonDown(int *actualValue, const int incrementValue, const int limitValue);

//=====[Implementations of public functions]============================
void keypadManagerInit(PinName runButtonPin, PinName modeButtonPin, PinName downButtonPin, PinName upButtonPin){
    keypadInit(runButtonPin, modeButtonPin, downButtonPin, upButtonPin);

    adjust_mode = TIME;
}

// se espera recibir punteros
void keypadManagerUpdate(systemState_t *state, int *actity_time, int *work_temperature){
    keypadUpdate(); // Actualiza el estado del teclado
    // se pasan los punteros
    keypadTask( state, actity_time, work_temperature);
}

//=====[Implementations of private functions]===========================
static void keypadTask(systemState_t *state, int *activity_time, int *work_temperature){
    // estado de botones
    static buttonTemplate_t past_button = NONE;
    buttonTemplate_t user_button = keypadReadButton();

    // si no se mantiene presionado el botón
    if(user_button != past_button){
        past_button = user_button;

        switch(user_button){
            case RUN_STOP: // presiono arranque/parada

                switch (*state){
                    case SYSTEM_ON:
                    break;

                    case SYSTEM_FINISH:
                    break;

                    case SYSTEM_WORK: // Esta secando
                        *state = SYSTEM_STOP;
                        
                    break;
                    
                    case SYSTEM_FINISH_AWAIT: // Termino de secar y esta a la espera de reiniciar el secado
                    case SYSTEM_STOP: // Se detuvo el secado
                        *state = SYSTEM_WORK;
                        
                    break;

                    default:
                    break;
                }
            break;

            case MODE: // cambio de modo

                switch (adjust_mode){
                    case TEMPERATURE:
                        // estaba en modo temperatura cambia a tiempo
                        adjust_mode = TIME;
                        
                    break;

                    case TIME:
                        // estaba en modo de tiempo cambia a temperatura
                        adjust_mode = TEMPERATURE; 
                        
                    break;
                }
            break;

            case PLUS: // aumenta temperatura o tiempo
                switch (adjust_mode){
                    case TEMPERATURE:   
                        adjustButtonUp(work_temperature, INCREMENT_TEMP, MAX_TEMP);
                    break;

                    case TIME:
                        adjustButtonUp(activity_time, INCREMENT_TIME, MAX_TIME);
                    break; 
                }

            break;

            case LESS: // disminuye temperatura o tiempo

                switch (adjust_mode){
                    case TEMPERATURE:   
                        adjustButtonDown(work_temperature, INCREMENT_TEMP, MIN_TEMP);
                    break;

                    case TIME:
                        adjustButtonDown(activity_time, INCREMENT_TIME, MIN_TIME);
                    break; 
                }
            
            break;

            case NONE:
                past_button = NONE;
            break;
        
        }
    }

}

static void adjustButtonUp(int *actualValue, const int incrementValue, const int limitValue){
    
    if(*actualValue < limitValue){
        *actualValue = *actualValue + incrementValue;
    }                
    
}

static void adjustButtonDown(int *actualValue, const int incrementValue, const int limitValue){

    if(*actualValue > limitValue){
        *actualValue = *actualValue - incrementValue;
    }     
    
}