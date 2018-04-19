//
// Created by chris on 07.02.2018.
//

#include <wiringPi.h>
#include "sipserv-structs.h"

int initPi(void);
void nibbleOutputGPIO(short, short, short, short, short);
void togglePin(short);
//AMK CHANGE THIS GITHUB
short dtmf_trigger = 0;
short dtmf_value = 0;


PI_THREAD (raspi_output)
{
    if (dtmf_trigger) {
        piLock(0);
        dtmf_trigger = 0;
        piUnlock(0);
        piLock(1);
        nibbleOutputGPIO(dtmf_value, app_cfg.gpio_port[0], app_cfg.gpio_port[1], app_cfg.gpio_port[2], app_cfg.gpio_port[3]);
        piUnlock(1);
        togglePin(app_cfg.interrupt_send_port);
    }
}

int initPi(void)
{
    wiringPiSetup();
    pinMode(app_cfg.gpio_port[0],OUTPUT);
    pinMode(app_cfg.gpio_port[1],OUTPUT);
    pinMode(app_cfg.gpio_port[2],OUTPUT);
    pinMode(app_cfg.gpio_port[3],OUTPUT);
    pinMode(app_cfg.interrupt_send_port,OUTPUT);
    int success = piThreadCreate(raspi_output);
    return success;
}
void nibbleOutputGPIO(short nibbleValue, short GPIO0,short GPIO1,short GPIO2,short GPIO3)
{
    unsigned short mask = 1;
    unsigned short temp = nibbleValue;
    digitalWrite(GPIO0,(mask&temp));
    temp = temp >> 1;
    digitalWrite(GPIO1,(mask&temp));
    temp = temp >> 1;
    digitalWrite(GPIO2,(mask&temp));
    temp = temp >> 1;
    digitalWrite(GPIO3,(mask&temp));
}
void togglePin(short pin)
{
    digitalWrite(pin,1);
    delay(1);
    digitalWrite(pin,0);
}
