hyperion-usbasp
===============

AVR program to turn an USBASP programmer into a WS2801/WS2812 led controller for use with [Hyperion](https://github.com/tvdzwan/hyperion).

WS2801
------
Use the following device configuration in Hyperion:
```
"device" :
{
  "name"       : "MyDevice",
  "type"       : "hyperion-usbasp-ws2801",
  "colorOrder" : "rgb"
},
```

WS2812
------
Use the following device configuration in Hyperion:
```
"device" :
{
  "name"       : "MyDevice",
  "type"       : "hyperion-usbasp-ws2812",
  "colorOrder" : "rgb"
},
```
