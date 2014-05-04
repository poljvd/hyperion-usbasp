#include "leddrv.h"

extern "C"
{
#include "light_ws2812.h"
#include "ws2812_config.h"
}

#define PORT B
#define DDR DDRB
#define PIN_MOSI PB3
#define PIN_SCK PB5
#define PIN_SS PB2

void initLedPins()
{
	// set mosi, sck, and ss as output.
	DDR = _BV(PIN_MOSI) | _BV(PIN_SCK) | _BV(PIN_SS);
}

void enableSpi()
{
	// TODO: make the clock configurable
	// enable spi as master and set clock to fck/32 (12MHz / 32 = 375 kHz)
	SPSR = _BV(SPI2X);
	SPCR = _BV(SPE) | _BV(MSTR) | _BV(SPR1);
}

void disableSpi()
{
	SPCR = 0;
}

void writeSpi(uint16_t length, const uint8_t * data)
{
	for (uint16_t i = 0; i < length; ++i, ++data)
	{
		// start transmission by writing data in SPDR
		SPDR = *data;

		// wait until the transmission is finished
		while (!(SPSR & _BV(SPIF)));
	}
}

void writeLedsWs2801(uint16_t ledCount, const uint8_t * data)
{
	enableSpi();
	writeSpi(ledCount+ledCount+ledCount, data);
	disableSpi();
}

void writeLedsWs2812(uint16_t ledCount, const uint8_t * data)
{
	// Disable interrupts when writing to the ws2812 as it requires strict timing
	// This may however result in a USB pipe error...
	cli();
	ws2812_sendarray(const_cast<uint8_t *>(data), ledCount+ledCount+ledCount);
	sei();
}
