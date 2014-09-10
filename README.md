Overview
============

Architecture Using STM32 By Eirbot ENSEIRB-MATMECA.
This tool is provided for building automatically a complete STM32F project.

Licence
=============

You are free to use or modify this tool. Neither EIRBOT, or the authors will be held
responsible of any direct or indirect damages.

Usage
=============

- Configure your board (type "make help" for further informations).
- write your source code in Project/src (headers and source files).
- run "make"
- run "make program" for downloading your code into your device.

Features
=============

- FreeRTOS
- ST Std_Periph_Driver
- libausbee
- stm32flash

Dependencies
=============
gperf
flex
bison
libncurses-dev (for menuconfig)
wget
unzip
tar
stm32flash

Authors of the project
=============

Please read the file's headers.

Bugs, patch, requests
=============

https://github.com/Kev-J/ausbee

Maintainer : Kevin JOLY <joly.kevin25@gmail.com>

Related to this project
=============

libausbee
-------------
https://github.com/Kev-J/libausbee

ausbee-hardware
-------------
https://github.com/Kev-J/ausbee-hardware
