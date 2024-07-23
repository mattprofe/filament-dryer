/**
* @file filament_dryer_tester.h
* @brief Implementación de funciones para el testeo del sistema de la secadora de filamento. 
* @author Matias Leonardo Baez
* @date 2024
* @contact elmattprofe@gmail.com
*/

#include "filament_dryer_tester.h"

#include "modules/rtc/rtc.h"
#include "modules/buzzer/buzzer.h"
#include "modules/keypad/keypad.h"
#include "modules/temperature_sensor/temperature_sensor.h"
#include "modules/heater/heater.h"
#include "modules/led/led.h"

/**
* @brief Función de prueba para el teclado.
* 
* Permite realizar pruebas manuales del teclado informa por uart si se presiona un botón.
*/
void filamentDryerTestingKeyPad(){
    keypadUpdate();

    if(keypadReadButton() != NONE){
        printf("*** Keypressed.\n");
    }else{
        printf("*** None pressed.\n");
    }

    rtcUpdate(); // actualiza el estado del reloj
}

/**
 * @brief Función de prueba manual para el buzzer.
 * 
 * Permite realizar pruebas manuales del buzzer al presionar el botón run/stop.
 */
void filamentDryerTestingBuzzerManual(){
    static buttonTemplate_t last_button = NONE;
    buttonTemplate_t actual_button = NONE;

    keypadUpdate();

    actual_button = keypadReadButton();

    if(actual_button == RUN_STOP){ // se presiono el botón de RUN/STOP
        if(actual_button != last_button){ // si no es el mismo botón
            last_button = actual_button;
    
            if(buzzerStatus() == ON){
                buzzerOff();
                printf("*** Buzzer OFF.\n");
            }else{
                buzzerOn();
                printf("*** Buzzer ON.\n");
            }
        }
    }else{ // si se solto el botón o se presiono cualquier otro
        last_button = NONE;
    }

    rtcUpdate(); // actualiza el estado del reloj
}

/**
 * @brief Función de prueba automática para el buzzer.
 * 
 * Permite realizar pruebas automáticas del buzzer al emitir pitidos transcurridos los BEEP_EVERY_SECONDS.
 */
void filamentDryerTestingBuzzerAutomatic(){

    buzzerSetTimeBeep(BEEP_EVERY_SECONDS);

    buzzerUpdate();

    rtcUpdate();
}

/**
 * @brief Función de prueba manual para el calentador.
 * 
 * Permite realizar pruebas manuales del calentador utilizando el botón run/stop con protección por sobrecalentamiento, informa por uart temperatura y estado del calentador.
 */
void filamentDryerTestingHeaterManual(){
    static buttonTemplate_t last_button = NONE;
    buttonTemplate_t actual_button = NONE;
    static int last_second = 0;
    int actual_second = 0;

    keypadUpdate();
    temperatureSensorUpdate();

    actual_button = keypadReadButton();
    actual_second = rtcRead().seconds;

    if(actual_button == RUN_STOP){ // se presiono el botón de RUN/STOP
        if(actual_button != last_button){ // si no es el mismo botón
            last_button = actual_button;
    
            if(heaterStatus() == ON){
                heaterOff();
                printf("*** Heater OFF.\n");
            }else{
                heaterOn();
                printf("*** Heater ON.\n");
            }
        }
    }else{ // si se solto el botón o se presiono cualquier otro
        last_button = NONE;
    }

    // cuando pasa 1 segundo
    if(last_second != actual_second){
        last_second = actual_second;

        // protección para evitar dañar el sensor o el calentador
        if(temperatureSensorReadCelsius() >= 100){
            if(heaterStatus() == ON){
                heaterOff();
                printf("----> Heater OFF to prevent overheating (100°C LIMIT)\n");
            }
        }

        // muestra la temperatura por uart
        printf("*** Heater Temperature: %d.\n", temperatureSensorReadCelsius());
    }

    rtcUpdate(); // actualiza el estado del reloj
}

/**
 * @brief Función de prueba automática para el calentador.
 * 
 * Permite realizar pruebas automáticas del calentador seteandolo a 60°C cada 1 segundo informa la temperatura por uart.
 */
void filamentDryerTestingHeaterAutomatic(){

    static int last_second = 0;
    int actual_second = 0;

    actual_second = rtcRead().seconds;

    heaterSetTemperature(60);

    temperatureSensorUpdate();
    
    heaterUpdate(temperatureSensorReadCelsius());

    // cuando pasa 1 segundo
    if(last_second != actual_second){
        last_second = actual_second;

        // muestra la temperatura por uart
        printf("*** Heater Temperature: %d Temperature Test: %d Heater Status: %d.\n", temperatureSensorReadCelsius(), heaterGetTemperatureWork(), heaterStatus());
    }

    rtcUpdate();
}