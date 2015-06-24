Overview
============

Architecture Using STM32 By Eirbot ENSEIRB-MATMECA.
This tool is provided for building automatically a complete STM32F project.

Licence
=============

See LICENCE file.

Usage
=============

- git clone the repository or download the snapshot of the last version.
- If you choose the git clone method, it is recommended to use a tagged version (git checkout vX.X).
- Configure your board (type "make help" for further informations).
- write your source code in Project/src (headers and source files).
- run "make"
- run "make program" for downloading your code into your device.

For further informations, please visit our wiki : https://github.com/Kev-J/ausbee/wiki

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

Please see AUTHORS

Bugs, patch, requests
=============

https://github.com/Kev-J/ausbee
or
<ausbee@googlegroups.com>

Maintainer : Kevin JOLY <joly.kevin25@gmail.com>

Related to this project
=============

libausbee
-------------
https://github.com/Kev-J/libausbee

ausbee-hardware
-------------
https://github.com/Kev-J/ausbee-hardware
