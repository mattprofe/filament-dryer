/**
* @file filament_dryer_system.cpp
* @brief Implementación de las funciones para el manejo de de la secadora de filamento.
* @author Matias Leonardo Baez
* @date 2024
* @contact elmattprofe@gmail.com
*/
//=====[Libraries]====================================================
#include "filament_dryer_system.h"
#include "modules/rtc/rtc.h"
#include "modules/heater_manager/heater_manager.h"
#include "modules/keypad_manager/keypad_manager.h"
#include "modules/indicator_manager/indicator_manager.h"
#include "modules/uart_manager/uart_manager.h"

//=====[Declaration of private defines]===============================

//=====[Declaration of private data types]============================

//=====[Declaration and initialization of public global objects]======

//=====[Declaration of external public global variables]==============

//=====[Declaration and initialization of public global variables]====

//=====[Declaration and initialization of private global variables]===
static systemState_t system_mode; /**< Modo de trabajo del sistema */

static adjustState_t adjust_mode; /**< Para cambiar entre tiempo y temperatura */

static int activity_time; /**< Horas especificadas para trabajar */
static int work_temperature; /**< Temperatura especificada de trabajo */

//=====[Declaration (prototypes) of private functions]================
/**
* @brief Se encendio el sistema.
*
* Al encender queda en estado de espera de comandos
* 
*/
static void systemOn();

/**
 * @brief Detiene el sistema de secado.
 * 
 * Esta función se encarga de detener el funcionamiento del sistema de secado,
 * asegurando que todos los componentes relacionados se apaguen o se pongan en un
 * estado seguro.
 */
static void systemStop();

/**
 * @brief Activa el sistema de secado.
 * 
 * Esta función se encarga de monitorear el proceso de secado y finalizarlo al completarse el tiempo de trabajo.
 */
static void systemWorking();

/**
 * @brief Finaliza el proceso de secado.
 * 
 * Esta función se encarga mantener el sistema en el estado de fin de secado
 */
static void systemEndWorking();

/**
 * @brief Administra lo que sucede mientras se aguardan comandos.
 * 
 * Luego de finalizar el secado "aguarda" a recibir comandos
 */
static void systemEndWorkingAwait();


//=====[Implementations of public functions]==========================
/**
 * @brief Inicializa el sistema de secado de filamento.
 * 
 * Configura los pines y el estado inicial del sistema.
 */
void filamentDryerInit(){

    rtcInit();

    heaterManagerInit(PIN_HEATER, PIN_AMBIENT_SENSOR);

    keypadManagerInit(PIN_BUTTON_RUN, PIN_BUTTON_MODE, PIN_BUTTON_DOWN, PIN_BUTTON_UP);
    
    indicatorManagerInit(PIN_ACTIVITY_LED, PIN_RUN_LED, PIN_BUZZER);

    uartManagerInit(USBTX, USBRX, 115200);
    
    systemOn();
}

/**
 * @brief Actualiza el estado del sistema de secado.
 * 
 * Debe ser llamada periódicamente para manejar el estado del sistema.
 */
void filamentDryerUpdate(){

    keypadManagerUpdate( &system_mode , &activity_time, &work_temperature);

    indicatorManagerUpdate(system_mode); //estado de los leds y buzzer

    uartManagerUpdate(system_mode, adjust_mode, activity_time);

    switch (system_mode)
    {
        case SYSTEM_ON:
        case SYSTEM_STOP:
            systemStop();
        break;

        case SYSTEM_WORK:
            systemWorking();
        break;
        
        case SYSTEM_FINISH:
            systemEndWorking();            
        break;
        
        case SYSTEM_FINISH_AWAIT:
            systemEndWorkingAwait();
        break;

        default:
        break;
    }

    heaterManagerUpdate(system_mode, work_temperature);

    rtcUpdate(); // actualiza el estado del reloj

}

//=====[Implementations of private functions]=========================
/**
* @brief Se encendio el sistema.
*
* Al encender queda en estado de espera de comandos
* 
*/
static void systemOn(){
    system_mode = SYSTEM_ON;
}

/**
 * @brief Detiene el sistema de secado.
 * 
 * Esta función se encarga de detener el funcionamiento del sistema de secado,
 * asegurando que todos los componentes relacionados se apaguen o se pongan en un
 * estado seguro.
 */
static void systemStop(){

    system_mode = SYSTEM_STOP; // trabajando no

    activity_time = MIN_TIME; // tiempo minimo de secado
    work_temperature = MIN_TEMP; // temperatura minima de secado

    adjust_mode = TIME;
    
    rtcRestart();
}

/**
 * @brief Activa el sistema de secado.
 * 
 * Esta función se encarga de monitorear el proceso de secado y finalizarlo al completarse el tiempo de trabajo.
 */
static void systemWorking(){

    static int previous_second = 0;

    rtcTime_t realTime = rtcRead();

    // se alcanzo el tiempo de secado?
    if(realTime.hours >= activity_time){

        system_mode = SYSTEM_FINISH;

        rtcRestart(); // lleva el contador de tiempo a 0
    }

}

/**
 * @brief Finaliza el proceso de secado.
 * 
 * Esta función se encarga mantener el sistema en el estado de fin de secado
 */
static void systemEndWorking(){

    adjust_mode = TIME;
    system_mode = SYSTEM_FINISH_AWAIT;

}

/**
 * @brief Administra lo que sucede mientras se aguardan comandos.
 * 
 * Luego de finalizar el secado "aguarda" a recibir comandos
 */
static void systemEndWorkingAwait(){
    rtcRestart();
}