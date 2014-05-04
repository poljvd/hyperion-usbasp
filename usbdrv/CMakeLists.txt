


set(usbdrv_HEADERS
	usbconfig.h
	usbdrv.h
	usbportability.h
	oddebug.h
	
	asmcommon.inc
	usbdrvasm12.inc
	usbdrvasm128.inc
	usbdrvasm15.inc
	usbdrvasm16.inc
	usbdrvasm165.inc
	usbdrvasm18-crc.inc
	usbdrvasm20.inc
)

set(usbdrv_SOURCES
   usbdrv.c
   usbdrvasm.S
   oddebug.c
)

add_avr_library(usbdrv
	${usbdrv_HEADERS}
	${usbdrv_SOURCES}
)
