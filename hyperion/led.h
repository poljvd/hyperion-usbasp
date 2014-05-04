#pragma once

#include <avr/io.h>

#define ledRedOn()    PORTC &= ~(1 << PC0)
#define ledRedOff()   PORTC |= (1 << PC0)
