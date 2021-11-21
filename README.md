## SPD Enclosure based PowerMonitor - 2 DIN Modules - Single/Three Phase

## Table of contents

* [Built with](#built-with)
* [Software used](#dependencies)
* [Directory structure](#directory-structure)
* [Flash instructions](#flash-instructions)
* [Running tests](#running-tests)
* [Hardware Design](#hardware-design)

## Built with <a name="built-with"></a>

* [ESP-IDF](https://www.espressif.com/en/products/sdks/esp-idf)

## Software used <a name="dependencies"></a>

* [ESP-IDF Toolchain](https://www.espressif.com/en/products/sdks/esp-idf)
* [CMake](https://cmake.org/download/)
* [Arduino ADE9153a](https://github.com/analogdevicesinc/arduino/tree/master/Arduino%20Uno%20R3/libraries/ADE9153A)
* [minfft](https://github.com/aimukhin/minfft)
* [fmtlib](https://github.com/fmtlib/fmt)
* [Microsoft GSL](https://github.com/microsoft/GSL)

## Directory structure <a name="directory-structure"></a>

* `3rdparty`: Third party code and dependencies
* `cmake`: Additional CMake scripts used to configure and build the project
* `data`: Resources embedded in the final binary
* `hardware_design`: Hardware design files
* `main`: ESP IDF component
* `src`: Source code
* `src/include`: Header files
* `test`: Unit tests (meant to be run on PC)

## Flash instructions <a name="flash-instructions"></a>

After setting up the ESP IDF build environment and making sure the tools are available in your PATH, run:

```
idf.py build # Build the source code
idf.py -p <port> flash
idf.py -p <port> monitor
```

## Running tests <a name="running-tests"></a>

Make sure you have CMake and CTest available in your PATH and a C and C++ compiler available.

Run:

```
mkdir build && cd build
cmake .. && cmake --build .
ctest
```

## Hardware Design <a name="hardware-design"></a>

Design files for PowerMonitor hardware for development:

* SPD_PowerMonitor-AFE - board containing the analog frontend and isolation barrier
* SPD_PowerMonitor-Controller - board containing the ESP32 MCU with RS485 and USB for software debugging

Characteristics:

* Designed to fit into a 2 DIN Module SPD base enclosure
* Instead of Ethernet and 24V AC power the controller has a USB transciever chip to ease development
* Powered by USB 5V DC
* Breakout headers for internal SPI bus in order to experiment with external RAM
* Breakout headers for I2C bus to add ST NFC module for configuration loading
* Shunt mounted directly on the SPD spade plugs

**Notes**

From software side this is the final design, any changes to hardware should be transparent to software. On hardware
side, because of chip shortages and especially the low availability of the isolated power supply for the AFE, this
design will have to be modified to use other ICs that are available. Analog FE will not change.
