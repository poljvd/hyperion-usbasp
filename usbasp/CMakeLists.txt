
set(usbasp_HEADERS
    clock.h
    isp.h
    tpi_defs.h
    tpi.h
    usbasp.h
)

set(usbasp_SOURCES
    main.cpp
	clock.c
	isp.c
	tpi.S
)

add_avr_executable(usbasp
   ${usbasp_HEADERS}
   ${usbasp_SOURCES}
)

# link libraries; NEEDS elf target as base!
target_link_libraries(usbasp-${AVR_MCU}.elf
	usbdrv-${AVR_MCU}
	light_ws2812-${AVR_MCU}
	leddrv-${AVR_MCU}
)
