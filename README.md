# CNCD-ESP01

🔴 **WARNING** - the hardware / firmware of the project is not stable and has a showstopper issue https://github.com/wireless-cnc/cncd-esp01/issues/1


Firmware project for Wireless CNC targeting ESP-01 board.

The firmware implements a simple WebSocket server that re-transmit all the messages from / to serial interface and WebSocket.

## How to build

1. Install VSCode and PlatformIO. The latter will take care of downloading all necessary toolchains and libs.
2. Create ``.env`` file at the root of the repo.
3. Put the ``CNCD_HOTSPOT_PW=<password>`` into this file. That is a WiFi hot spot password you'll need to enter on first connect to the device.
2. Compile and flash firmware using PlatformIO.

## How to use it

1. Grab the ESP-01 board and flash it with firmware
2. Insert ESP-01 into the slot of the [cncd-esp01-board
](https://github.com/wireless-cnc/cncd-esp01-board), the arrow on the top side shows the direction of the ESP-01 antenna
3. Connect the board with the CNC Controller Board using [Offline Controller's cable](https://docs.sainsmart.com/article/zinzutpbhg-genmitsu-3018-pro-offline-controller-guide)
4. Power on CNC
5. Configure WiFi connection of CNCD 
6. Install and run [Wireless CNC Controller](https://github.com/wireless-cnc/cnc-controller/releases)
7. Now you can upload CNC job to controller and launch it!

## First launch

1. Device will start a WiFi hot spot called "WirelessCNC" protected with the password you specified in ``.env`` file before the build.
2. Connect to it from smartphone or other device.
3. Smartphone will show you are captive portal hosted by the device that will be asking you to select and then connect to your home WiFi network.
4. After selecting the network and entering password device will reboot and connect to your home network.
5. After that it becomes discoverable by [Wireless CNC Controller](https://github.com/wireless-cnc/cnc-controller/releases) app


## Features

* Wifi connection configuration powered by WiFiManager library
    * The firmware starts a hotspot that allows to configure connection to your home WiFi network and then reboots
* mDNS server that allows CNC Controller app to discover the device
