
# Christmas tree with LEDs ans Attiny4-5-9-10

## Getting Started

This is a christmas tree ornament that use an Attiny and 3 LEDs. The power is supplied by an CR2032 battery.



## Requirements


* Arduino IDE version 1.8.3 (The attine10 core is not working on higher versions)
* [ATtiny10Core](https://github.com/technoblogy/attiny10core)
* USBASP programmer(Need recent firmware, will probably require an update if bought from ebay)


See [here](http://www.technoblogy.com/show?1YQY) to learn how to install the required software and program the MCU.

## Building
### Programming

The PCB does not include a programming port. It is possible to use an external programmer with a socket, or use one of the PCB as the programmer. 
To do it:

 1. Solder wires to one PCB as seen in the images folder
 2. Plug the wires in one end of the programmer's cable
 3. Disconnect the cable from the programmer
 4. Place the IC on the PCB, at the right place and in the right direction, and hold it with one hand
 5. With the other hand, plug the wire in the programmer
 6. Program with the Arduino IDE
 7. Disconnect the programmer's cable

### Assembling
* Start with the MCU.
* Continue with the leds (D*) and the resistors (R*). For the leds, the small green dot is the negative side and it goes in the "white box".
* Solder the battery holder. The + side is at the top.

## BOM

* PCB (Printed Circuit Boards, order from OSHPark or another supplier)
* 3 * 0805 1kOhm resistors
* 3 * 0805 LED (different colors)
* 2032 battery holder (with distance between pins of 20mm)

## Possible improvements
* Real random LEDs pattern
* Add a small programming port
* Use a smaller battery so it is smaller than the board

## Author

* **Edward Rousseau** - *Initial work* - [Edward Rousseau](https://github.com/edwardrousseau)


## License

This project is licensed under the GPLv3 - see the [LICENSE](LICENSE) file for details
