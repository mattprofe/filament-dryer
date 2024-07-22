/**
* @file led.cpp
* @brief Implementación de las funciones para el manejo del sensor de temperatura.
* @author Matias Leonardo Baez
* @date 2024
* @contact elmattprofe@gmail.com
*/
//=====[Libraries]======================================================
#include "temperature_sensor.h"

//=====[Declaration of private defines]=================================
#define SAMPLES 100

#define LM35    0
#define LM35_MINIMUN_OPERATION_CELCIUS  -55
#define LM35_MAXIMUN_OPERATION_CELCIUS  150
#define LM35_ERROR_MAXIMUN_COMPLETE   2
#define LM35_ERROR_MAXIMUN_AMBIENT   0.5

#define SENSOR_SELECT   LM35
//=====[Declaration of private data types]==============================

//=====[Declaration and initialization of public global objects]========
AnalogIn* heaterSensor;    /** Objeto para el sensor del calentador */

//=====[Declaration of external public global variables]================

//=====[Declaration and initialization of public global variables]======

//=====[Declaration and initialization of private global variables]=====
static float voltageSensorValue[SAMPLES];
static float voltageSensorAVG = 0;
//=====[Declaration (prototypes) of private functions]==================

//=====[Implementations of public functions]============================

void temperatureSensorInit(PinName heaterSensorPin){
    heaterSensor = new AnalogIn(heaterSensorPin);
    
    voltageSensorAVG = 0;
    
    for(int i = 0; i < SAMPLES; i++){
        voltageSensorValue[i] = 0;
    }
}

int temperatureSensorReadCelsius(){
    // El LM35 proporciona 10mV por grado Celsius, así que convertimos el voltaje a grados Celsius
    return static_cast<int>(voltageSensorAVG * 100); // Convertir a grados Celsius y truncar a entero
}

/**
 * @brief Lee la temperatura del sensor del calentador.
 *
 */
void temperatureSensorUpdate(){
    static int index = 0;
    float samples_sum = 0;

    voltageSensorValue[index] = heaterSensor->read() * 3.3f; // Convertir la lectura a voltaje (0.0 a 3.3V)

    index++;

    if(index >= SAMPLES){
        index = 0;
    }

    for(int i = 0; i < SAMPLES; i++){
        samples_sum = samples_sum + voltageSensorValue[i];
    }

    voltageSensorAVG = samples_sum / SAMPLES;

}

//=====[Implementations of private functions]===========================