//=====[Libraries]====================================================
#include "mbed.h"

//=====[Declaration and Initialization of public global Objects]======
DigitalOut activityLed(PA_15); /** Objeto para el LED de máquina en actividad o secado finalizado */
DigitalOut runLed(PC_12);   /** Objeto para el LED de máquina encendida */
DigitalOut buzzer(PD_2);    /** Objeto para el buzzer */
DigitalOut heater(PC_10);   /** Objeto para el calentador */

DigitalIn upButton(PA_13);  /** Objeto para el botón de incrementar */
DigitalIn downButton(PA_14);    /** Objeto para el botón de disminuir */
DigitalIn modeButton(PB_2);
DigitalIn runButton(PC_8);

AnalogIn heaterSensor(PC_4);    /** Objeto para el sensor del calentador */

UnbufferedSerial uartUsb(USBTX, USBRX, 115200); /** Objeto asociado al convertidor serial USB */

//=====[Declaration and Initialization of public global Variables]====
#define SYSTEM_STOP 0 /**< Estado de sistema detenido */
#define SYSTEM_WORK 1 /**< Estado de sistema secando */
#define SYSTEM_FINISH 2 /**< Estado de sistema secado finalizado */

#define MAX_TEMP    90 /**< Temperatura máxima en grados que se puede seleccionar */
#define MIN_TEMP    30 /**< Temperatura minima en grados que se puede seleccionar */
#define INCREMENT_TEMP  5 /**< Incremento de grados de secado al presionar botones */

#define MAX_TIME    24 /**< Cantidad máxima de horas que se puede seleccionar */
#define MIN_TIME    1 /**< Cantidad mínima de horas que se puede seleccionar */
#define INCREMENT_TIME  1 /**< Incremento de horas de secado al presionar botones */

#define BEEP_EVERY_SECONDS  10 /**< Segundos para emitir un pitido al finalizar el secado */

#define MARGIN_OFF_HEATER   5 /**< Si alcanzo la temperatura no vuelve a encender hasta que cae por debajo */

#define REBOUND_TIME_MS 10  /**< Tiempo de demora para el antirebote en los botones */
#define BUTTON_RUN  5   /**< Botón disminuir presionado */
#define BUTTON_MODE 4   /**< Botón aumentar presionado */
#define BUTTON_UP_DOWN  3   /**< Botón aumentar y disminuir presionados al mismo tiempo */
#define BUTTON_DOWN 2   /**< Botón disminuir presionado */
#define BUTTON_UP   1   /**< Botón aumentar presionado */
#define BUTTON_NONE 0   /**< Ningún Botón presionado */
#define SECONDS_TO_STOPPED_MODE 3 /**< Si se mantienen los 2 botones presionados más de estos segundos detiene el sistema menos cambia el modo*/

#define TIME false  /**< Modo de trabajo de los botones para setear tiempo de secado */
#define TEMPERATURE true /**< Modo de trabajo de los botones para setear temperatura de secado */

#define ON  1   /**< Valor que se usa para encender leds/calentador */
#define OFF !ON /**< Valor que se usa para apagar leds/calentador */
#define BUZZER_ON   1   /**< Valor con el que el buzzer enciende */
#define BUZZER_OFF  !BUZZER_ON  /**< Valor para apagar el buzzer */
#define delay(ms)   thread_sleep_for( ms ) /**< Pseudonimo delay para thread_sleep_fo */

int system_mode; /**< Modo de trabajo del sistema */
bool adjust_mode; /**< Para cambiar entre tiempo y temperatura */

bool heater_status; /**< Estado del calentador */
int heater_temp; /**< Almacena la temperatura cada 1 segundo */

int activity_time; /**< Horas especificadas para trabajar */
int work_temperature; /**< Temperatura especificada de trabajo */

int elapsed_seconds = 0;    /**< Lleva el conteo de segundos transcurridos */
int elapsed_minutes = 0;    /**< Lleva el conteo de minutos transcurridos */
int elapsed_hours = 0;  /**< Lleva el conteo de horas transcurridas */

//=====[Declarations (prototypes) of public functions]================

/**
 * @brief Restablece los contadores de tiempo.
 */
void resetRTC();

/**
 * @brief Lleva el control del tiempo.
 */
void userRTC();

/**
 * @brief Detiene el sistema y restablece los valores iniciales.
 */
void systemStop();

/**
 * @brief Inicializa el sistema y sus componentes.
 */
void systemInit();

/**
 * @brief Lee el estado de los botones.
 *
 * @return Estado del botón presionado.
 */
int buttonPress();

/**
 * @brief Gestiona las acciones cuando se presionan el botón de subir.
 */
void adjustButtonUp();

/**
 * @brief Gestiona las acciones cuando se presiona el botón de bajar.
 */
void adjustButtonDown();

/**
 * @brief Gestiona las acciones cuando presiona un botón.
 */
void keyboardTask();

/**
 * @brief Gestiona el funcionamiento del sistema mientras está secando.
 */
void systemWorking();

/**
 * @brief Gestiona el sistema una vez que el secado ha finalizado.
 */
void systemEndWorking();

/**
 * @brief Lee la temperatura del sensor del calentador.
 *
 * @return Temperatura en grados Celsius.
 */
int heaterTemperature();

//=====[Main function]================================================

/**
 * @brief Punto de entrada principal del programa.
 *
 * Este bucle infinito gestiona el estado del secador de filamento,
 * incluyendo la lectura de botones, la gestión del sistema en reposo y
 * funcionamiento, y la actualización de tiempo y temperatura.
 */
int main()
{
 
    systemInit();

    while (true) {
        
        keyboardTask();

        switch (system_mode)
        {
            case SYSTEM_STOP:
                systemStop();
                break;

            case SYSTEM_WORK:
                systemWorking();
                break;
            
            case SYSTEM_FINISH:
                systemEndWorking(); 
                break;
        }

        userRTC();

    }
}

//=====[Implementations of public functions]==========================
void resetRTC(){
    elapsed_seconds = 0;
    elapsed_minutes = 0;
    elapsed_hours = 0;
}

void userRTC(){
    
    static int delay_count = 0;    /**< Lleva el conteo de la cantidad de retardos */

    delay(10);

    delay_count = delay_count + 1;

    // si se alcanzo 100 retardos de 10 ms paso 1 segundo
    if(delay_count == 100){
        delay_count = 0;

        if(elapsed_seconds<60){
            elapsed_seconds = elapsed_seconds + 1;
        }else{
            elapsed_seconds = 0;

            if(elapsed_minutes<59){
                elapsed_minutes = elapsed_minutes + 1;
            }else{

                elapsed_minutes = 0;
                elapsed_hours = elapsed_hours + 1;
            }
        }
    }
}

/**
 * @brief Detiene el sistema y restablece los valores iniciales.
 *
 * Apaga el calentador, el zumbador y el LED de actividad. También
 * reinicia los tiempos y temperaturas especificados.
 */
void systemStop(){
    activityLed = OFF; // led de actividad apagado
    buzzer = BUZZER_OFF; // zumbador apagado
    heater = OFF; // calentador apagado

    system_mode = SYSTEM_STOP; // trabajando no

    heater_status = false; // calentador apagado
    activity_time = MIN_TIME; // tiempo minimo de secado
    work_temperature = MIN_TEMP; // temperatura minima de secado

    adjust_mode = TIME;
    
    resetRTC();
}

/**
 * @brief Inicializa el sistema y sus componentes.
 *
 * Configura los LEDs, el zumbador, el calentador y los botones en sus
 * estados iniciales, y establece los valores por defecto para la
 * temperatura y el tiempo de secado.
 */
void systemInit(){

    upButton.mode(PullDown);
    downButton.mode(PullDown);
    modeButton.mode(PullDown);
    runButton.mode(PullDown);

    runLed = ON; // led de sistema energizado encendido
    
    systemStop();

    printf("*** Secadora de filamento encendida!.\n");
}



/**
 * @brief Lee el estado de los botones.
 *
 * @return Estado del botón presionado.
 */
int buttonPress(){
    
    // si no se presiono ningun boton
    if(!upButton && !downButton && !runButton && !modeButton)
        return BUTTON_NONE;

    // se presiono alguno de los botones o ambos hacemos una demora
    delay(REBOUND_TIME_MS);

     // Paso el tiempo y resulta que no esta ningun botón presionado
    if(!upButton && !downButton && !runButton && !modeButton)
        return BUTTON_NONE;

    if(upButton && downButton) // fueron ambos botones a la vez
        return BUTTON_UP_DOWN;
        
    if(upButton) // solo fue el botón de subir
        return BUTTON_UP;

    if(downButton)
        return BUTTON_DOWN; // solo fue el botón de bajar

    if(runButton)
        return BUTTON_RUN;

    //if(modeButton)
    return BUTTON_MODE;

}

/**
 * @brief Gestiona las acciones cuando se presionan los botones.
 *
 * Esta función ajusta la temperatura y el tiempo de secado según el
 * botón presionado y el modo de configuración actual. También puede
 * detener el secado si se presionan ambos botones simultáneamente por
 * un tiempo suficiente.
 *
 * @param button El botón que ha sido presionado.
 */
void adjustButtonUp(){

    if(adjust_mode == TIME){
        if(activity_time < MAX_TIME){
            activity_time = activity_time + INCREMENT_TIME;
        }                
    }

    if(adjust_mode == TEMPERATURE){
        if(work_temperature < MAX_TEMP){
            work_temperature = work_temperature + INCREMENT_TEMP;
        }
    }
    
}

void adjustButtonDown(){

    if(adjust_mode == TIME){
        if(activity_time > MIN_TIME){
            activity_time = activity_time - INCREMENT_TIME;
        }
    }

    if(adjust_mode == TEMPERATURE){
        if(work_temperature > MIN_TEMP){
            work_temperature = work_temperature - INCREMENT_TEMP;
        }
    }         
    
}

void keyboardTask(){
    // estado de botones
    static int past_button = BUTTON_NONE;
    int user_button = buttonPress();

    // se presiono un botón
    if(user_button != BUTTON_NONE){

        // si no se mantiene presionado el botón
        if(user_button != past_button){
            past_button = user_button;

            switch(user_button){
                case BUTTON_RUN: // arranque parada
                    if(system_mode == SYSTEM_WORK){ // si estaba secando
                        system_mode = SYSTEM_STOP;
                        printf("-> Secado detenido por el usuario, presione run para volver a secar\n");
                    }else{ // si esta detenido o termino de secar
                        system_mode = SYSTEM_WORK;
                        printf("-> Secado iniciado\n");
                    }
                break;

                case BUTTON_MODE: // cambio de modo
                    // estaba en modo de tiempo cambia a temperatura
                    if(adjust_mode==TIME){
                        adjust_mode = TEMPERATURE;
                        printf("-> Modo Temperatura\n");
                    }else{ // estaba en modo temperatura cambia a tiempo
                        adjust_mode = TIME;
                        printf("-> Modo Tiempo\n");
                    }
                break;

                case BUTTON_UP: // aumenta temperatura o tiempo
                    adjustButtonUp();
                break;

                case BUTTON_DOWN: // disminuye temperatura o tiempo
                    adjustButtonDown();
                break;
            
            }
        }

    }else{
        past_button = BUTTON_NONE;
    }
}

/**
 * @brief Gestiona el funcionamiento del sistema mientras está secando.
 *
 * Enciende el LED de actividad y el calentador según sea
 * necesario para mantener la temperatura especificada, hasta que se 
 * alcance el tiempo de secado.
 */
void systemWorking(){

    static int previous_second = 0;

    // si paso 1 segundo
    if(previous_second != elapsed_seconds){
        previous_second = elapsed_seconds;

        // lee la temperatura
        heater_temp = heaterTemperature();

        // enciende el led de actividad
        activityLed = ON;

        // informa el estado de la maquina
        printf("temperature_now: %d temperature_user: %d hour: %d  minutes: %d seconds: %d hour_user: %d heater: %d\n", heater_temp, work_temperature, elapsed_hours, elapsed_minutes, elapsed_seconds, activity_time, heater_status);
    }else{ // si no paso aún 1 segundo
        //apaga el led de actividad
        activityLed = OFF;
    }

    // se alcanzo el tiempo de secado?
    if(elapsed_hours >= activity_time){

        printf("-> Secado finalizado, para volver a secar presione un boton\n");
        system_mode = SYSTEM_FINISH;
        resetRTC(); // lleva el contado de tiempo a 0
    }

    // se alcanzo la temperatura
    if(heater_temp >= work_temperature){
        heater_status = false; // calentador apagado
    }else{
        // calentador apagado por haber alcanzado temp de trabajo
        if(!heater_status){
            // temperatura paso del margen de mantener apagado
            if(heater_temp < (work_temperature - MARGIN_OFF_HEATER)){
                heater_status = true;
            }
        }
    }

    // pasa el estado del calentador al calentador
    heater = heater_status;
}

/**
 * @brief Gestiona el sistema una vez que el secado ha finalizado.
 *
 * Mantiene encendido el LED de actividad y hace que el zumbador emita
 * un pitido cada cierto intervalo.
 */
void systemEndWorking(){

    //systemStop();
    static int previous_second = 0;
    static int count_seconds = 0;

    heater = OFF; // calentador apagado
    
    activityLed = ON; // led de actividad encendido

    adjust_mode = TIME;

    // si ya paso 1 segundo
    if(previous_second != elapsed_seconds){
        previous_second = elapsed_seconds;
        
        //si aún no se alcanzo los BEEP_EVERY_SECONDS
        if(count_seconds < BEEP_EVERY_SECONDS){
            count_seconds = count_seconds + 1;
        }else{ // se alcanzo los BEEP_EVERY_SECONDS
            count_seconds = 0;
            buzzer = BUZZER_ON; // enciende el zumbador
            //printf("-> Secado finalizado, para volver a secar presione un botón\n");
        }
    }else{ // aún no paso 1 segundo
        buzzer = BUZZER_OFF; // mantiene el zumbador apagado
    }
    
}

/**
 * @brief Lee la temperatura del sensor del calentador.
 *
 * @return Temperatura en grados Celsius.
 */
int heaterTemperature(){

    float voltage = heaterSensor.read() * 3.3f; // Convertir la lectura a voltaje (0.0 a 3.3V)

    // El LM35 proporciona 10mV por grado Celsius, así que convertimos el voltaje a grados Celsius
    int degreesCelsius = static_cast<int>(voltage * 100); // Convertir a grados Celsius y truncar a entero

    return degreesCelsius;
}