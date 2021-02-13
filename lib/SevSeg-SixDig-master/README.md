# SevSeg-SixDig

With this library you can implement the same tasks as the original SevSeg library. In addition you can drive an NSA1166 7-seg 6 digit LED array [Inspired by 8bitkick's SevSegPlus] using an Arduino Nano, UNO, Mega, etc. (pretty much if you have enough pins) Below is one of the first tests driven by a Nano.

![Alt Text](https://github.com/tennercheung/SevSeg-SixDig/blob/master/examples/example.gif)

## Current Limitations

- Omits the segments of some numbers and letters usually the top left of the 7 seg
- Text must be typed as array of chars

## Hardware Setup

![Alt Text](https://github.com/tennercheung/SevSeg-SixDig/blob/master/examples/NS1166_fritzing_picture.png)

[Display I used]: NSA1166 7-seg 6 digit LED array (https://www.jameco.com/Jameco/Products/ProdDS/2210976NAT.pdf)

* NSA1166 with male headers
* inserted into breadboard
* 220 ohm+ resistors in series with the 6x cathodes 'digit'
* hooked up to Arduino Nano with jumper wires (see table below)
Pinout from Arduino to NSA1166 display

Use a 220ohm+ limiting resistor in series with each of these digit pins

|        |Arduino  | NSA1166|
| :------------- | :----------: | -----------: |
|digit1     |2     |Pin 2|
|digit2     |3     |Pin 8|
|digit3     |4     |Pin 10|
|digit4     |5     |Pin 12|
|digit5     |6     |Pin 14|
|digit6     |7     |Pin 16|

The segment pins are hooked directly to the Arduino Nano

| |Arduino  |NSA1166|
| :------------- | :----------: | -----------: |
|segA       |8     |Pin 7|
|segB       |9     |Pin 15|
|segC       |11    |Pin 3|
|segD       |13    |Pin 11|
|segE       |12    |Pin 9|
|segF       |18    |Pin 17|
|segG       |19    |Pin 13|
|segDP      |0     |Pin 5|


## Credits
-------------------
Based on: https://github.com/sparkfun/SevSeg and https://github.com/8bitkick/SevSegPlus

Original Library: http://arduino.cc/playground/Main/SevenSegmentLibrary

Improvements by Tenner Cheung, 2019
