/**
* @file heater.h
* @brief Declaraciones de funciones para el manejo del calentador.
* @author Matias Leonardo Baez
* @date 2024
* @contact elmattprofe@gmail.com
*/
//=====[#include guards - begin]========================================
#ifndef _HEATER_H_
#define _HEATER_H_

#include "mbed.h"

//=====[Declaration of private defines]=================================

//=====[Declaration of private data types]==============================

//=====[Declaration (prototypes) of public functions]===================
/**
* @brief Inicializa el calentador.
* 
* Configura el pin del calentador, establece su estado inicial en apagado y la temperatura de trabajo en 0.
* 
* @param heaterPin Pin que controla el buzzer.
*/
void heaterInit(PinName heaterPin);

/**
* @brief Activa el calentador.
* 
* Configura el calentador para que esté encendido.
*/
void heaterOff();

/**
* @brief Desactiva el calentador.
* 
* Configura el calentador para que esté apagado.
*/
void heaterOn();

/**
* @brief Estado del calentador.
* 
* Retorna el estado del calentador.
*
* @return true encendido false apagado.
*/
bool heaterStatus();

/**
* @brief Establece la temperatura del calentador.
* 
* Configura la temperatura que debe alcanzar y mantener el calentador.
*
* @param int temperature temperatura en grados celsius
*/
void heaterSetTemperature(int temperature);

/**
* @brief Temperatura de trabajo del calentador en celcius.
* 
* Retorna la temperatura de trabajo del calentador.
*
* @return int temperatura de trabajo en grados celsius.
*/
int heaterGetTemperatureWork();

/**
* @brief Gestiona el estado del calentador.
* 
* Hace que el calentador trabaje a la temperatura especificada por medio de la función heaterSetTemperature
*
* @param int heaterTemperature temperatura actual
*/
void heaterUpdate(int heaterTemperature);

//=====[#include guards - end]==========================================
#endif