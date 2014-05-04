
set(hyperion_HEADERS
	hyperion.h
	led.h
)

set(hyperion_SOURCES
	main.cpp
)

add_avr_executable(hyperion
	${hyperion_HEADERS}
	${hyperion_SOURCES}
)

# link libraries; NEEDS elf target as base!
target_link_libraries(hyperion-${AVR_MCU}.elf
	usbdrv-${AVR_MCU}
	leddrv-${AVR_MCU}
	light_ws2812-${AVR_MCU}
)
