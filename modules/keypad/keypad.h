/**
* @file keypad.h
* @brief Declaraciones de funciones para el manejo de botones.
* @author Matias Leonardo Baez
* @date 2024
* @contact elmattprofe@gmail.com
*/
//=====[#include guards - begin]=======================================
#ifndef _KEYPAD_H_
#define _KEYPAD_H_

#include "mbed.h"

//=====[Declaration of private defines]================================

//=====[Declaration of private data types]=============================

// botones del teclado
typedef enum{
    NONE,   /**< Ningun botón presionado */
    RUN_STOP,   /**< Botón Run/Stop presionado */
    MODE,   /**< Botón de modo presionado */
    PLUS,   /**< Botón de incrementar presionado */
    LESS    /**< Botón de disminuir presionado */
}buttonTemplate_t;

//=====[Declaration (prototypes) of public functions]==================
/**
* @brief Inicializa los botones
*
* Inicializa y configura los botónes
*
* @param runButtonPin Pin para el botón
* @param modeButtonPin Pin para el botón
* @param downButtonPin Pin para el botón
* @param upButtonPin Pin para el botón
*/
void keypadInit(PinName runButtonPin, PinName modeButtonPin, PinName downButtonPin, PinName upButtonPin);

/**
* @brief Retorna el botón presionado o no
*
* Retorna el botón presionado sin Bounce ni Glitch
* 
* @return buttonTemplate_t botón presionado o no
*/
buttonTemplate_t keypadReadButton();

/**
* @brief Actualiza el estado de los botones
*
* filtra bounce y glitch del teclado
*/
void keypadUpdate();

//=====[#include guards - end]=======================================
#endif