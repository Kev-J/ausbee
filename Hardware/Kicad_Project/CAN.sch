EESchema Schematic File Version 2  date dim. 06 oct. 2013 19:36:18 CEST
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
LIBS:sd_holder
LIBS:ap1117
LIBS:ausbee-cache
EELAYER 25  0
EELAYER END
$Descr A4 11700 8267
encoding utf-8
Sheet 2 5
Title ""
Date "6 oct 2013"
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
Wire Wire Line
	5300 4200 5300 4150
Wire Wire Line
	6350 2950 6350 3050
Wire Wire Line
	6350 2950 6950 2950
Wire Wire Line
	6950 2950 6950 3450
Wire Wire Line
	6350 3250 6350 3300
Wire Wire Line
	4750 3650 4700 3650
Wire Wire Line
	4750 3450 4650 3450
Connection ~ 6350 3800
Wire Wire Line
	6950 3650 6950 3800
Wire Wire Line
	6950 3800 6100 3800
Wire Wire Line
	5900 3550 6100 3550
Wire Wire Line
	6100 3550 6100 3800
Wire Wire Line
	5900 3450 6100 3450
Connection ~ 6350 3300
Wire Wire Line
	4650 3450 4650 3500
Wire Wire Line
	4750 3550 4500 3550
Wire Wire Line
	4700 3350 4750 3350
Wire Wire Line
	6100 3450 6100 3050
Wire Wire Line
	6100 3050 6350 3050
Wire Wire Line
	5300 4650 5300 4600
$Comp
L GND #PWR?
U 1 1 52505E54
P 5300 4650
F 0 "#PWR?" H 5300 4650 30  0001 C CNN
F 1 "GND" H 5300 4580 30  0001 C CNN
	1    5300 4650
	1    0    0    -1  
$EndComp
$Comp
L +3.3V #PWR?
U 1 1 52505E50
P 5300 4150
F 0 "#PWR?" H 5300 4110 30  0001 C CNN
F 1 "+3.3V" H 5300 4260 30  0000 C CNN
	1    5300 4150
	1    0    0    -1  
$EndComp
$Comp
L C C?
U 1 1 52505E43
P 5300 4400
F 0 "C?" H 5350 4500 50  0000 L CNN
F 1 "100n" H 5350 4300 50  0000 L CNN
	1    5300 4400
	1    0    0    -1  
$EndComp
$Comp
L CONN_2 P?
U 1 1 52505DE1
P 6700 3150
F 0 "P?" V 6650 3150 40  0000 C CNN
F 1 "CONN_2" V 6750 3150 40  0000 C CNN
	1    6700 3150
	1    0    0    -1  
$EndComp
Text HLabel 4700 3650 0    60   Input ~ 0
R
Text HLabel 4700 3350 0    60   Input ~ 0
D
$Comp
L +3.3V #PWR?
U 1 1 52505D30
P 4500 3550
F 0 "#PWR?" H 4500 3510 30  0001 C CNN
F 1 "+3.3V" H 4500 3660 30  0000 C CNN
	1    4500 3550
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR?
U 1 1 52505D28
P 4650 3500
F 0 "#PWR?" H 4650 3500 30  0001 C CNN
F 1 "GND" H 4650 3430 30  0001 C CNN
	1    4650 3500
	1    0    0    -1  
$EndComp
$Comp
L CONN_2 P?
U 1 1 52505D1B
P 7300 3550
F 0 "P?" V 7250 3550 40  0000 C CNN
F 1 "CONN_2" V 7350 3550 40  0000 C CNN
	1    7300 3550
	1    0    0    -1  
$EndComp
$Comp
L R R?
U 1 1 52505D04
P 6350 3550
F 0 "R?" V 6430 3550 50  0000 C CNN
F 1 "120" V 6350 3550 50  0000 C CNN
	1    6350 3550
	1    0    0    -1  
$EndComp
$Comp
L SN65HVD232D U?
U 1 1 52505CC2
P 5300 3500
F 0 "U?" H 5750 3200 60  0000 C CNN
F 1 "SN65HVD232D" H 5300 3800 60  0000 C CNN
	1    5300 3500
	1    0    0    -1  
$EndComp
$EndSCHEMATC
