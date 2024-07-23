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
#define SAMPLES 100 /**< Número de muestras para el promedio del sensor. */

#define LM35    0   /**< Selección del tipo de sensor utilizado. */
#define LM35_MINIMUN_OPERATION_CELCIUS  -55 /**< Temperatura mínima de operación del sensor LM35 en grados Celsius. */
#define LM35_MAXIMUN_OPERATION_CELCIUS  150 /**< Temperatura máxima de operación del sensor LM35 en grados Celsius. */
#define LM35_ERROR_MAXIMUN_COMPLETE   2 /**< Error máximo del sensor LM35 en toda la gama de temperaturas en grados Celsius. */
#define LM35_ERROR_MAXIMUN_AMBIENT   0.5    /**< Error máximo del sensor LM35 en rango de temperatura ambiente en grados Celsius. */

#define SENSOR_SELECT   LM35    /**< Sensor utilizado. */    
//=====[Declaration of private data types]==============================

//=====[Declaration and initialization of public global objects]========
AnalogIn* heaterSensor;    /** Objeto para el sensor del calentador */

//=====[Declaration of external public global variables]================

//=====[Declaration and initialization of public global variables]======

//=====[Declaration and initialization of private global variables]=====
static float voltageSensorValue[SAMPLES]; /**< muestras de voltaje leídas del sensor de temperatura */
static float voltageSensorAVG = 0; /**< valor promedio del voltaje del sensor de temperatura */
//=====[Declaration (prototypes) of private functions]==================

//=====[Implementations of public functions]============================

/**
 * @brief Inicializa el sensor de temperatura.
 * 
 * Esta función configura el pin del sensor de temperatura e inicializa 
 * el valor promedio de voltaje del sensor.
 * 
 * @param heaterSensorPin Pin del sensor de temperatura.
 */
void temperatureSensorInit(PinName heaterSensorPin){
    heaterSensor = new AnalogIn(heaterSensorPin);
    
    voltageSensorAVG = 0;
    
    for(int i = 0; i < SAMPLES; i++){
        voltageSensorValue[i] = 0;
    }
}

/**
 * @brief Lee la temperatura en grados Celsius.
 * 
 * Convierte el valor promedio de voltaje del sensor a grados Celsius.
 * 
 * @return int Temperatura en grados Celsius.
 */
int temperatureSensorReadCelsius(){
    // El LM35 proporciona 10mV por grado Celsius, así que convertimos el voltaje a grados Celsius
    return static_cast<int>(voltageSensorAVG * 100); // Convertir a grados Celsius y truncar a entero
}

/**
 * @brief Actualiza los valores de temperatura.
 * 
 * Lee el voltaje del sensor de temperatura, lo almacena en un 
 * arreglo y calcula el promedio de las muestras para obtener una lectura estable.
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