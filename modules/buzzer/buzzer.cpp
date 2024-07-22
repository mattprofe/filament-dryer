/**
* @file buzzer.cpp
* @brief Implementación de las funciones para el manejo del buzzer.
* @author Matias Leonardo Baez
* @date 2024
* @contact elmattprofe@gmail.com
*/
//=====[Libraries]======================================================
#include "buzzer.h"

//=====[Declaration of private defines]=================================
#ifndef TIME_MS
#define TIME_MS 10
#endif

#define BUZZER_ON   1   /**< Valor con el que el buzzer enciende */
#define BUZZER_OFF  !BUZZER_ON  /**< Valor para apagar el buzzer */

//=====[Declaration of private data types]==============================

//=====[Declaration and initialization of public global objects]========
DigitalOut* alertBuzzer;    /** Objeto para el buzzer */

//=====[Declaration of external public global variables]================

//=====[Declaration and initialization of public global variables]======

//=====[Declaration and initialization of private global variables]=====
static int seconds_to_beep; /**< Tiempo en segundos para que el buzzer emita sonido */

//=====[Declaration (prototypes) of private functions]==================

//=====[Implementations of public functions]============================
/**
 * @brief Inicializa el buzzer.
 * 
 * Configura el pin del buzzer y establece su estado inicial en apagado.
 * 
 * @param buzzerPin Pin que controla el buzzer.
 */
void buzzerInit(PinName buzzerPin){
    alertBuzzer = new DigitalOut(buzzerPin);
    buzzerOff();
    buzzerSetTimeBeep(0);
}

/**
 * @brief Activa el buzzer.
 * 
 * Configura el buzzer para que esté encendido.
 */
void buzzerOn(){
    *alertBuzzer = BUZZER_ON;
}

/**
 * @brief Desactiva el buzzer.
 * 
 * Configura el buzzer para que esté apagado.
 */
void buzzerOff(){
    *alertBuzzer = BUZZER_OFF;
}

/**
 * @brief Obtiene el estado actual del buzzer.
 * 
 * @return El estado actual del buzzer, donde 1 significa encendido y 0 apagado.
 */
int buzzerStatus(){
    return *alertBuzzer;
}

/**
 * @brief Obtiene el tiempo configurado para el beep del buzzer.
 * 
 * @return Tiempo en segundos para que el buzzer emita sonido.
 */
int buzzerGetTimeBeep(){
    return seconds_to_beep;
}

/**
 * @brief Configura el tiempo para el beep del buzzer.
 * 
 * @param seconds Tiempo en segundos para el beep del buzzer.
 */
void buzzerSetTimeBeep(int seconds){
    seconds_to_beep = seconds;
}

/**
 * @brief Actualiza el estado del buzzer basándose en el tiempo configurado.
 * 
 * Controla el encendido y apagado del buzzer de acuerdo con el tiempo configurado y el tiempo transcurrido.
 */
void buzzerUpdate(){

    static int elapsed_seconds = 0;  /**< Contador de segundos transcurridos */
    static int previous_second = 0;  /**< Último segundo registrado */
    static int count_seconds = 0;    /**< Contador para el tiempo de beep */
    static int delay_count = 0;      /**< Contador para los retardos de 10 ms */

    delay_count = delay_count + 1;

    // si se alcanzo 100 retardos de 10 ms paso 1 segundo
    if(delay_count >= 100){
        delay_count = 0;
        
        if(elapsed_seconds<60){
            elapsed_seconds = elapsed_seconds + 1;
        }else{
            elapsed_seconds = 0;
        }
    }

    // si ya paso 1 segundo
    if(previous_second != elapsed_seconds){
        previous_second = elapsed_seconds;
        
        count_seconds = count_seconds + 1;

        // se alcanzo los seconds_to_beep
        if(count_seconds >= seconds_to_beep){
            count_seconds = 0;
            buzzerOn(); // enciende el zumbador
        }

    }else{ // aún no paso 1 segundo
        buzzerOff();
    }
}


//=====[Implementations of private functions]===========================