EESchema Schematic File Version 2  date dim. 06 oct. 2013 19:21:38 CEST
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
Sheet 1 5
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
	6050 3600 5800 3600
Wire Wire Line
	6050 3400 5800 3400
Wire Wire Line
	6050 2350 5800 2350
Wire Wire Line
	6050 2550 5800 2550
Wire Wire Line
	4300 1850 4150 1850
Wire Wire Line
	4150 1850 4150 2350
Wire Wire Line
	4150 2350 4250 2350
Wire Wire Line
	5800 3500 6050 3500
$Sheet
S 4300 850  1400 1100
U 525169A8
F0 "Power" 60
F1 "power.sch" 60
F2 "AX12_POWER" I L 4300 1850 60 
$EndSheet
$Sheet
S 6050 3050 900  700 
U 52514074
F0 "SD_Storage" 60
F1 "SD_Storage.sch" 60
F2 "Card_Detect" I L 6050 3150 60 
F3 "MISO" I L 6050 3500 60 
F4 "SCK" I L 6050 3400 60 
F5 "MOSI" I L 6050 3600 60 
F6 "SS" I L 6050 3300 60 
$EndSheet
$Sheet
S 6050 2150 550  650 
U 52505041
F0 "CAN" 60
F1 "CAN.sch" 60
F2 "R" I L 6050 2550 60 
F3 "D" I L 6050 2350 60 
$EndSheet
$Sheet
S 4250 2150 1550 2850
U 52002A3D
F0 "microcontroller" 60
F1 "microcontroller.sch" 60
F2 "CAN1_TX" I R 5800 2350 60 
F3 "CAN1_RX" I R 5800 2550 60 
F4 "enc4_B" I L 4250 4100 60 
F5 "enc4_A" I L 4250 4000 60 
F6 "enc3_B" I L 4250 3850 60 
F7 "enc3_A" I L 4250 3750 60 
F8 "enc2_B" I L 4250 3600 60 
F9 "enc2_A" I L 4250 3500 60 
F10 "enc1_B" I L 4250 3350 60 
F11 "enc1_A" I L 4250 3250 60 
F12 "PWM4" I L 4250 4600 60 
F13 "PWM3" I L 4250 4500 60 
F14 "PWM2" I L 4250 4400 60 
F15 "PWM1" I L 4250 4300 60 
F16 "AX12_POWER" I L 4250 2350 60 
F17 "SCK_SD" I R 5800 3400 60 
F18 "MOSI_SD" I R 5800 3600 60 
F19 "MISO_SD" I R 5800 3500 60 
$EndSheet
$EndSCHEMATC
