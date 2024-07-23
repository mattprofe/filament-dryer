/**
* @file keypad.cpp
* @brief Implementación de las funciones para el manejo de botones.
* @author Matias Leonardo Baez
* @date 2024
* @contact elmattprofe@gmail.com
*/
//=====[Libraries]====================================================
#include "keypad.h"

//=====[Declaration of private defines]===============================
#define DEBOUNCE_TIME_MS   30   // ms para evitar BOUNCE and GLITCH

// Si no esta declarado TIME_MS 
#ifndef TIME_MS
#define TIME_MS 10
#endif

//=====[Declaration of private data types]============================
// Estados para la FSM de teclado
typedef enum{
    DOWN,           /**< Botón presionado */
    UP,             /**< Botón suelto*/
    FALLING,        /**< Botón en proceso de presionado*/
    RISING          /**< Botón en proceso de suelto*/
}buttonState_t;


//=====[Declaration and initialization of public global objects]======
DigitalIn* upButton;    /** Objeto para el botón de incrementar */
DigitalIn* downButton;  /** Objeto para el botón de disminuir */
DigitalIn* modeButton;  /** Objeto para el botón de modo */
DigitalIn* runButton;   /** Objeto para el botón de run/stop */

//=====[Declaration of external public global variables]===============

//=====[Declaration and initialization of public global variables]======

//=====[Declaration and initialization of private global variables]======
static buttonState_t keypadStatus;  /**< Se usa para almacenar el estado del teclado en la FSM */
static buttonTemplate_t button; /**< botón valor del teclado  */

//=====[Declaration (prototypes) of private functions]==================
/**
* @brief Retorna el estado del teclado
*
* @return buttonTemplate_t Boton presionado o no
*/
static buttonTemplate_t buttonPress();

//=====[Implementations of public functions]============================
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
void keypadInit(PinName runButtonPin, PinName modeButtonPin, PinName downButtonPin, PinName upButtonPin){

    upButton = new DigitalIn(upButtonPin);
    downButton = new DigitalIn(downButtonPin);
    modeButton = new DigitalIn(modeButtonPin);
    runButton = new DigitalIn(runButtonPin);

    upButton->mode(PullDown);
    downButton->mode(PullDown);
    modeButton->mode(PullDown);
    runButton->mode(PullDown);

    button = NONE;
    keypadStatus = UP;
}

/**
* @brief Retorna el botón presionado o no
*
* Retorna el botón presionado sin Bounce ni Glitch
* 
* @return buttonTemplate_t botón presionado o no
*/
buttonTemplate_t keypadReadButton(){
    return button;
}

/**
* @brief Actualiza el estado de los botones
*
* filtra bounce y glitch del teclado
*/
void keypadUpdate(){

    static int reboundTime = 0;
    static buttonTemplate_t lastButton = NONE;
    buttonTemplate_t actualButton = buttonPress(); 

    switch(keypadStatus){
        case DOWN: // Hay algún presionado presionado
            
            // se soltaron los botones
            if(actualButton == NONE){
                keypadStatus = RISING;   // el botón esta subiendo
            }else{
                keypadStatus = DOWN; // sigue estando presionado algun botón
                
                // Solo acepta que el botón sea otro si efectivamente antes se solto el que estaba presionado
                if(lastButton == NONE){
                    lastButton = actualButton;
                    button = actualButton;
                }
                
            }
        break;

        case FALLING:

            if(reboundTime >= DEBOUNCE_TIME_MS){
                keypadStatus = DOWN;
                reboundTime = 0;
            }

            if(actualButton != NONE){
                reboundTime = reboundTime + TIME_MS;
            }else{
                keypadStatus = UP;
                reboundTime = 0;
            }
        break;
 
        case UP: // ningun botón presionado

            // se presiono alguno botón
            if(actualButton != NONE){
                keypadStatus = FALLING;
            }else{  // sigue sin presionarse algun botón
                keypadStatus = UP;
                button = NONE;
                lastButton = NONE;
            }
        break;

        case RISING:

            // se alcanzo el tiempo para considerar que se solto el botón
            if(reboundTime >= DEBOUNCE_TIME_MS){
                keypadStatus = UP;
                reboundTime = 0;
            }

            // sigue sin presionarse algun botón 
            if(actualButton == NONE){
                reboundTime = reboundTime + TIME_MS;
            }else{ // algún botón sigue presionado
                keypadStatus = DOWN;
                reboundTime = 0;
            }

        break;
    }
}

//=====[Implementations of private functions]=============================
/**
* @brief Retorna el estado del teclado
*
* @return buttonTemplate_t Boton presionado o no
*/
static buttonTemplate_t buttonPress(){
    
    // fue el botón de cambio de modo
    if(*modeButton)
        return MODE;
        
    if(*upButton) // solo fue el botón de subir
        return PLUS;

    if(*downButton)
        return LESS; // solo fue el botón de bajar

    if(*runButton) // fue el botón de inicio/parada
        return RUN_STOP;

    // si no se presiono ningun botón
    return NONE;

}