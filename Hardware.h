/*
* Hardware.h
*
* Created: 03.11.2014 19:30:12
* Author: Mikhail Doshevsky <m.doshevsky@gmail.com>
*/

#ifndef HARDWARE_H_
#define HARDWARE_H_

#include "Configuration.h"
#include "Pin.h"

extern const Pin LEDS[LEDS_COUNT];
extern ButtonPin P1_BUTTON;
extern ButtonPin P2_BUTTON;

void InitializeHardware(void);
void LedOn(const Pin* pin);
void LedOff(const Pin* pin);
uint8_t IsButtonPressed(ButtonPin* pin);

#endif /* HARDWARE_H_ */