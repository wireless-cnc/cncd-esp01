# CNCD-ESP01

Firmware project for Wireless CNC targeting ESP-01 board.

The firmware implements a simple WebSocket server that re-transmit all the messages from / to serial interface and WebSocket.


## Features

* Wifi connection configuration powered by WiFiManager library
    * The firmware starts a hotspot that allows to configure connection to your home WiFi network and then reboots
* mDNS server that allows CNC Controller app to discover the device