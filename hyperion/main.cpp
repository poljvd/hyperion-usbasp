#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <util/atomic.h>

#include <leddrv.h>

extern "C"
{
#include <usbdrv.h>
}

#include "hyperion.h"
#include "led.h"

#define MIN(X,Y)      ((X)<(Y) ? (X) : (Y))

extern "C"
{
/// Blink led function used as hook when receiving data over USB
void blinkLed()
{
	ledRedOn();
	_delay_ms(0.5);
	ledRedOff();
}
}

// global variables for receiving the led data
#define MAX_LED_COUNT   256 // limited by the available RAM
#define MAX_DATA_LENGTH (3*MAX_LED_COUNT)

static uint16_t dataLength = MAX_DATA_LENGTH;
static uint16_t receivedDataLength = 0;
static uint8_t ledData[MAX_DATA_LENGTH];
static void (*writeLeds)(uint16_t ledCount, const uint8_t * data) = NULL;

// callback function to receive a setup package
usbMsgLen_t usbFunctionSetup(uchar setupData[8])
{
	// cast to structured data for parsing
	usbRequest_t *request = reinterpret_cast<usbRequest_t *>(setupData);

	switch(request->bRequest)
	{
	case WRITE_LEDS_WS2801:
		// set the write led function
		writeLeds = &writeLedsWs2801;

		// store the data length
		dataLength = MIN(request->wLength.word, MAX_DATA_LENGTH);
		receivedDataLength = 0;
		return USB_NO_MSG;
	case WRITE_LEDS_WS2812:
		// set the write led function
		writeLeds = &writeLedsWs2812;

		// store the data length
		dataLength = MIN(request->wLength.word, MAX_DATA_LENGTH);
		receivedDataLength = 0;
		return USB_NO_MSG;
	}

	// ignore all unknown requests
	return 0;
}

// callback function to receive data
uchar usbFunctionWrite(uchar *data, uchar len)
{
	// copy the bytes
	memcpy(ledData + receivedDataLength, data, len);
	receivedDataLength += len;

	if (receivedDataLength != dataLength)
	{
		// wait for more data
		return 0;
	}

	// write the data to the leds
	writeLeds(dataLength/3, ledData);

	// return 1 to signal that we are finished
	return 1;
}

int main(void) {
	// set the led (PC0) as output
	DDRC = _BV(PC0);
	ledRedOff();

	// initialize the led output pins
	initLedPins();

	// disconnect from USB and reconnect after > 100ms to be sure
	// of re-enumeration of the device
	usbDeviceDisconnect();

	// wait for a while
	for (int i=0; i < 50; ++i) _delay_ms(10);

	// reconnect the usb
	usbDeviceConnect();

	// initialize the USB and enable interrupts
	usbInit();
	sei();

	// start polling the USB
	for (;;)
	{
		usbPoll();
	}

	return 0;
}
