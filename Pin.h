/*
* PingPongGame.c
*
* Created: 03.11.2014 19:25:11
* Author: Mikhail Doshevsky <m.doshevsky@gmail.com>
*/

#ifndef PIN_H_
#define PIN_H_

#include <stdint.h>

typedef struct
{
    uint8_t DDR;
    uint8_t Port;
    uint8_t Bit;
} Pin;

typedef struct
{
    uint8_t DDR;
    uint8_t Port;
    uint8_t PinN;
    uint8_t Bit;
    uint8_t PreviousState;
} ButtonPin;

#endif /* PIN_H_ */
