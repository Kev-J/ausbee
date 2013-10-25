EESchema Schematic File Version 2
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
LIBS:stm32f103c4
LIBS:ap1117
LIBS:conn_2_jst
LIBS:conn_4_jst
LIBS:sn65hvd232d
LIBS:serv_module-cache
EELAYER 27 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 2 4
Title ""
Date "25 oct 2013"
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
Text Notes 4500 4450 0    40   ~ 0
5V
Text Notes 4400 3200 0    40   ~ 0
9V
Connection ~ 5100 5450
Wire Wire Line
	5100 5500 5100 5450
Wire Wire Line
	5200 5000 5200 5050
Wire Wire Line
	4800 2350 4800 2300
Wire Wire Line
	7300 3250 7350 3250
Wire Wire Line
	4950 2700 4950 2750
Connection ~ 5400 3250
Wire Wire Line
	4850 3250 5450 3250
Wire Wire Line
	5400 3750 5400 3700
Wire Wire Line
	6700 3700 6700 3750
Wire Wire Line
	6050 3750 6050 3850
Connection ~ 6050 3750
Wire Wire Line
	6700 3250 6700 3300
Wire Wire Line
	5400 3300 5400 3250
Wire Wire Line
	4850 3450 4850 3750
Wire Wire Line
	4850 3750 6700 3750
Connection ~ 5400 3750
Wire Wire Line
	4950 4700 5000 4700
Wire Wire Line
	6800 3250 6650 3250
Connection ~ 6700 3250
Wire Wire Line
	7350 3650 7350 3700
Wire Wire Line
	4800 2300 4950 2300
Wire Wire Line
	5250 4500 4950 4500
Connection ~ 5200 4500
Wire Wire Line
	5000 4700 5000 5450
Wire Wire Line
	5000 5450 5200 5450
$Comp
L LED D3
U 1 1 52613CD7
P 5200 5250
F 0 "D3" H 5200 5350 50  0000 C CNN
F 1 "LED" H 5200 5150 50  0000 C CNN
F 2 "" H 5200 5250 60  0001 C CNN
F 3 "" H 5200 5250 60  0001 C CNN
	1    5200 5250
	0    1    1    0   
$EndComp
$Comp
L R R4
U 1 1 52613CBA
P 5200 4750
F 0 "R4" V 5280 4750 50  0000 C CNN
F 1 "330" V 5200 4750 50  0000 C CNN
F 2 "" H 5200 4750 60  0001 C CNN
F 3 "" H 5200 4750 60  0001 C CNN
	1    5200 4750
	-1   0    0    1   
$EndComp
$Comp
L GND #PWR?
U 1 1 52613C2B
P 7350 3700
F 0 "#PWR?" H 7350 3700 30  0001 C CNN
F 1 "GND" H 7350 3630 30  0001 C CNN
F 2 "" H 7350 3700 60  0001 C CNN
F 3 "" H 7350 3700 60  0001 C CNN
	1    7350 3700
	1    0    0    -1  
$EndComp
$Comp
L LED D2
U 1 1 52613C23
P 7350 3450
F 0 "D2" H 7350 3550 50  0000 C CNN
F 1 "LED" H 7350 3350 50  0000 C CNN
F 2 "" H 7350 3450 60  0001 C CNN
F 3 "" H 7350 3450 60  0001 C CNN
	1    7350 3450
	0    1    1    0   
$EndComp
$Comp
L R R3
U 1 1 52613C1D
P 7050 3250
F 0 "R3" V 7130 3250 50  0000 C CNN
F 1 "220" V 7050 3250 50  0000 C CNN
F 2 "" H 7050 3250 60  0001 C CNN
F 3 "" H 7050 3250 60  0001 C CNN
	1    7050 3250
	0    1    1    0   
$EndComp
$Comp
L GND #PWR?
U 1 1 52613B24
P 4800 2350
F 0 "#PWR?" H 4800 2350 30  0001 C CNN
F 1 "GND" H 4800 2280 30  0001 C CNN
F 2 "" H 4800 2350 60  0001 C CNN
F 3 "" H 4800 2350 60  0001 C CNN
	1    4800 2350
	1    0    0    -1  
$EndComp
$Comp
L LED D1
U 1 1 52613B17
P 4950 2500
F 0 "D1" H 4950 2600 50  0000 C CNN
F 1 "LED" H 4950 2400 50  0000 C CNN
F 2 "" H 4950 2500 60  0001 C CNN
F 3 "" H 4950 2500 60  0001 C CNN
	1    4950 2500
	0    -1   -1   0   
$EndComp
$Comp
L R R2
U 1 1 52613B05
P 4950 3000
F 0 "R2" V 5030 3000 50  0000 C CNN
F 1 "820" V 4950 3000 50  0000 C CNN
F 2 "" H 4950 3000 60  0001 C CNN
F 3 "" H 4950 3000 60  0001 C CNN
	1    4950 3000
	1    0    0    -1  
$EndComp
Text Notes 4500 4300 0    80   ~ 0
SERVO_POWER_IN
Text Notes 5700 2900 0    80   ~ 0
9V_TO_3.3V
Text HLabel 5250 4500 2    40   Input ~ 0
SERVO_POWER
$Comp
L GND #PWR?
U 1 1 526136B4
P 5100 5500
F 0 "#PWR?" H 5100 5500 30  0001 C CNN
F 1 "GND" H 5100 5430 30  0001 C CNN
F 2 "" H 5100 5500 60  0001 C CNN
F 3 "" H 5100 5500 60  0001 C CNN
	1    5100 5500
	1    0    0    -1  
$EndComp
$Comp
L CONN_2 P3
U 1 1 526136A8
P 4600 4600
F 0 "P3" V 4550 4600 40  0000 C CNN
F 1 "CONN_2" V 4650 4600 40  0000 C CNN
F 2 "" H 4600 4600 60  0001 C CNN
F 3 "" H 4600 4600 60  0001 C CNN
	1    4600 4600
	-1   0    0    -1  
$EndComp
$Comp
L CONN_2 P2
U 1 1 52613672
P 4500 3350
F 0 "P2" V 4450 3350 40  0000 C CNN
F 1 "CONN_2" V 4550 3350 40  0000 C CNN
F 2 "" H 4500 3350 60  0001 C CNN
F 3 "" H 4500 3350 60  0001 C CNN
	1    4500 3350
	-1   0    0    -1  
$EndComp
$Comp
L AP1117 U?
U 1 1 52613406
P 6050 3250
F 0 "U?" H 6300 2900 60  0000 C CNN
F 1 "AP1117" H 6000 3400 60  0000 C CNN
F 2 "" H 6050 3250 60  0001 C CNN
F 3 "" H 6050 3250 60  0001 C CNN
	1    6050 3250
	1    0    0    -1  
$EndComp
$Comp
L +3.3V #PWR?
U 1 1 526135E7
P 6700 3250
F 0 "#PWR?" H 6700 3210 30  0001 C CNN
F 1 "+3.3V" H 6700 3360 30  0000 C CNN
F 2 "" H 6700 3250 60  0001 C CNN
F 3 "" H 6700 3250 60  0001 C CNN
	1    6700 3250
	1    0    0    -1  
$EndComp
$Comp
L CP 22u
U 1 1 526135C0
P 6700 3500
F 0 "22u" H 6750 3600 50  0000 L CNN
F 1 "CP2" H 6750 3400 50  0000 L CNN
F 2 "" H 6700 3500 60  0001 C CNN
F 3 "" H 6700 3500 60  0001 C CNN
	1    6700 3500
	1    0    0    -1  
$EndComp
$Comp
L CP 10u
U 1 1 526135BB
P 5400 3500
F 0 "10u" H 5450 3600 50  0000 L CNN
F 1 "CP1" H 5450 3400 50  0000 L CNN
F 2 "" H 5400 3500 60  0001 C CNN
F 3 "" H 5400 3500 60  0001 C CNN
	1    5400 3500
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR?
U 1 1 52613414
P 6050 3850
F 0 "#PWR?" H 6050 3850 30  0001 C CNN
F 1 "GND" H 6050 3780 30  0001 C CNN
F 2 "" H 6050 3850 60  0001 C CNN
F 3 "" H 6050 3850 60  0001 C CNN
	1    6050 3850
	1    0    0    -1  
$EndComp
$EndSCHEMATC
