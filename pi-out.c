//
// Created by chris on 07.02.2018.
//

#include <wiringPi/wiringPi/wiringPi.h>

int initPi(void);
void nibbleOutputGPIO(int,int,int,int,int);
void togglePin(int);

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
    wiringPiSetupGpio();
    pinMode(1,OUTPUT);
    pinMode(4,OUTPUT);
    pinMode(5,OUTPUT);
    pinMode(6,OUTPUT);
    pinMode(7,OUTPUT);
    int success = piThreadCreate(raspi_output);
    return success;
}
void nibbleOutputGPIO(int nibbleValue, int GPIO0,int GPIO1,int GPIO2,int GPIO3)
{
    int mask = 1;
    digitalWrite(GPIO0,(mask&&nibbleValue));
    digitalWrite(GPIO1,(mask&&(nibbleValue>>1)));
    digitalWrite(GPIO2,(mask&&(nibbleValue>>2)));
    digitalWrite(GPIO3,(mask&&(nibbleValue>>3)));
}
void togglePin(int pin)
{
    digitalWrite(pin,1);
    delay(1);
    digitalWrite(pin,0);
}
