# Ambilight multi-color effects for pinball machines

## Motivation and Summary

Goal of this project is to add ambilight multi-color effects to pinball machines. Instead of simple static colors we apply effects depending on the current game situation such as the active mission, running multiball or any other context.

From a hardware perspective we add LED strips below the cabinet and behind the backbox, both to the left and right side. The strips are controlled by a microcontroller, an Arduino Uno in this case.

The actual challenge of the project is to find out the current game situation. Unfortunately pinball manufacturers do not provide any APIs for their machines. The only way is to read the state of lamps, flashers and coils. For the latter two this could be  done directly via measuring the current from the corresponding board connectors. Accessing the multiplexed lamp matrix however seems to be hardly feasible.

Due to the fact not being an electronics engineer and in order not to disturb the sensitive pinball electronics we decided to simply read the state of lamps and flashers from below the playfield using photo sensors.

## Hardware

### LED strips

The Neopixel multi-color LED strips allow us to control each pixel individually and they can easily be programmed using a microcontroller with help of the Neopixel C++ library.

![Neopixel LED Strip][neopixelstrip]

We attach two long LED strips to either side below the cabinet and two shorter LED strips to either side behind the backbox:

![Backbox LED Strip][backboxledstrip]

The backbox strips are wired through the little hole on the top of the backbox which is present on all newer Stern pinball machines as a preparation for custom toppers. The undercab strips are wired through one of the holes at the rear of the cabinet.

The DIN (digital in) port is directly connected to a digital output port of the microcontroller. The power supply ports 5VDC and GND are connected to the 5V power supply unit.

### Photo Sensors

We use a LM393 board integrated with a photo sensor and a potentiometer.

![LM393 Photo Sensor][photosensor]

The sensor is placed below the playfield beneath the insert whose lighting state we want to read. The example shows how we placed sensors below the mission inserts of Star Trek.

![Playfield Sensors Details][playfieldsensorsdetails]

The potentiometers allow us to fine-tune the sensitivity of each photo sensor and avoid that any sensor is triggered erroneously from the lighting of a another nearby sensor.

![Playfield Sensors][playfieldsensors]

### Arduino Uno

The Arduino microcontroller is attached wtihin the backbox directly below the existing boards. Fortunately as we are modding a SAM system there is enough space there. We applied an additional shield with clamps for easy installation.

![Arduino][arduinoconnections]

We use 4 digital ports (10-13) to feed the Neopixel strips and 9 ports (1-9) to read the sensor outputs. For this showcase project the Arduino Uno provides us a sufficient number of ports but for larger scaled project with more sensors involved we may need to switch to an Arduino Mega.

### 5V Power Supply

We install a separate 5v power supply unit within the backbox and connect it directly to the 220V connector of the pinball machine.

![5V Power Supply][powersupply]

Both Arduino and LED strips are fed from this power supply. Note that one single Neopixel LED consumes up to 63mA which may result - as we install about 200 LEDs in this project - in a maximum of about 12A.

### Setup and Wiring

The complete backbox setup is shown below - it easily fits into the backbox of a SAM platform based machine. As usual I ran out of proper wire colors - that's the reason for the weird wiring.

![Backbox Setup][backboxwiring]

The wiring below the playfield is a challenge - we need to follow the already existing wiring paths.

![Playfield Wiring][playfieldwiring]

The bunch of cable for power supply and sensor signals is routed to the back of the playfield and further up to the backbox from below.

### Budget

Only branded product items from German shops were used. You may spend only a half or less of money if you fine-tune your expenses and buy clones from Fareast Asian shops.

Rough estimation:

- Arduino Uno microcontroller: 20 EUR
- Arduino shield: 10 EUR
- Neopixel strips: 20 EUR
- 5V power supply: 15 EUR
- Photo sensors, 9 pieces: 15 EUR
- Wiring and connectors: 15 EUR

Total budget around 95 EUR.

[powersupply]: https://github.com/reilo/flip4fun-neopixel/blob/main/pictures/5V-Power-Supply.jpg?raw=true

[arduinoconnections]: https://github.com/reilo/flip4fun-neopixel/blob/main/pictures/Arduino-Connections.jpg?raw=true

[backboxledstrip]: https://github.com/reilo/flip4fun-neopixel/blob/main/pictures/Backbox-LED-Strip.jpg?raw=true

[backboxwiring]: https://github.com/reilo/flip4fun-neopixel/blob/main/pictures/Backbox-Setup.jpg?raw=true

[photosensor]: https://github.com/reilo/flip4fun-neopixel/blob/main/pictures/LM393-Photo-Sensor.jpg?raw=true

[neopixelstrip]: https://github.com/reilo/flip4fun-neopixel/blob/main/pictures/Neopixel-Strip.jpg?raw=true

[playfieldsensors]: https://github.com/reilo/flip4fun-neopixel/blob/main/pictures/Playfield-Sensors.jpg?raw=true

[playfieldsensorsdetails]: https://github.com/reilo/flip4fun-neopixel/blob/main/pictures/Playfield-Sensors-Details.jpg?raw=true 

[playfieldwiring]: https://github.com/reilo/flip4fun-neopixel/blob/main/pictures/Playfield-Wiring-Challenge.jpg?raw=true

## Software

Under construction. For now refer to the source code.