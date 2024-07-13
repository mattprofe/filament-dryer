# Secador de Filamento para impresora 3D

## TP1 - Curso Online de Sistemas Embebidos

### Alumno:
Matias Leonardo Baez

### Profesores: 
- Ariel Lutenberg
- Segio Caprile
- Juan Manuel Reta
- Eduardo Filomena

### Objetivo:
Eliminar la humedad del filamento que se utiliza en la impresión 3D.

### Descripción:
El sistema eliminará la humedad del filamento especificando la temperatura y la duración del secado mediante dos pulsadores. La temperatura se ajusta de a 1 grado con un máximo de 60 grados y el tiempo de a 1 hora con un máximo de 24 horas. Al encender el sistema, un LED indica que está energizado. Al presionar cualquiera de los botones, se incrementa o disminuye la temperatura, activando o desactivando una hotbed sobre la cual está suspendida una bobina de 1 kg de filamento. Por defecto, el tiempo de secado es 1 hora. Mientras el sistema está trabajando, otro LED parpadea cada segundo. Al finalizar el tiempo de secado, el LED de actividad se mantiene encendido, el buzzer emite un pitido cada 10 segundos y la hotbed se apaga. Al presionar cualquier botón, el buzzer se apaga y el proceso comienza nuevamente con la temperatura previamente configurada. El sistema entra en inactividad, apagando la hotbed y el contador de tiempo, al mantener presionados los dos botones durante 3 segundos y vuelve a su estado de trabajo al presionar cualquier botón.

Además cada 1 segundo se enviarán por el puerto serie los siguientes datos:

- Temperatura actual
- Temperatura seteada
- Tiempo transcurrido
- Tiempo seteado
- Estado de la hotbed

***Para las siguientes etapas del curso se planea implementar el sensor de temperatura y humedad dht11, un display de caracteres o gráfico y el Módulo RTC Ds3231***

### Plataforma de Desarrollo:
Nucleo-64 STM32F401

### Periféricos a Utilizar:

**Sensores:**
- LM35 (Sensor de temperatura)
**Actuadores:**
- Relé (Para controlar la hotbed)
**Indicadores:**
- 2 LEDs (1 para indicar que el sistema está encendido y 1 para indicar que el sistema está trabajando o ha finalizado la tarea)
- 1 Buzzer (Para alertas sonoras)
**Entradas:**
- 2 Pulsadores (Para ajustar la temperatura y el tiempo)
**Comunicación:**
- Serial (Para enviar datos a un sistema externo)
     
### Diagrama en Bloques:

![Diagrama en bloques](https://raw.githubusercontent.com/mattprofe/assets/master/filament_dryer/diagrama_de_bloques_tp1.png "Diagrama en bloques")
