/**
* @file main.cpp
* @brief Inicialización de la secadora de filamento y ejecución.
* @author Matias Leonardo Baez
* @date 2024
* @contact elmattprofe@gmail.com
*/
//=====[Libraries]====================================================
#include "mbed.h"
#include "modules/filament_dryer_system/filament_dryer_system.h"

//=====[Declaration and Initialization of public global Objects]======

//=====[Declaration and Initialization of public global Variables]====

//=====[Declarations (prototypes) of public functions]================

//=====[Main function]================================================

/**
 * @brief Punto de entrada principal del programa.
 *
 * Este bucle infinito gestiona el estado del secador de filamento,
 * incluyendo la lectura de botones, la gestión del sistema en reposo y
 * funcionamiento, y la actualización de tiempo y temperatura.
 */
int main(){
    filamentDryerInit();
    
    while (true) {
        filamentDryerUpdate();
        //filamentDryerTestingBuzzerManual();
        //filamentDryerTestingBuzzerAutomatic();
        //filamentDryerTestingKeyPad();
        //filamentDryerTestingHeaterManual();
        //filamentDryerTestingHeaterAutomatic();
    }

}

//=====[Implementations of public functions]==========================