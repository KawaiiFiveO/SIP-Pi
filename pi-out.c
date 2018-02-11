//
// Created by chris on 07.02.2018.
//

#include <wiringPi.h>

int initPi(void);
void nibbleOutputGPIO(short, short, short, short, short);
void togglePin(int);
//AMK CHANGE THIS GITHUB
int dtmf_trigger = 0;
int dtmf_value = 0;


PI_THREAD (raspi_output)
{
    if (dtmf_trigger) {
        dtmf_trigger = 0;
        nibbleOutputGPIO(dtmf_value, 1, 4, 5, 6);
        togglePin(7);
    }
}

int initPi(void)
{
    wiringPiSetup();
    pinMode(1,OUTPUT);
    pinMode(4,OUTPUT);
    pinMode(5,OUTPUT);
    pinMode(6,OUTPUT);
    pinMode(7,OUTPUT);
    int success = piThreadCreate(raspi_output);
    return success;
}
void nibbleOutputGPIO(short nibbleValue, short GPIO0,short GPIO1,short GPIO2,short GPIO3)
{
    short mask = 1;
    short temp = nibbleValue;
    digitalWrite(GPIO0,(mask&&temp));
    temp = temp >> 1;
    digitalWrite(GPIO1,(mask&&temp));
    temp = temp >> 1;
    digitalWrite(GPIO2,(mask&&temp));
    temp = temp >> 1;
    digitalWrite(GPIO3,(mask&&temp));
}
void togglePin(int pin)
{
    digitalWrite(pin,1);
    delay(1);
    digitalWrite(pin,0);
}
