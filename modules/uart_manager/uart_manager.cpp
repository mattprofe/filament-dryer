/**
* @file uart_manager.cpp
* @brief Implementación de las funciones para el manejo de alertar por UART.
* @author Matias Leonardo Baez
* @date 2024
* @contact elmattprofe@gmail.com
*/
//=====[Libraries]======================================================
#include "uart_manager.h"
#include "modules/rtc/rtc.h"
#include "modules/heater/heater.h"
#include "modules/temperature_sensor/temperature_sensor.h"

//=====[Declaration of private defines]=================================

//=====[Declaration of private data types]==============================

//=====[Declaration and initialization of public global objects]========
UnbufferedSerial* uart; /** Objeto asociado al convertidor serial USB */

//=====[Declaration of external public global variables]================

//=====[Declaration and initialization of public global variables]======

//=====[Declaration and initialization of private global variables]=====

//=====[Declaration (prototypes) of private functions]==================

//=====[Implementations of public functions]============================
/**
 * @brief Inicializa la comunicación UART.
 * 
 * Configura los pines y la velocidad de la comunicación UART.
 * 
 * @param rxPin El pin de recepción UART.
 * @param txPin El pin de transmisión UART.
 * @param bauds La velocidad de baudios para la comunicación UART.
 */
void uartManagerInit(PinName rxPin, PinName txPin, const int bauds){
    uart = new UnbufferedSerial(rxPin, txPin, bauds);
}

/**
 * @brief Informa el estado del sistema a través de UART.
 * 
 * Envía el estado actual del sistema, el modo de ajuste, y el tiempo de actividad 
 * a través de la comunicación UART.
 * 
 * @param state El estado actual del sistema.
 * @param mode El modo de ajuste actual (temperatura o tiempo).
 * @param activity_time El tiempo de actividad configurado para el sistema.
 */
void uartManagerUpdate(systemState_t state, adjustState_t mode, const int activity_time){

    static int previous_second = 0;
    static systemState_t previous_state = SYSTEM_STOP;
    static adjustState_t previous_mode = TIME;

    rtcTime_t realTime = rtcRead();

    switch (state){
        case SYSTEM_ON:
            printf("*** Secadora de filamento encendida!.\n");
        break;

        case SYSTEM_STOP:    /**< Estado de sistema detenido */
            if(previous_state == SYSTEM_WORK){
                previous_state = SYSTEM_STOP;

                printf("-> Secado detenido por el usuario, presione run para volver a secar\n");
            }

        break;

        case SYSTEM_WORK:    /**< Estado de sistema secando */
            
            if(previous_state == SYSTEM_STOP or previous_state == SYSTEM_FINISH){
                previous_state = SYSTEM_WORK;

                printf("-> Secado iniciado\n");
            }

            // si hubo cambio de modo
            if(previous_mode != mode){

                previous_mode = mode;

                switch (mode){
                    case TIME:
                        printf("-> Modo Tiempo\n");
                    break;
                    case TEMPERATURE:
                        printf("-> Modo Temperatura\n");
                    break;
                }
                
            }

            // si paso 1 segundo
            if(previous_second != realTime.seconds){
                previous_second = realTime.seconds;

                // informa el estado de la maquina
                printf("temperature_now: %d temperature_user: %d hour: %d  minutes: %d seconds: %d hour_user: %d heater: %d\n", temperatureSensorReadCelsius(), heaterGetTemperatureWork(), realTime.hours, realTime.minutes, realTime.seconds, activity_time, heaterStatus() );
            }
        break;

        case SYSTEM_FINISH:   /**< Estado de sistema secado finalizado */
            previous_state = SYSTEM_FINISH;
            printf("-> Secado finalizado, para volver a secar presione un boton\n");
        break;

        case SYSTEM_FINISH_AWAIT:
        break;

        default:
        break;
    }
}
//=====[Implementations of private functions]===========================