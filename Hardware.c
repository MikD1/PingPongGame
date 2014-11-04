/*
* Hardware.c
*
* Created: 03.11.2014 19:46:40
* Author: Mikhail Doshevsky <m.doshevsky@gmail.com>
*/

#define F_CPU 1000000

#include <avr/io.h>
#include <util/delay.h>

#include "Hardware.h"
#include "Configuration.h"

const Pin LEDS[LEDS_COUNT] =
{
    { 0x17, 0x18, 5 },
    { 0x11, 0x12, 0 },
    { 0x11, 0x12, 1 },
    { 0x1A, 0x1B, 1 },
    { 0x1A, 0x1B, 0 },
    { 0x11, 0x12, 2 },
    { 0x11, 0x12, 3 },
    { 0x11, 0x12, 4 },
    { 0x11, 0x12, 5 },
    { 0x17, 0x18, 6 },
    { 0x17, 0x18, 4 },
    { 0x17, 0x18, 3 },
    { 0x11, 0x12, 6 },
    { 0x17, 0x18, 0 },
    { 0x17, 0x18, 2 }
};

ButtonPin P1_BUTTON = { 0x17, 0x18, 0x16, 7, 0 };
ButtonPin P2_BUTTON = { 0x17, 0x18, 0x16, 1, 0 };

void InitializeHardware(void)
{
    for (int i = 0; i < LEDS_COUNT; ++i)
    {
        _SFR_IO8(LEDS[i].DDR) |= (1 << LEDS[i].Bit);
    }
    
    _SFR_IO8(P1_BUTTON.DDR) &= ~(1 << P1_BUTTON.Bit);
    _SFR_IO8(P1_BUTTON.Port) |= (1 << P1_BUTTON.Bit);
    
    _SFR_IO8(P2_BUTTON.DDR) &= ~(1 << P2_BUTTON.Bit);
    _SFR_IO8(P2_BUTTON.Port) |= (1 << P2_BUTTON.Bit);
}

void LedOn(const Pin* pin)
{
    _SFR_IO8(pin->Port) |= (1 << pin->Bit);
}

void LedOff(const Pin* pin)
{
    _SFR_IO8(pin->Port) &= ~(1 << pin->Bit);
}

uint8_t IsButtonPressed(ButtonPin* pin)
{
    uint8_t result = 0;
    
    uint8_t buttonState = _SFR_IO8(pin->PinN) & (1 << pin->Bit);
    if (!pin->PreviousState && !buttonState)
    {
        _delay_ms(20);
        buttonState = _SFR_IO8(pin->PinN) & (1 << pin->Bit);
        if (!buttonState)
        {
            result = 1;
        }
    }
    
    buttonState = _SFR_IO8(pin->PinN) & (1 << pin->Bit);
    pin->PreviousState = !buttonState;
    
    return result;
}