
set(leddrv_HEADERS
	leddrv.h
)

set(leddrv_SOURCES
	leddrv.cpp
)

add_avr_library(leddrv
	${leddrv_HEADERS}
	${leddrv_SOURCES}
)
