/**
* @file filament_dryer_system.h
* @brief Declaraciones de funciones para el manejo de la secadora de filamento.
* @author Matias Leonardo Baez
* @date 2024
* @contact elmattprofe@gmail.com
*/
//=====[#include guards - begin]========================================
#ifndef _FILAMENT_DRYER_SYSTEM_H_
#define _FILAMENT_DRYER_SYSTEM_H_

//=====[Declaration of private defines]=================================
/** Pin para el LED de actividad */
#define PIN_ACTIVITY_LED    PA_15
/** Pin para el LED de funcionamiento */
#define PIN_RUN_LED PC_12
/** Pin para el calentador */
#define PIN_HEATER  PC_10
/** Pin para el sensor de ambiente */
#define PIN_AMBIENT_SENSOR  PC_4
/** Pin para el buzzer */
#define PIN_BUZZER  PD_2
/** Pin para el botón de incremento */
#define PIN_BUTTON_UP   PA_13
/** Pin para el botón de decremento */
#define PIN_BUTTON_DOWN PA_14
/** Pin para el botón de modo */
#define PIN_BUTTON_MODE PB_2
/** Pin para el botón de arranque/parada */
#define PIN_BUTTON_RUN  PC_8

#define ON  1   /**< Valor que se usa para encender leds/calentador */
#define OFF !ON /**< Valor que se usa para apagar leds/calentador */

#define MAX_TEMP    90 /**< Temperatura máxima en grados que se puede seleccionar */
#define MIN_TEMP    30 /**< Temperatura minima en grados que se puede seleccionar */
#define INCREMENT_TEMP  5 /**< Incremento de grados de secado al presionar botones */

#define MAX_TIME    24 /**< Cantidad máxima de horas que se puede seleccionar */
#define MIN_TIME    1 /**< Cantidad mínima de horas que se puede seleccionar */
#define INCREMENT_TIME  1 /**< Incremento de horas de secado al presionar botones */

#define BEEP_EVERY_SECONDS  10 /**< Segundos para emitir un pitido al finalizar el secado */

//=====[Declaration of private data types]==============================

/**
 * @brief Estados posibles del sistema de secado.
 */
typedef enum{
    SYSTEM_ON,  /**< Se encendio la máquina */
    SYSTEM_STOP,    /**< Estado de sistema detenido */
    SYSTEM_WORK,    /**< Estado de sistema secando */
    SYSTEM_FINISH,  /**< Estado de sistema secado finalizado */
    SYSTEM_FINISH_AWAIT /**< Secado Finalizado espera de comandos*/
}systemState_t;

/**
 * @brief Modos de ajuste del botón "mode" los botones.
 */
typedef enum{
    TEMPERATURE,    /**< Modo de trabajo de los botones para setear temperatura de secado */
    TIME            /**< Modo de trabajo de los botones para setear tiempo de secado */
}adjustState_t;
//=====[Declaration (prototypes) of public functions]===================

/**
 * @brief Inicializa el sistema de secado de filamento.
 * 
 * Configura los pines y el estado inicial del sistema.
 */
void filamentDryerInit();

/**
 * @brief Actualiza el estado del sistema de secado.
 * 
 * Debe ser llamada periódicamente para manejar el estado del sistema.
 */
void filamentDryerUpdate();

/**
 * @brief Función de prueba para el teclado.
 * 
 * Permite realizar pruebas manuales del teclado informa por uart si se presiona un botón.
 */
void filamentDryerTestingKeyPad();

/**
 * @brief Función de prueba manual para el buzzer.
 * 
 * Permite realizar pruebas manuales del buzzer al presionar el botón run/stop.
 */
void filamentDryerTestingBuzzerManual();

/**
 * @brief Función de prueba automática para el buzzer.
 * 
 * Permite realizar pruebas automáticas del buzzer al emitir pitidos transcurridos los BEEP_EVERY_SECONDS.
 */
void filamentDryerTestingBuzzerAutomatic();

/**
 * @brief Función de prueba manual para el calentador.
 * 
 * Permite realizar pruebas manuales del calentador utilizando el botón run/stop con protección por sobrecalentamiento, informa por uart temperatura y estado del calentador.
 */
void filamentDryerTestingHeaterManual();

/**
 * @brief Función de prueba automática para el calentador.
 * 
 * Permite realizar pruebas automáticas del calentador seteandolo a 60°C cada 1 segundo informa la temperatura por uart.
 */
void filamentDryerTestingHeaterAutomatic();

//=====[#include guards - end]==========================================
#endif