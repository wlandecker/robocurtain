# robocurtain
Source code for an arduino-controlled circuit that opens or closes my curtain depending on an opened / closed switch on my desk.

## parts
* [Adafruit Metro Mini](https://www.adafruit.com/product/2590) (or other Arduino-type controller)
* [A4988](https://www.pololu.com/product/1182) or other Arduino-compatible stepper motor driver
* A stepper motor that can be driven by the driver. I used a NEMA-17 motor like [this one](https://www.adafruit.com/product/324?gclid=Cj0KCQjw78yFBhCZARIsAOxgSx3dNbwpMxdGpMKO2eSwk9kavhkuKxqNSe1BPVoUfb8XnATOi6yRQY0aAtBJEALw_wcB)
* SPST switch
* Compatible [timing belt](https://www.adafruit.com/product/1184), [cogs](https://www.adafruit.com/product/1253), and ball bearings.
* 12V power supply with enough amps to drive the motor and processor at the same time.
* Miscellaneous resistors, capacitors, wires.

## circuit
TODO: find a good circuit drawing tool online.

In the meantime, here's a quick description of the circuit. The switch provides an open (0V) or closed (5V) signal to the arduino. When the arduino registers a change in the switch's state, it tells the stepper motor driver to run the motor in order to open or close the curtain.

The 12V supply powers both the motor (through the stepper motor driver) and the arduino (via the `Vin` pin). In order to prevent the motor's high inductance from messing with the arduino supply, put two electrolytic capacitors (one larger, one smaller) between the `Vin` and `Gnd` pins of the arduino. Use a [pull-up resistor](https://learn.sparkfun.com/tutorials/pull-up-resistors/all) to make sure that the switch cycles the input between 0V and 5V.
