EESchema Schematic File Version 2  date sam. 05 oct. 2013 20:48:26 CEST
LIBS:power
LIBS:device
LIBS:transistors
LIBS:conn
LIBS:linear
LIBS:regul
LIBS:74xx
LIBS:cmos4000
LIBS:adc-dac
LIBS:memory
LIBS:xilinx
LIBS:special
LIBS:microcontrollers
LIBS:dsp
LIBS:microchip
LIBS:analog_switches
LIBS:motorola
LIBS:texas
LIBS:intel
LIBS:audio
LIBS:interface
LIBS:digital-audio
LIBS:philips
LIBS:display
LIBS:cypress
LIBS:siliconi
LIBS:opto
LIBS:atmel
LIBS:contrib
LIBS:valves
LIBS:stm32f407zg
LIBS:sn65hvd232d
LIBS:ausbee-cache
EELAYER 25  0
EELAYER END
$Descr A4 11700 8267
encoding utf-8
Sheet 1 3
Title ""
Date "5 oct 2013"
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
Wire Wire Line
	6050 2350 5800 2350
Wire Wire Line
	6050 2550 5800 2550
$Sheet
S 6050 2150 550  650 
U 52505041
F0 "CAN" 60
F1 "CAN.sch" 60
F2 "R" I L 6050 2550 60 
F3 "D" I L 6050 2350 60 
$EndSheet
$Sheet
S 4250 2150 1550 1200
U 52002A3D
F0 "FP1_microcontroller" 60
F1 "FP1_microcontroller.sch" 60
F2 "CAN1_TX" I R 5800 2350 60 
F3 "CAN1_RX" I R 5800 2550 60 
$EndSheet
$EndSCHEMATC
