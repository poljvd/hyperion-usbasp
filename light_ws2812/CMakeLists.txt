
set(ws2812_HEADERS
	light_ws2812.h
	ws2812_config.h
)

set(ws2812_SOURCES
	light_ws2812.c
)

add_avr_library(light_ws2812
	${ws2812_HEADERS}
	${ws2812_SOURCES}
)
