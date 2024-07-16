//=====[Libraries]====================================================
#include "mbed.h"

//=====[Declaration and Initialization of public global Objects]======
DigitalOut activityLed(PA_15);
DigitalOut runLed(PC_12);
DigitalOut buzzer(PD_2); /**< */
DigitalOut heater(PC_10);

DigitalIn upButton(PA_13);
DigitalIn downButton(PA_14);

AnalogIn heaterSensor(PC_4);

UnbufferedSerial uartUsb(USBTX, USBRX, 115200); /**< Object associated serial USB converter */

//=====[Declaration and Initialization of public global Variables]====
#define MAX_TEMP    90 /**< Temperatura máxima en grados que se puede seleccionar */
#define MIN_TEMP    30 /**< Temperatura minima en grados que se puede seleccionar */
#define INCREMENT_TEMP  5 /**< Incremento de grados de secado al presionar botones */
#define TEMPERATURE true

#define MAX_TIME    24 /**< Cantidad máxima de horas que se puede seleccionar */
#define MIN_TIME    1 /**< Cantidad mínima de horas que se puede seleccionar */
#define INCREMENT_TIME  1 /**< Incremento de horas de secado al presionar botones */
#define TIME false

#define BLINK_ACTIVITY_SECONDS  1 /**< Especifica cada cuantos segundos parpadea el led de actividad */

#define BEEP_EVERY_SECONDS  10 /**< Segundos para emitir un pitido al finalizar el secado */

#define MARGIN_OFF_HEATER   5 /**< Si alcanzo la temperatura no vuelve a encender hasta que cae por debajo */

#define REBOUND_TIME_MS 10 /**< Tiempo de demora para el antirebote en los botones */
#define BUTTON_UP_DOWN  3
#define BUTTON_DOWN 2
#define BUTTON_UP   1
#define BUTTON_NONE 0
#define SECONDS_TO_STOPPED_MODE 3 /**< Si se mantienen los 2 botones presionados durante estos segundos detiene el sistema */

#define OFF 0
#define ON  1
#define delay(ms)   thread_sleep_for( ms ) /**< Pseudonimo delay para thread_sleep_fo */

bool activity; // si el sistema esta secando
bool dryer_complete; // termino de secar
bool heater_status; // estado del calentador
int heater_temp; // almacena la temperatura cada 1 segundo

bool mode_configuration; // Para cambiar entre tiempo y temperatura

int activity_time; // horas especificadas para trabajar
int work_temperature; // temperatura especificada de trabajo

int delay_count = 0;
int elapsed_seconds = 0;
int elapsed_minutes = 0;
int elapsed_hours = 0;

int past_button;

//=====[Declarations (prototypes) of public functions]================
void systemInit();
void blinkActivityLed();
int buttonPress();
void buttonPressingTask(int button);
void systemStop();
void systemWorking();
void systemEndWorking();
int heaterTemperature();

//=====[Main function]================================================
int main()
{
    systemInit();

    volatile int user_button = BUTTON_NONE;    

    printf("*** Secadora de filamento encendida!.\n");

    while (true) {
        // estado de botones
        user_button = buttonPress();

        // si se presiono algun botón
        if(user_button != BUTTON_NONE){

            // no esta trabajando
            if(!activity){

                // antes no se estaba presionando ningun botón
                if(past_button == BUTTON_NONE ){
                    activity = true;
                    dryer_complete = false;
                    printf("-> Secado Iniciado\n");
                }
            }else{ // esta trabajando

                // aun esta secando
                if(!dryer_complete){
                    buttonPressingTask(user_button);
                }else{ // termino de secar
                    activity = false;
                    dryer_complete = false;
                }
            }
        }else{ // no se presiono ningun botón
            past_button = BUTTON_NONE; // ultimo botón presionado es ninguno
        }

        // sistema en reposo
        if(!activity){
            systemStop();
        }else{ // sistema funcionando

            // no termino de secar
            if(!dryer_complete){
                systemWorking();
            }else{ // termino de secar
                systemEndWorking(); 
            }
        }

        delay(10);

        delay_count = delay_count + 1;

        // si se alcanzo 100 retardos de 10 ms paso 1 segundo
        if(delay_count == 100){
            delay_count = 0;

            if(elapsed_seconds<60){

                // se lee la temperatura cada 1 segundo
                heater_temp = heaterTemperature();

                // Solo envia los valores si la máquina no termino de secar
                if(!dryer_complete){
                    printf("temp_now: %d temp_user: %d time: %d : %d : %d time_user: %d heater: %d\n", heater_temp, work_temperature, elapsed_hours, elapsed_minutes, elapsed_seconds, activity_time, heater_status);
                }

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
}

//=====[Implementations of public functions]==========================
void systemInit(){
    runLed = ON; // led de sistema energizado encendido
    activityLed = OFF; // led de actividad apagado
    buzzer = OFF; // zumbador apagado
    heater = OFF; // calentador apagado

    upButton.mode(PullDown);
    downButton.mode(PullDown);

    activity = false; // trabajando no
    heater_status = false; // calentador apagado
    activity_time = MIN_TIME; // tiempo minimo de secado
    work_temperature = MIN_TEMP; // temperatura minima de secado

    past_button = BUTTON_UP;

    mode_configuration = TIME; // especifica que se configura el tiempo con los botones

    delay_count = 0;
    elapsed_seconds = 0;
    elapsed_minutes = 0;
    elapsed_hours = 0;
}

void blinkActivityLed(){

    static int previous_second = 0;

    // si paso 1 segundo enciende el led de actividad
    if(previous_second != elapsed_seconds){
        previous_second = elapsed_seconds;

        activityLed = ON;
    }else{ // si no paso aún 1 segundo apaga el led de actividad
        activityLed = OFF;
    }
}

int buttonPress(){
    
    // si no se presiono ningun boton
    if(!upButton && !downButton)
        return BUTTON_NONE;

    // se presiono alguno de los botones o ambos hacemos una demora
    delay(REBOUND_TIME_MS);

     // Paso el tiempo y resulta que no esta ningun botón presionado
    if(!upButton && !downButton)
        return BUTTON_NONE;

    if(upButton && downButton) // fueron ambos botones a la vez
        return BUTTON_UP_DOWN;
        
    if(upButton) // solo fue el botón de subir
        return BUTTON_UP;

    return BUTTON_DOWN; // solo fue el botón de bajar

}

void buttonPressingTask(int button){

    static int previous_second = 0;
    static int count_seconds = 0;

    // para que solo se lea el botón presionado una vez
    if(button != past_button){

        // si se presiono ambos botones a la vez
        if(past_button == BUTTON_UP_DOWN){

            // se mantuvo presionado ambos botones mas de SECONDS_TO_STOPPED_MODE
            if(count_seconds >= SECONDS_TO_STOPPED_MODE){
                activity = false;
                printf("-> Secado detenido por el usuario, presione un botón para iniciar\n");
            }

            // se mantuvo presionado ambos botones menos de SECONDS_TO_STOPPED_MODE
            if(count_seconds < SECONDS_TO_STOPPED_MODE){

                if(mode_configuration == TIME){
                    printf("-> Modo Temperatura\n");
                }else{
                    printf("-> Modo Tiempo\n");
                }

                // cambia el modo de seteo de valores 
                mode_configuration = !mode_configuration;
            }

        }

        // el botón actual pasa a ser el anterior
        past_button = button;

        if(button == BUTTON_UP){
            if(mode_configuration == TIME){
                if(activity_time < MAX_TIME){
                    activity_time = activity_time + INCREMENT_TIME;
                }                
            }

            if(mode_configuration == TEMPERATURE){
                if(work_temperature < MAX_TEMP){
                    work_temperature = work_temperature + INCREMENT_TEMP;
                }
            }
        }

        if(button == BUTTON_DOWN){
            if(mode_configuration == TIME){
                if(activity_time > MIN_TIME){
                    activity_time = activity_time - INCREMENT_TIME;
                }
            }

            if(mode_configuration == TEMPERATURE){
                if(work_temperature > MIN_TEMP){
                    work_temperature = work_temperature - INCREMENT_TEMP;
                }
            }                  
        }

        count_seconds = 0; // limpia el valor de segundos presionando el mismo boton

    }else{ // se mantienen presionado los mismos botones
        
        // si paso 1 segundo
        if(previous_second != elapsed_seconds){
            previous_second = elapsed_seconds;
            // incrementa el contador de segundos que estan presionados
            count_seconds = count_seconds + 1;
        }

    }
    
}

void systemStop(){
    activityLed = OFF; // led de actividad apagado
    buzzer = OFF; // zumbador apagado
    heater = OFF; // calentador apagado

    activity = false; // trabajando no
    heater_status = false; // calentador apagado
    activity_time = MIN_TIME; // tiempo minimo de secado
    work_temperature = MIN_TEMP; // temperatura minima de secado

    mode_configuration = TIME;

    delay_count = 0;
    elapsed_seconds = 0;
    elapsed_minutes = 0; // setear en 58 para hacer pruebas
    elapsed_hours = 0;
}

void systemWorking(){

    // se alcanzo el tiempo de secado?
    if(elapsed_hours >= activity_time){

        printf("-> Secado finalizado, para volver a secar presione un boton\n");
        dryer_complete = true;
    }

    // parpadea cada 1 segundo
    blinkActivityLed();

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

void systemEndWorking(){

    //systemStop();
    static int previous_second = 0;
    static int count_seconds = 0;

    heater = OFF; // calentador apagado
    
    activityLed = ON; // led de actividad encendido

    mode_configuration = TIME;

    // si ya paso 1 segundo
    if(previous_second != elapsed_seconds){
        previous_second = elapsed_seconds;
        
        //si aún no se alcanzo los BEEP_EVERY_SECONDS
        if(count_seconds < BEEP_EVERY_SECONDS){
            count_seconds = count_seconds + 1;
        }else{ // se alcanzo los BEEP_EVERY_SECONDS
            count_seconds = 0;
            buzzer = ON; // enciende el zumbador
            printf("-> Secado finalizado, para volver a secar presione un botón\n");
        }
    }else{ // aún no paso 1 segundo
        buzzer = OFF; // mantiene el zumbador apagado
    }
    
}

int heaterTemperature(){

    float voltage = heaterSensor.read() * 3.3f; // Convertir la lectura a voltaje (0.0 a 3.3V)

    // El LM35 proporciona 10mV por grado Celsius, así que convertimos el voltaje a grados Celsius
    int degreesCelsius = static_cast<int>(voltage * 100); // Convertir a grados Celsius y truncar a entero

    return degreesCelsius;
}