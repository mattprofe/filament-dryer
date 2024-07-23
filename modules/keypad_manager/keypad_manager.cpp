/**
* @file keypad_manager.cpp
* @brief Implementación de las funciones para el manejo del teclado de la secadora de filamento.
* @author Matias Leonardo Baez
* @date 2024
* @contact elmattprofe@gmail.com
*/
//=====[Libraries]======================================================
#include "keypad_manager.h"
#include "modules/keypad/keypad.h"

//=====[Declaration of private defines]=================================

//=====[Declaration of private data types]==============================

//=====[Declaration and initialization of public global objects]========

//=====[Declaration of external public global variables]================

//=====[Declaration and initialization of public global variables]======

//=====[Declaration and initialization of private global variables]=====
static adjustState_t adjust_mode; // modo temperatura o tiempo

//=====[Declaration (prototypes) of private functions]==================
/**
 * @brief Maneja los estados y ajustes del sistema.
 * 
 * Esta función maneja la lógica de control del teclado, incluyendo el cambio
 * de estados del sistema y los ajustes de tiempo y temperatura.
 * 
 * @param state Puntero al estado actual del sistema.
 * @param actity_time Puntero al tiempo de actividad (secado) en horas.
 * @param work_temperature Puntero a la temperatura de trabajo en grados Celsius.
 */
static void keypadTask(systemState_t *state, int *actity_time, int *work_temperature);

/**
 * @brief Incrementa el valor actual dentro de un límite especificado.
 * 
 * Incrementa el valor actual por un valor de incremento dado,
 * asegurándose de que no se exceda el valor límite.
 * 
 * @param actualValue Puntero al valor actual que se va a incrementar.
 * @param incrementValue Valor de incremento.
 * @param limitValue Valor límite máximo.
 */
static void adjustButtonUp(int *actualValue, const int incrementValue, const int limitValue);

/**
 * @brief Decrementa el valor actual dentro de un límite especificado.
 * 
 * Decrementa el valor actual por un valor de decremento dado,
 * asegurándose de que no se baje del valor límite.
 * 
 * @param actualValue Puntero al valor actual que se va a decrementar.
 * @param incrementValue Valor de decremento.
 * @param limitValue Valor límite mínimo.
 */
static void adjustButtonDown(int *actualValue, const int incrementValue, const int limitValue);

//=====[Implementations of public functions]============================
/**
 * @brief Inicializa el gestor del teclado con los pines especificados.
 * 
 * Esta función configura e inicializa los pines utilizados para los botones
 * del teclado, preparando el sistema para la gestión de las entradas del usuario.
 * 
 * @param runButtonPin PinName del botón de inicio/parada.
 * @param modeButtonPin PinName del botón de modo.
 * @param downButtonPin PinName del botón de decremento.
 * @param upButtonPin PinName del botón de incremento
 */
void keypadManagerInit(PinName runButtonPin, PinName modeButtonPin, PinName downButtonPin, PinName upButtonPin){
    keypadInit(runButtonPin, modeButtonPin, downButtonPin, upButtonPin);

    adjust_mode = TIME;
}


/**
 * @brief Actualiza el estado del gestor del teclado.
 * 
 * Esta función actualiza el estado del teclado y ejecuta las acciones correspondientes
 * en función de las entradas del usuario y el estado actual del sistema.
 * 
 * @param state Puntero al estado actual del sistema.
 * @param activity_time Puntero al tiempo de actividad (secado) en horas.
 * @param work_temperature Puntero a la temperatura de trabajo en grados Celsius.
 */
void keypadManagerUpdate(systemState_t *state, int *actity_time, int *work_temperature){
    keypadUpdate(); // Actualiza el estado del teclado
    // se pasan los punteros
    keypadTask( state, actity_time, work_temperature);
}

//=====[Implementations of private functions]===========================
/**
 * @brief Maneja los estados y ajustes del sistema.
 * 
 * Esta función maneja la lógica de control del teclado, incluyendo el cambio
 * de estados del sistema y los ajustes de tiempo y temperatura.
 * 
 * @param state Puntero al estado actual del sistema.
 * @param actity_time Puntero al tiempo de actividad (secado) en horas.
 * @param work_temperature Puntero a la temperatura de trabajo en grados Celsius.
 */
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

/**
 * @brief Incrementa el valor actual dentro de un límite especificado.
 * 
 * Incrementa el valor actual por un valor de incremento dado,
 * asegurándose de que no se exceda el valor límite.
 * 
 * @param actualValue Puntero al valor actual que se va a incrementar.
 * @param incrementValue Valor de incremento.
 * @param limitValue Valor límite máximo.
 */
static void adjustButtonUp(int *actualValue, const int incrementValue, const int limitValue){
    
    if(*actualValue < limitValue){
        *actualValue = *actualValue + incrementValue;
    }                
    
}

/**
 * @brief Decrementa el valor actual dentro de un límite especificado.
 * 
 * Decrementa el valor actual por un valor de decremento dado,
 * asegurándose de que no se baje del valor límite.
 * 
 * @param actualValue Puntero al valor actual que se va a decrementar.
 * @param incrementValue Valor de decremento.
 * @param limitValue Valor límite mínimo.
 */
static void adjustButtonDown(int *actualValue, const int incrementValue, const int limitValue){

    if(*actualValue > limitValue){
        *actualValue = *actualValue - incrementValue;
    }     
    
}