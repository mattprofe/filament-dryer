/**
* @file heater.cpp
* @brief Implementación de las funciones para el manejo del calentador.
* @author Matias Leonardo Baez
* @date 2024
* @contact elmattprofe@gmail.com
*/
//=====[Libraries]======================================================
#include "heater.h"

//=====[Declaration of private defines]=================================
#define ON  1   /**< Valor que se usa para encender leds/calentador */
#define OFF !ON /**< Valor que se usa para apagar leds/calentador */

#define HYSTERESIS  2 /**< Para evitar conmutaciones de relé rápidas */

//=====[Declaration of private data types]==============================

//=====[Declaration and initialization of public global objects]========
DigitalOut* heater;   /** Objeto para el calentador */

//=====[Declaration of external public global variables]================

//=====[Declaration and initialization of public global variables]======

//=====[Declaration and initialization of private global variables]=====
static int heaterWorkTemperature;  // temperatura de trabajo del calentador

static float kp = 72.63f;  // Ganancia proporcional
static float ki = 14.19f;  // Ganancia integral
static float kd = 247.56f; // Ganancia derivativa

static float integral = 0.0f;
static float last_error = 0.0f;

//=====[Declaration (prototypes) of private functions]==================
/**
* @brief Gestiona el estado del calentador por medio de control ON/OFF.
* 
* Hace que el calentador trabaje a la temperatura especificada por medio de la función heaterSetTemperature
*
* @param int heaterTemperature temperatura actual
*/
static void heaterControlOnOff(int heaterTemperature);

/**
* @brief Gestiona el estado del calentador por medio de control PID.
* 
* Hace que el calentador trabaje a la temperatura especificada por medio de la función heaterSetTemperature
*
* @param int heaterTemperature temperatura actual
*/
static void heaterControlPID(int heaterTemperature);

//=====[Implementations of public functions]============================
/**
* @brief Inicializa el calentador.
* 
* Configura el pin del calentador, establece su estado inicial en apagado y la temperatura de trabajo en 0.
* 
* @param heaterPin Pin que controla el buzzer.
*/
void heaterInit(PinName heaterPin){
    heater = new DigitalOut(heaterPin);
    heaterOff();
    heaterWorkTemperature = 0;
}

/**
* @brief Activa el calentador.
* 
* Configura el calentador para que esté encendido.
*/
void heaterOff(){
    *heater = OFF;
}

/**
* @brief Desactiva el calentador.
* 
* Configura el calentador para que esté apagado.
*/
void heaterOn(){
    *heater = ON;
}

/**
* @brief Estado del calentador.
* 
* Retorna el estado del calentador.
*
* @return true encendido false apagado.
*/
bool heaterStatus(){
    return *heater;
}

/**
* @brief Establece la temperatura del calentador.
* 
* Configura la temperatura que debe alcanzar y mantener el calentador.
*
* @param int temperature temperatura en grados celsius
*/
void heaterSetTemperature(int temperature){
    heaterWorkTemperature = temperature;
}

/**
* @brief Temperatura de trabajo del calentador en celcius.
* 
* Retorna la temperatura de trabajo del calentador.
*
* @return int temperatura de trabajo en grados celsius.
*/
int heaterGetTemperatureWork(){
    return heaterWorkTemperature;
}

/**
* @brief Gestiona el estado del calentador.
* 
* Hace que el calentador trabaje a la temperatura especificada por medio de la función heaterSetTemperature
*
* @param int heaterTemperature temperatura actual
*/
void heaterUpdate(int heaterTemperature){

    //heaterControlPID(heaterTemperature);
    heaterControlOnOff(heaterTemperature);
}

//=====[Implementations of private functions]===========================
/**
* @brief Gestiona el estado del calentador por medio de control ON/OFF.
* 
* Hace que el calentador trabaje a la temperatura especificada por medio de la función heaterSetTemperature
*
* @param int heaterTemperature temperatura actual
*/
static void heaterControlOnOff(int heaterTemperature){
    if(heaterTemperature >= (heaterWorkTemperature + HYSTERESIS)){
        heaterOff(); // calentador apagado
    }else{
        // calentador apagado por haber alcanzado temp de trabajo
        if(heaterStatus() == OFF){
            // temperatura paso del margen de mantener apagado
            if(heaterTemperature < (heaterWorkTemperature - HYSTERESIS)){
                heaterOn();
            }
        }
    }
}

/**
* @brief Gestiona el estado del calentador por medio de control PID.
* 
* Hace que el calentador trabaje a la temperatura especificada por medio de la función heaterSetTemperature
*
* @param int heaterTemperature temperatura actual
*/
static void heaterControlPID(int heaterTemperature){
    float error = heaterWorkTemperature - heaterTemperature;

    integral += error;
    float derivative = error - last_error;
    float controlOutput = kp * error + ki * integral + kd * derivative;

    last_error = error;

    if (controlOutput > 0.0f) {
        heaterOn();
    } else {
        heaterOff();
    }
}