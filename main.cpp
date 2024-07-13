#include "mbed.h"

int main()
{

    DigitalOut LED(LED1);

    DigitalIn BUTTON(BUTTON1);

    while (true) {

        LED = !BUTTON;

        
    }
}

