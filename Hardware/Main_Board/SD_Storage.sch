EESchema Schematic File Version 2  date dim. 20 oct. 2013 18:50:44 CEST
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
LIBS:l298
LIBS:conn_4_jst
LIBS:conn_2_jst
LIBS:microsd_holder
LIBS:ausbee-cache
EELAYER 25  0
EELAYER END
$Descr A4 11700 8267
encoding utf-8
Sheet 5 6
Title ""
Date "20 oct 2013"
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
Wire Wire Line
	4000 3350 4400 3350
Wire Wire Line
	4400 3150 4350 3150
Wire Wire Line
	6600 3750 6600 3800
Wire Wire Line
	3850 3450 3850 3400
Wire Wire Line
	4350 3650 4400 3650
Wire Wire Line
	4400 3550 4350 3550
Wire Wire Line
	4350 3550 4350 3600
Wire Wire Line
	4350 4100 4350 4050
Wire Wire Line
	4350 4050 4400 4050
Wire Wire Line
	4350 3450 4400 3450
Wire Wire Line
	4400 3950 3700 3950
Connection ~ 3850 3950
Wire Wire Line
	6600 3350 6600 3300
Wire Wire Line
	5450 4450 5450 4400
Wire Wire Line
	4350 3250 4400 3250
NoConn ~ 4400 3050
Text HLabel 4350 3150 0    60   Input ~ 0
SS
$Comp
L GND #PWR142
U 1 1 525ECE80
P 5450 4450
F 0 "#PWR142" H 5450 4450 30  0001 C CNN
F 1 "GND" H 5450 4380 30  0001 C CNN
	1    5450 4450
	1    0    0    -1  
$EndComp
$Comp
L MICROSD_HOLDER U6
U 1 1 525ECE5E
P 5400 3600
F 0 "U6" H 5950 3000 60  0000 C CNN
F 1 "MICROSD_HOLDER" H 5600 3700 60  0000 C CNN
	1    5400 3600
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR144
U 1 1 525142D2
P 6600 3800
F 0 "#PWR144" H 6600 3800 30  0001 C CNN
F 1 "GND" H 6600 3730 30  0001 C CNN
	1    6600 3800
	1    0    0    -1  
$EndComp
$Comp
L +3.3V #PWR143
U 1 1 525142CF
P 6600 3300
F 0 "#PWR143" H 6600 3260 30  0001 C CNN
F 1 "+3.3V" H 6600 3410 30  0000 C CNN
	1    6600 3300
	1    0    0    -1  
$EndComp
$Comp
L C C34
U 1 1 525142CB
P 6600 3550
F 0 "C34" H 6650 3650 50  0000 L CNN
F 1 "100n" H 6650 3450 50  0000 L CNN
	1    6600 3550
	1    0    0    -1  
$EndComp
$Comp
L +3.3V #PWR138
U 1 1 525142AE
P 3850 3400
F 0 "#PWR138" H 3850 3360 30  0001 C CNN
F 1 "+3.3V" H 3850 3510 30  0000 C CNN
	1    3850 3400
	1    0    0    -1  
$EndComp
$Comp
L R R10
U 1 1 525142AC
P 3850 3700
F 0 "R10" V 3930 3700 50  0000 C CNN
F 1 "10k" V 3850 3700 50  0000 C CNN
	1    3850 3700
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR141
U 1 1 5251424F
P 4350 4100
F 0 "#PWR141" H 4350 4100 30  0001 C CNN
F 1 "GND" H 4350 4030 30  0001 C CNN
	1    4350 4100
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR140
U 1 1 52514242
P 4350 3600
F 0 "#PWR140" H 4350 3600 30  0001 C CNN
F 1 "GND" H 4350 3530 30  0001 C CNN
	1    4350 3600
	1    0    0    -1  
$EndComp
$Comp
L +3.3V #PWR139
U 1 1 52514239
P 4000 3350
F 0 "#PWR139" H 4000 3310 30  0001 C CNN
F 1 "+3.3V" H 4000 3460 30  0000 C CNN
	1    4000 3350
	1    0    0    -1  
$EndComp
NoConn ~ 4400 3750
Text HLabel 3700 3950 0    60   Input ~ 0
Card_Detect
Text HLabel 4350 3650 0    60   Input ~ 0
MISO
Text HLabel 4350 3450 0    60   Input ~ 0
SCK
Text HLabel 4350 3250 0    60   Input ~ 0
MOSI
$EndSCHEMATC
