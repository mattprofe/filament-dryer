/**
* @file indicator_manager.cpp
* @brief Implementación de las funciones para el manejo de los indicadores LED y Buzzer del sistema dependiendo del modo de trabajo.
* @author Matias Leonardo Baez
* @date 2024
* @contact elmattprofe@gmail.com
*/
//=====[Libraries]======================================================
#include "indicator_manager.h"

//=====[Declaration of private defines]=================================

//=====[Declaration of private data types]==============================

//=====[Declaration and initialization of public global objects]========

//=====[Declaration of external public global variables]================

//=====[Declaration and initialization of public global variables]======

//=====[Declaration and initialization of private global variables]=====

//=====[Declaration (prototypes) of private functions]==================

//=====[Implementations of public functions]============================
/**
 * @brief Inicializa los indicadores LED y el Buzzer
 * 
 * @param runLedPin Pin del LED de encendido.
 * @param activityLedPin Pin del LED de actividad.
 * @param buzzerPin Pin del Buzzer fin de secado
 * @param beepEverySeconds Segundos de demora para emitir el pitido de fin de secado
 */
void indicatorManagerInit(PinName activityLedPin, PinName runLedPin, PinName buzzerPin){
    ledsInit(activityLedPin,runLedPin); // inicia los leds del panel
    buzzerInit(buzzerPin);  // inicia el zumbador
    buzzerSetTimeBeep(BEEP_EVERY_SECONDS); // especifica cada cuantos segundos emite pitidos al terminar de secar
}

/**
 * @brief Actualiza el estado de los indicadores LED y Buzzer basado en el estado del sistema.
 * 
 * @param state Estado actual del sistema.
 */
void indicatorManagerUpdate(systemState_t state){
    switch (state){
        case SYSTEM_ON:
            ledsRun();
        break;

        case SYSTEM_STOP:    /**< Estado de sistema detenido */
            ledsStop(); // led de actividad apagado
            buzzerOff(); // zumbador apagado
        break;

        case SYSTEM_WORK:    /**< Estado de sistema secando */
            ledsWorking();
            buzzerOff();
        break;
        
        case SYSTEM_FINISH:   /**< Estado de sistema secado finalizado */
            ledsEndWorking();
        break;

        case SYSTEM_FINISH_AWAIT:
            buzzerUpdate(); // Emite los pitidos si corresponde
        break;

        default:
        break;
    }
}

//=====[Implementations of private functions]===========================