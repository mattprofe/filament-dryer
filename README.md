# Secador de Filamento para impresora 3D

## TP1 - Curso Online de Sistemas Embebidos

### Alumno:
Matias Leonardo Baez

### Profesores: 
- Ariel Lutenberg
- Segio Caprile
- Juan Manuel Reta
- Eduardo Filomena

## Video del Funcionamiento

<div align="left">
      <a href="https://youtu.be/93DJ_dfqi2k">
         <img src="https://i.ytimg.com/vi/93DJ_dfqi2k/maxresdefault.jpg" style="width:45%;">
      </a>
</div>

## Objetivo:
Eliminar la humedad del filamento que se utiliza en la impresión 3D.

## Descripción:
El sistema eliminará la humedad del filamento especificando la temperatura y la duración del secado mediante dos pulsadores. La temperatura se ajusta de a 5°C con un máximo de 90°C (mínimo 30°C) y el tiempo de a 1 hora con un máximo de 24 horas (mínimo 1 hora). Al encender el sistema, un LED indica que está energizado. Al presionar cualquiera de los botones, se incrementa o disminuye la temperatura, activando o desactivando una hotbed sobre la cual está suspendida una bobina de 1 kg de filamento. Por defecto, el tiempo de secado es 1 hora y la temperatura en 30°C. Mientras el sistema está trabajando, otro LED parpadea cada segundo. Al finalizar el tiempo de secado, el LED de actividad se mantiene encendido, el buzzer emite un pitido cada 10 segundos y la hotbed se apaga. Al presionar cualquier botón, el buzzer se apaga y el proceso comienza nuevamente con la temperatura previamente configurada. El sistema entra en inactividad, apagando la hotbed y el contador de tiempo, al mantener presionados los dos botones más de 3 segundos y vuelve a su estado de trabajo al presionar cualquier botón, si se presiona menos de 3 segundos ambos botones se cambia a modo de selección de temperatura o tiempo.

Además cada 1 segundo se enviarán por uart los siguientes datos:

- Temperatura actual
- Temperatura seteada
- Tiempo transcurrido
- Tiempo seteado
- Estado de la hotbed

## Plataforma de Desarrollo:
Nucleo-64 STM32F401

## Periféricos a Utilizar:

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
- Uart (Para enviar datos a un sistema externo)
     
## Diagrama en Bloques:

![Diagrama en bloques](https://raw.githubusercontent.com/mattprofe/assets/master/filament_dryer/diagrama_de_bloques_tp1.png "Diagrama en bloques")

## Estado actual del sistema:

Actualmente se encuentra funcionando sobre una protoboard como se aprecia en la figura 1.

#### Figura 1:
![Electrónica de la máquina](https://raw.githubusercontent.com/mattprofe/assets/master/filament_dryer/20240716_141809.jpg "Electrónica de la máquina")

El estado y control del sistema se realiza desde los botones montados en la protoboard (pulsador izquierdo aumenta y derecho disminuye), el led verde indica que el sistema está encendido y el rojo si se encuentra secando o termino de secar, el buzzer solo se activa cuando el secado finalizo. Figura 2.

#### Figura 2:
![Panel de la máquina](https://raw.githubusercontent.com/mattprofe/assets/master/filament_dryer/20240716_141917.jpg "Panel de la máquina")

Se monto el LM35 en el centro de la hotbed, el control de encendido de la hotbed se hace mediante un relé que se aprecia a la derecha. Figura 3.

#### Figura 3:
![LM35 y hotbed](https://raw.githubusercontent.com/mattprofe/assets/master/filament_dryer/20240716_141932.jpg "LM35 y hotbed")

Al encender el sistema se enciende el led verde (Figura 4), se envia el mensaje por uart (Figura 5) y queda a la espera de que se presione alguno de los botones para comenzar a trabajar.

#### Figura 4:
![Sistema encendido](https://raw.githubusercontent.com/mattprofe/assets/master/filament_dryer/20240716_142011.jpg "Sistema encendido")

#### Figura 5:
![Sistema encendido uart](https://raw.githubusercontent.com/mattprofe/assets/master/filament_dryer/20240716_142046.jpg "Sistema encendido uart")

Al presionar cualquiera de los botones, inicia el proceso de secado y cada 1 segundo parpadea el led de actividad (Rojo), además se envia la temperatura actual, temperatura especificada, tiempo actual, tiempo especificado y estado de la hotbed. Figura 6.

#### Figura 6:
![Sistema secando](https://raw.githubusercontent.com/mattprofe/assets/master/filament_dryer/20240716_142106.jpg "Sistema secando")

Al mantener presionados ambos botones menos de 3 segundos, se cambia entre modo de selección de tiempo y temperatura, esto mientras el sistema esta secando, se notifica por uart el evento de cambio de modo. Figura 7.

#### Figura 7:
![Cambio de modo](https://raw.githubusercontent.com/mattprofe/assets/master/filament_dryer/20240716_142143.jpg "Cambio de modo")

Al mantener presionados ambos botones por 3 segundos o más, el sistema se detiene, informa por uart el evento, se restablece la temperatura y tiempo de secado, el sistema espera a que se presione un botón para volver a secar o que se apague. Figura 8.

#### Figura 8:
![Sistema detenido por el usuario](https://raw.githubusercontent.com/mattprofe/assets/master/filament_dryer/secado_detenido_usuario.jpg "Sistema detenido por el usuario")

Al alcanzar la/s hora/s de secado especificadas por el usuario, se envia por uart un aviso, se apaga la hotbed y el led de actividad se mantiene encendido, cada 10 segundos se emite un pitido y queda a la espera de que se presione un botón para volver a secar o que se apague el sistema. Figura 9.

#### Figura 9:
![Secado finalizado](https://raw.githubusercontent.com/mattprofe/assets/master/filament_dryer/20240716_142304.jpg "Secado finalizado")

## Desarrollos a futuro

***Para las siguientes etapas del curso se planea implementar el sensor de temperatura y humedad dht11, un display de caracteres o gráfico y el Módulo RTC Ds3231***