#pragma once

#include <stdint.h>

void initLedPins();

void writeLedsWs2801(uint16_t ledCount, const uint8_t * data);
void writeLedsWs2812(uint16_t ledCount, const uint8_t * data);
