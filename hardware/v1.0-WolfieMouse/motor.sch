EESchema Schematic File Version 2
LIBS:components_micromouse
LIBS:power
LIBS:transistors
LIBS:device
LIBS:conn
LIBS:linear
LIBS:regul
LIBS:74xx
LIBS:cmos4000
LIBS:adc-dac
LIBS:memory
LIBS:xilinx
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
LIBS:pcb1
LIBS:micromouse-cache
EELAYER 25 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 2 4
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L MAX14871 U2
U 1 1 56EB63E4
P 4300 2950
F 0 "U2" H 3950 3400 60  0000 C CNN
F 1 "MAX14871" H 3900 2400 60  0000 C CNN
F 2 "footprints_micromouse:TSSOP-16_EP" H 4950 3200 60  0001 C CNN
F 3 "" H 4950 3200 60  0000 C CNN
	1    4300 2950
	1    0    0    -1  
$EndComp
$Comp
L MAX14871 U3
U 1 1 56EB6417
P 4300 5100
F 0 "U3" H 3950 5550 60  0000 C CNN
F 1 "MAX14871" H 3900 4550 60  0000 C CNN
F 2 "footprints_micromouse:TSSOP-16_EP" H 4950 5350 60  0001 C CNN
F 3 "" H 4950 5350 60  0000 C CNN
	1    4300 5100
	1    0    0    -1  
$EndComp
$Comp
L MOTOR_MOUNTS_AND_ENCODERS M1
U 1 1 56EB6456
P 7450 3900
F 0 "M1" H 6550 4600 45  0001 C CNN
F 1 "MOTOR_MOUNTS_AND_ENCODERS" H 7400 4350 50  0000 C CNN
F 2 "footprints_micromouse:FUTURA-1.0-MOTOR-MOUNT-TEMPLATE" H 8100 4600 20  0001 C CNN
F 3 "" H 7450 3850 60  0000 C CNN
	1    7450 3900
	0    1    1    0   
$EndComp
Wire Wire Line
	4850 4800 5000 4800
Wire Wire Line
	5000 4800 5000 4900
Wire Wire Line
	4850 4900 6900 4900
Connection ~ 5000 4900
Wire Wire Line
	5000 5000 6900 5000
Wire Wire Line
	4850 2650 4950 2650
Wire Wire Line
	4950 2650 4950 2800
Wire Wire Line
	4950 2800 6900 2800
Wire Wire Line
	4850 2750 4950 2750
Connection ~ 4950 2750
Wire Wire Line
	4850 2900 6900 2900
Wire Wire Line
	4850 3000 4950 3000
Wire Wire Line
	4950 3000 4950 2900
Connection ~ 4950 2900
Wire Wire Line
	5000 5000 5000 5150
Wire Wire Line
	5000 5050 4850 5050
Wire Wire Line
	5000 5150 4850 5150
Connection ~ 5000 5050
$Comp
L GND #PWR035
U 1 1 56EB8B5A
P 6700 4650
F 0 "#PWR035" H 6700 4400 50  0001 C CNN
F 1 "GND" H 6700 4500 50  0000 C CNN
F 2 "" H 6700 4650 50  0000 C CNN
F 3 "" H 6700 4650 50  0000 C CNN
	1    6700 4650
	1    0    0    -1  
$EndComp
Wire Wire Line
	6900 3250 6600 3250
Wire Wire Line
	6600 3200 6600 4100
Wire Wire Line
	6600 4100 6900 4100
Connection ~ 6600 3250
Wire Wire Line
	6700 3350 6700 4650
Wire Wire Line
	6700 4200 6900 4200
Wire Wire Line
	6700 3350 6900 3350
Connection ~ 6700 4200
Text HLabel 6400 3600 0    60   BiDi ~ 0
L_CHA
Text HLabel 6400 3700 0    60   BiDi ~ 0
L_CHB
Text HLabel 6400 4450 0    60   BiDi ~ 0
R_CHA
Text HLabel 6400 4550 0    60   BiDi ~ 0
R_CHB
Wire Wire Line
	6400 3600 6900 3600
Wire Wire Line
	6900 3700 6400 3700
Wire Wire Line
	6400 4450 6900 4450
Wire Wire Line
	6900 4550 6400 4550
Text HLabel 3400 2650 0    60   BiDi ~ 0
L_PWM
Text HLabel 3400 2750 0    60   BiDi ~ 0
L_DIR
Text HLabel 3400 2850 0    60   BiDi ~ 0
~L_FAULT
Text HLabel 3450 4800 0    60   BiDi ~ 0
R_PWM
Text HLabel 3450 4900 0    60   BiDi ~ 0
R_DIR
Text HLabel 3450 5000 0    60   BiDi ~ 0
~R_FAULT
$Comp
L +BATT #PWR036
U 1 1 56EB8FD2
P 4250 2000
F 0 "#PWR036" H 4250 1850 50  0001 C CNN
F 1 "+BATT" H 4250 2140 50  0000 C CNN
F 2 "" H 4250 2000 50  0000 C CNN
F 3 "" H 4250 2000 50  0000 C CNN
	1    4250 2000
	1    0    0    -1  
$EndComp
$Comp
L +5V #PWR037
U 1 1 56EC1082
P 6600 3200
F 0 "#PWR037" H 6600 3050 50  0001 C CNN
F 1 "+5V" H 6600 3340 50  0000 C CNN
F 2 "" H 6600 3200 50  0000 C CNN
F 3 "" H 6600 3200 50  0000 C CNN
	1    6600 3200
	1    0    0    -1  
$EndComp
Text Notes 4400 1550 0    200  ~ 40
Motors & Encoders
$Comp
L C_Small C_MOTOR1
U 1 1 56ED6CB6
P 4550 2250
F 0 "C_MOTOR1" H 4560 2320 50  0000 L CNN
F 1 "1uF" H 4570 2170 50  0000 L CNN
F 2 "Capacitors_SMD:C_0603" H 4550 2250 50  0001 C CNN
F 3 "" H 4550 2250 50  0000 C CNN
	1    4550 2250
	0    -1   -1   0   
$EndComp
Connection ~ 4350 2250
Wire Wire Line
	4650 2250 4800 2250
Wire Wire Line
	4800 2250 4800 2350
Wire Wire Line
	4250 2000 4250 2350
$Comp
L +BATT #PWR038
U 1 1 56ED705F
P 4250 4150
F 0 "#PWR038" H 4250 4000 50  0001 C CNN
F 1 "+BATT" H 4250 4290 50  0000 C CNN
F 2 "" H 4250 4150 50  0000 C CNN
F 3 "" H 4250 4150 50  0000 C CNN
	1    4250 4150
	1    0    0    -1  
$EndComp
$Comp
L C_Small C_MOTOR2
U 1 1 56ED7065
P 4550 4400
F 0 "C_MOTOR2" H 4560 4470 50  0000 L CNN
F 1 "1uF" H 4570 4320 50  0000 L CNN
F 2 "Capacitors_SMD:C_0603" H 4550 4400 50  0001 C CNN
F 3 "" H 4550 4400 50  0000 C CNN
	1    4550 4400
	0    -1   -1   0   
$EndComp
Connection ~ 4350 4400
Wire Wire Line
	4650 4400 4800 4400
Wire Wire Line
	4800 4400 4800 4500
Wire Wire Line
	4250 4150 4250 4500
Connection ~ 4250 2250
Wire Wire Line
	4350 2250 4350 2350
Connection ~ 4250 4400
Wire Wire Line
	4350 4400 4350 4500
Wire Wire Line
	3700 2850 3400 2850
Wire Wire Line
	3400 2750 3700 2750
Wire Wire Line
	3700 2650 3400 2650
$Comp
L R_Small R_MOTOR1
U 1 1 56ED74EF
P 3550 2450
F 0 "R_MOTOR1" V 3490 2360 50  0000 L CNN
F 1 "10k" V 3610 2360 50  0000 L CNN
F 2 "Resistors_SMD:R_0603" H 3550 2450 50  0001 C CNN
F 3 "" H 3550 2450 50  0000 C CNN
	1    3550 2450
	1    0    0    -1  
$EndComp
Wire Wire Line
	3550 2100 3550 2350
Wire Wire Line
	3550 2550 3550 2850
Connection ~ 3550 2850
$Comp
L R_Small R_MOTOR2
U 1 1 56ED76B9
P 3600 4600
F 0 "R_MOTOR2" V 3540 4510 50  0000 L CNN
F 1 "10k" V 3660 4510 50  0000 L CNN
F 2 "Resistors_SMD:R_0603" H 3600 4600 50  0001 C CNN
F 3 "" H 3600 4600 50  0000 C CNN
	1    3600 4600
	1    0    0    -1  
$EndComp
Wire Wire Line
	3450 4800 3700 4800
Wire Wire Line
	3700 4900 3450 4900
Wire Wire Line
	3450 5000 3700 5000
Connection ~ 3600 5000
Wire Wire Line
	3600 4300 3600 4500
Wire Wire Line
	3600 4700 3600 5000
$Comp
L GND #PWR039
U 1 1 56ED82CD
P 3550 3400
F 0 "#PWR039" H 3550 3150 50  0001 C CNN
F 1 "GND" H 3550 3250 50  0000 C CNN
F 2 "" H 3550 3400 50  0000 C CNN
F 3 "" H 3550 3400 50  0000 C CNN
	1    3550 3400
	1    0    0    -1  
$EndComp
Wire Wire Line
	3700 3300 3550 3300
Wire Wire Line
	3550 2950 3550 3400
$Comp
L +3.3V #PWR040
U 1 1 56ED83FC
P 3150 3350
F 0 "#PWR040" H 3150 3200 50  0001 C CNN
F 1 "+3.3V" H 3150 3490 50  0000 C CNN
F 2 "" H 3150 3350 50  0000 C CNN
F 3 "" H 3150 3350 50  0000 C CNN
	1    3150 3350
	1    0    0    -1  
$EndComp
Wire Wire Line
	3150 3350 3150 3450
Wire Wire Line
	3150 3450 3350 3450
Wire Wire Line
	3350 3450 3350 3200
Wire Wire Line
	3350 3200 3700 3200
Wire Wire Line
	3700 2950 3550 2950
Connection ~ 3550 3300
Wire Wire Line
	4300 3750 4300 3650
$Comp
L R_Small R13
U 1 1 56ED8689
P 5000 3500
F 0 "R13" V 4940 3410 50  0000 L CNN
F 1 "62.5m" V 5060 3410 50  0000 L CNN
F 2 "Resistors_SMD:R_0603" H 5000 3500 50  0001 C CNN
F 3 "" H 5000 3500 50  0000 C CNN
	1    5000 3500
	1    0    0    -1  
$EndComp
Wire Wire Line
	4850 3350 5000 3350
Wire Wire Line
	5000 3150 5000 3400
Wire Wire Line
	4850 3250 4900 3250
Wire Wire Line
	4900 3250 4900 3350
Connection ~ 4900 3350
Wire Wire Line
	5000 3600 5000 3700
Wire Wire Line
	5000 3700 4300 3700
Connection ~ 4300 3700
Wire Wire Line
	4850 3150 5000 3150
Connection ~ 5000 3350
$Comp
L R_Small R14
U 1 1 56ED90B0
P 5000 5650
F 0 "R14" V 4940 5560 50  0000 L CNN
F 1 "62.5m" V 5060 5560 50  0000 L CNN
F 2 "Resistors_SMD:R_0603" H 5000 5650 50  0001 C CNN
F 3 "" H 5000 5650 50  0000 C CNN
	1    5000 5650
	1    0    0    -1  
$EndComp
Wire Wire Line
	4850 5500 5000 5500
Wire Wire Line
	5000 5300 5000 5550
Wire Wire Line
	4850 5400 4900 5400
Wire Wire Line
	4900 5400 4900 5500
Connection ~ 4900 5500
Wire Wire Line
	5000 5750 5000 5850
Wire Wire Line
	4850 5300 5000 5300
Connection ~ 5000 5500
Wire Wire Line
	4300 5800 4300 5950
Wire Wire Line
	5000 5850 4300 5850
Connection ~ 4300 5850
$Comp
L GND #PWR041
U 1 1 56ED9574
P 3550 5550
F 0 "#PWR041" H 3550 5300 50  0001 C CNN
F 1 "GND" H 3550 5400 50  0000 C CNN
F 2 "" H 3550 5550 50  0000 C CNN
F 3 "" H 3550 5550 50  0000 C CNN
	1    3550 5550
	1    0    0    -1  
$EndComp
Wire Wire Line
	3700 5450 3550 5450
Wire Wire Line
	3550 5100 3550 5550
$Comp
L +3.3V #PWR042
U 1 1 56ED957C
P 3150 5500
F 0 "#PWR042" H 3150 5350 50  0001 C CNN
F 1 "+3.3V" H 3150 5640 50  0000 C CNN
F 2 "" H 3150 5500 50  0000 C CNN
F 3 "" H 3150 5500 50  0000 C CNN
	1    3150 5500
	1    0    0    -1  
$EndComp
Wire Wire Line
	3150 5500 3150 5600
Wire Wire Line
	3150 5600 3350 5600
Wire Wire Line
	3350 5600 3350 5350
Wire Wire Line
	3350 5350 3700 5350
Wire Wire Line
	3700 5100 3550 5100
Connection ~ 3550 5450
$Comp
L GNDM #PWR043
U 1 1 56FA27B2
P 4300 3750
F 0 "#PWR043" H 4300 3500 50  0001 C CNN
F 1 "GNDM" H 4300 3600 50  0000 C CNN
F 2 "" H 4300 3750 50  0000 C CNN
F 3 "" H 4300 3750 50  0000 C CNN
	1    4300 3750
	1    0    0    -1  
$EndComp
$Comp
L GNDM #PWR044
U 1 1 56FA283F
P 4300 5950
F 0 "#PWR044" H 4300 5700 50  0001 C CNN
F 1 "GNDM" H 4300 5800 50  0000 C CNN
F 2 "" H 4300 5950 50  0000 C CNN
F 3 "" H 4300 5950 50  0000 C CNN
	1    4300 5950
	1    0    0    -1  
$EndComp
$Comp
L GNDM #PWR045
U 1 1 57019AE9
P 4800 4500
F 0 "#PWR045" H 4800 4250 50  0001 C CNN
F 1 "GNDM" H 4800 4350 50  0000 C CNN
F 2 "" H 4800 4500 50  0000 C CNN
F 3 "" H 4800 4500 50  0000 C CNN
	1    4800 4500
	1    0    0    -1  
$EndComp
$Comp
L GNDM #PWR046
U 1 1 57019B14
P 4800 2350
F 0 "#PWR046" H 4800 2100 50  0001 C CNN
F 1 "GNDM" H 4800 2200 50  0000 C CNN
F 2 "" H 4800 2350 50  0000 C CNN
F 3 "" H 4800 2350 50  0000 C CNN
	1    4800 2350
	1    0    0    -1  
$EndComp
Wire Wire Line
	4250 4400 4450 4400
$Comp
L +3.3V #PWR047
U 1 1 5702029E
P 3600 4300
F 0 "#PWR047" H 3600 4150 50  0001 C CNN
F 1 "+3.3V" H 3600 4440 50  0000 C CNN
F 2 "" H 3600 4300 50  0000 C CNN
F 3 "" H 3600 4300 50  0000 C CNN
	1    3600 4300
	1    0    0    -1  
$EndComp
Wire Wire Line
	4250 2250 4450 2250
$Comp
L +3.3V #PWR048
U 1 1 57020422
P 3550 2100
F 0 "#PWR048" H 3550 1950 50  0001 C CNN
F 1 "+3.3V" H 3550 2240 50  0000 C CNN
F 2 "" H 3550 2100 50  0000 C CNN
F 3 "" H 3550 2100 50  0000 C CNN
	1    3550 2100
	1    0    0    -1  
$EndComp
$EndSCHEMATC
