/*
* PingPongGame.c
*
* Created: 03.11.2014 19:17:32
* Author: Mikhail Doshevsky <m.doshevsky@gmail.com>
*/

#define F_CPU 1000000

#include <avr/io.h>
#include <util/delay.h>

#include "Configuration.h"
#include "Hardware.h"

const int CENTER_LED = LEDS_COUNT / 2;
const int WAIT_STEP = (MAX_WAIT_VALUE - MIN_WAIT_VALUE) / (LEDS_COUNT - 1);

int CurrentPosition;
uint8_t Direction = 1;
int WaitValue = MAX_WAIT_VALUE;

void HandleButtons(void);
void Finish(const Pin* led);

int main(void)
{
    InitializeHardware();
    
    CurrentPosition = CENTER_LED;
    LedOn(&LEDS[CurrentPosition]);
    _delay_ms(1000);
    
    while(1)
    {
        LedOff(&LEDS[CurrentPosition]);
        
        Direction ? ++CurrentPosition : --CurrentPosition;
        if (CurrentPosition < 0)
        {
            Finish(&LEDS[0]);
        }
        else if (CurrentPosition == LEDS_COUNT)
        {
            Finish(&LEDS[LEDS_COUNT - 1]);
        }
        else
        {
            LedOn(&LEDS[CurrentPosition]);
            for (int i = 0; i < WaitValue; ++i)
            {
                HandleButtons();
                _delay_ms(1);
            }
        }
    }
}

void HandleButtons(void)
{
    if (IsButtonPressed(&P1_BUTTON))
    {
        if (!Direction)
        {
            Direction = 1;
            WaitValue = MIN_WAIT_VALUE + CurrentPosition * WAIT_STEP;
        }
    }
    
    if (IsButtonPressed(&P2_BUTTON))
    {
        if (Direction)
        {
            Direction = 0;
            WaitValue = MIN_WAIT_VALUE + (LEDS_COUNT - CurrentPosition - 1) * WAIT_STEP;
        }
    }
}

void Finish(const Pin* led)
{
    for (int i = 0; i < LEDS_COUNT; ++i)
    {
        LedOff(&LEDS[i]);
    }
    
    while(1)
    {
        LedOn(led);
        _delay_ms(200);
        LedOff(led);
        _delay_ms(200);
    }
}