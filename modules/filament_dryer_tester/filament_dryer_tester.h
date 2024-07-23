/**
* @file filament_dryer_tester.h
* @brief Declaraciones de funciones para el testeo del sistema de la secadora de filamento. 
* @author Matias Leonardo Baez
* @date 2024
* @contact elmattprofe@gmail.com
*/
//=====[#include guards - begin]========================================

#ifndef _FILAMENT_DRYER_TESTER_H_
#define _FILAMENT_DRYER_TESTER_H_

#include "modules/filament_dryer_system/filament_dryer_system.h"

//=====[Declaration of private defines]=================================

//=====[Declaration of private data types]==============================

//=====[Declaration (prototypes) of public functions]===================
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