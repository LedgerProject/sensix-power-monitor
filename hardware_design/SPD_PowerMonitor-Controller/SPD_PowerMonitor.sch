EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title "PowerMonitor - Controller"
Date "2021-09-02"
Rev "A"
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L RF_Module:ESP32-WROOM-32U U1
U 1 1 6117D617
P 4400 3250
F 0 "U1" H 4400 4831 50  0000 C CNN
F 1 "ESP32-WROOM-32U" H 4400 4740 50  0000 C CNN
F 2 "RF_Module:ESP32-WROOM-32U" H 4400 1750 50  0001 C CNN
F 3 "https://www.espressif.com/sites/default/files/documentation/esp32-wroom-32d_esp32-wroom-32u_datasheet_en.pdf" H 4100 3300 50  0001 C CNN
	1    4400 3250
	1    0    0    -1  
$EndComp
Text GLabel 5250 2050 2    50   Input ~ 0
BOOT_MODE
Text GLabel 5250 2150 2    50   Input ~ 0
TXD0
Text GLabel 5250 2350 2    50   Input ~ 0
RXD0
Text GLabel 5250 2550 2    50   Input ~ 0
SPI_CS_0
Text GLabel 5250 2950 2    50   Input ~ 0
DEBUG_LOGS
Text GLabel 5250 3250 2    50   Input ~ 0
SPI_CLK
Text GLabel 5250 3350 2    50   Input ~ 0
SPI_MISO
Text GLabel 5250 3650 2    50   Input ~ 0
SPI_MOSI
Wire Wire Line
	5000 2050 5250 2050
Wire Wire Line
	5000 2150 5250 2150
Wire Wire Line
	5000 2350 5250 2350
Wire Wire Line
	5000 2550 5250 2550
Wire Wire Line
	5000 2950 5250 2950
Wire Wire Line
	5000 3250 5250 3250
Wire Wire Line
	5000 3350 5250 3350
Wire Wire Line
	5000 3650 5250 3650
NoConn ~ 5000 2650
$Comp
L Connector_Generic:Conn_01x08 J1
U 1 1 61180520
P 3400 3550
F 0 "J1" H 3318 2925 50  0000 C CNN
F 1 "Conn_01x08" H 3318 3016 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x08_P2.54mm_Vertical" H 3400 3550 50  0001 C CNN
F 3 "~" H 3400 3550 50  0001 C CNN
	1    3400 3550
	-1   0    0    1   
$EndComp
Wire Wire Line
	3600 3250 3800 3250
Wire Wire Line
	3600 3350 3800 3350
Wire Wire Line
	3600 3450 3800 3450
Wire Wire Line
	3600 3550 3800 3550
Wire Wire Line
	3600 3650 3800 3650
Wire Wire Line
	3600 3750 3800 3750
$Comp
L power:+3.3V #PWR0101
U 1 1 61182E5E
P 3750 3050
F 0 "#PWR0101" H 3750 2900 50  0001 C CNN
F 1 "+3.3V" H 3765 3223 50  0000 C CNN
F 2 "" H 3750 3050 50  0001 C CNN
F 3 "" H 3750 3050 50  0001 C CNN
	1    3750 3050
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0102
U 1 1 61183E34
P 3750 3950
F 0 "#PWR0102" H 3750 3700 50  0001 C CNN
F 1 "GND" H 3755 3777 50  0000 C CNN
F 2 "" H 3750 3950 50  0001 C CNN
F 3 "" H 3750 3950 50  0001 C CNN
	1    3750 3950
	1    0    0    -1  
$EndComp
Wire Wire Line
	3600 3150 3750 3150
Wire Wire Line
	3750 3150 3750 3050
Wire Wire Line
	3600 3850 3750 3850
Wire Wire Line
	3750 3850 3750 3950
NoConn ~ 3800 2350
NoConn ~ 3800 2250
$Comp
L Device:R R1
U 1 1 61185965
P 3300 1800
F 0 "R1" H 3370 1846 50  0000 L CNN
F 1 "10k" H 3370 1755 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 3230 1800 50  0001 C CNN
F 3 "~" H 3300 1800 50  0001 C CNN
	1    3300 1800
	1    0    0    -1  
$EndComp
$Comp
L Device:C C1
U 1 1 61186564
P 3300 2300
F 0 "C1" H 3415 2346 50  0000 L CNN
F 1 "0.1u" H 3415 2255 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 3338 2150 50  0001 C CNN
F 3 "~" H 3300 2300 50  0001 C CNN
	1    3300 2300
	1    0    0    -1  
$EndComp
$Comp
L Device:C C2
U 1 1 61186FBB
P 5050 1500
F 0 "C2" H 5165 1546 50  0000 L CNN
F 1 "10u" H 5165 1455 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 5088 1350 50  0001 C CNN
F 3 "~" H 5050 1500 50  0001 C CNN
	1    5050 1500
	1    0    0    -1  
$EndComp
$Comp
L Device:C C3
U 1 1 61187A5F
P 5350 1500
F 0 "C3" H 5465 1546 50  0000 L CNN
F 1 "0.1u" H 5465 1455 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 5388 1350 50  0001 C CNN
F 3 "~" H 5350 1500 50  0001 C CNN
	1    5350 1500
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0103
U 1 1 61187D2F
P 5050 1750
F 0 "#PWR0103" H 5050 1500 50  0001 C CNN
F 1 "GND" H 5055 1577 50  0000 C CNN
F 2 "" H 5050 1750 50  0001 C CNN
F 3 "" H 5050 1750 50  0001 C CNN
	1    5050 1750
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0104
U 1 1 61188987
P 5350 1750
F 0 "#PWR0104" H 5350 1500 50  0001 C CNN
F 1 "GND" H 5355 1577 50  0000 C CNN
F 2 "" H 5350 1750 50  0001 C CNN
F 3 "" H 5350 1750 50  0001 C CNN
	1    5350 1750
	1    0    0    -1  
$EndComp
Wire Wire Line
	5050 1750 5050 1650
Wire Wire Line
	5350 1750 5350 1650
Wire Wire Line
	5350 1350 5350 1150
Wire Wire Line
	5350 1150 5050 1150
Wire Wire Line
	4400 1150 4400 1850
Wire Wire Line
	5050 1350 5050 1150
Connection ~ 5050 1150
Wire Wire Line
	5050 1150 4400 1150
Wire Wire Line
	3300 2150 3300 2050
Wire Wire Line
	3800 2050 3300 2050
Connection ~ 3300 2050
Wire Wire Line
	3300 2050 3300 1950
$Comp
L power:GND #PWR0105
U 1 1 6118A9EA
P 3300 2550
F 0 "#PWR0105" H 3300 2300 50  0001 C CNN
F 1 "GND" H 3305 2377 50  0000 C CNN
F 2 "" H 3300 2550 50  0001 C CNN
F 3 "" H 3300 2550 50  0001 C CNN
	1    3300 2550
	1    0    0    -1  
$EndComp
Wire Wire Line
	3300 2550 3300 2450
$Comp
L power:+3.3V #PWR0106
U 1 1 6118B7E1
P 3300 1550
F 0 "#PWR0106" H 3300 1400 50  0001 C CNN
F 1 "+3.3V" H 3315 1723 50  0000 C CNN
F 2 "" H 3300 1550 50  0001 C CNN
F 3 "" H 3300 1550 50  0001 C CNN
	1    3300 1550
	1    0    0    -1  
$EndComp
Wire Wire Line
	3300 1550 3300 1650
$Comp
L power:+3.3V #PWR0107
U 1 1 6118C8FC
P 4400 1000
F 0 "#PWR0107" H 4400 850 50  0001 C CNN
F 1 "+3.3V" H 4415 1173 50  0000 C CNN
F 2 "" H 4400 1000 50  0001 C CNN
F 3 "" H 4400 1000 50  0001 C CNN
	1    4400 1000
	1    0    0    -1  
$EndComp
Wire Wire Line
	4400 1000 4400 1150
Connection ~ 4400 1150
$Comp
L Regulator_Linear:TC1262-33 U2
U 1 1 6118D990
P 6800 1300
F 0 "U2" H 6800 1542 50  0000 C CNN
F 1 "TC1262-33" H 6800 1451 50  0000 C CNN
F 2 "Package_TO_SOT_SMD:SOT-223-3_TabPin2" H 6800 1525 50  0001 C CIN
F 3 "http://ww1.microchip.com/downloads/en/DeviceDoc/21373C.pdf" H 6800 1000 50  0001 C CNN
	1    6800 1300
	1    0    0    -1  
$EndComp
Wire Wire Line
	6350 1000 6350 1300
Wire Wire Line
	6350 1300 6500 1300
$Comp
L Device:C C4
U 1 1 61190A13
P 6350 1550
F 0 "C4" H 6465 1596 50  0000 L CNN
F 1 "1u" H 6465 1505 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 6388 1400 50  0001 C CNN
F 3 "~" H 6350 1550 50  0001 C CNN
	1    6350 1550
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0109
U 1 1 61191514
P 6350 1850
F 0 "#PWR0109" H 6350 1600 50  0001 C CNN
F 1 "GND" H 6355 1677 50  0000 C CNN
F 2 "" H 6350 1850 50  0001 C CNN
F 3 "" H 6350 1850 50  0001 C CNN
	1    6350 1850
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0110
U 1 1 61191BAA
P 6800 1850
F 0 "#PWR0110" H 6800 1600 50  0001 C CNN
F 1 "GND" H 6805 1677 50  0000 C CNN
F 2 "" H 6800 1850 50  0001 C CNN
F 3 "" H 6800 1850 50  0001 C CNN
	1    6800 1850
	1    0    0    -1  
$EndComp
Wire Wire Line
	6350 1400 6350 1300
Connection ~ 6350 1300
Wire Wire Line
	6350 1850 6350 1700
Wire Wire Line
	6800 1850 6800 1600
$Comp
L Device:C C5
U 1 1 6119345E
P 7250 1550
F 0 "C5" H 7365 1596 50  0000 L CNN
F 1 "1u" H 7365 1505 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 7288 1400 50  0001 C CNN
F 3 "~" H 7250 1550 50  0001 C CNN
	1    7250 1550
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0111
U 1 1 61193E48
P 7250 1850
F 0 "#PWR0111" H 7250 1600 50  0001 C CNN
F 1 "GND" H 7255 1677 50  0000 C CNN
F 2 "" H 7250 1850 50  0001 C CNN
F 3 "" H 7250 1850 50  0001 C CNN
	1    7250 1850
	1    0    0    -1  
$EndComp
Wire Wire Line
	7250 1850 7250 1700
$Comp
L power:+3.3V #PWR0112
U 1 1 611949B0
P 7250 1000
F 0 "#PWR0112" H 7250 850 50  0001 C CNN
F 1 "+3.3V" H 7265 1173 50  0000 C CNN
F 2 "" H 7250 1000 50  0001 C CNN
F 3 "" H 7250 1000 50  0001 C CNN
	1    7250 1000
	1    0    0    -1  
$EndComp
Wire Wire Line
	7250 1000 7250 1300
Wire Wire Line
	7100 1300 7250 1300
Connection ~ 7250 1300
Wire Wire Line
	7250 1300 7250 1400
$Comp
L power:GND #PWR0113
U 1 1 6119662E
P 4400 4750
F 0 "#PWR0113" H 4400 4500 50  0001 C CNN
F 1 "GND" H 4405 4577 50  0000 C CNN
F 2 "" H 4400 4750 50  0001 C CNN
F 3 "" H 4400 4750 50  0001 C CNN
	1    4400 4750
	1    0    0    -1  
$EndComp
Wire Wire Line
	4400 4750 4400 4650
Text GLabel 5250 3850 2    50   Input ~ 0
RESET_ADE
Text GLabel 5250 3950 2    50   Input ~ 0
IRQ_ADE
Text GLabel 5250 4050 2    50   Input ~ 0
CF2_ADE
Wire Wire Line
	5000 3850 5250 3850
Wire Wire Line
	5000 3950 5250 3950
Wire Wire Line
	5000 4050 5250 4050
Text GLabel 5250 3550 2    50   Input ~ 0
SCL
Text GLabel 5250 3450 2    50   Input ~ 0
SDA
Wire Wire Line
	5250 3450 5000 3450
Wire Wire Line
	5250 3550 5000 3550
Text GLabel 5250 3150 2    50   Input ~ 0
TXD2
Text GLabel 5250 3050 2    50   Input ~ 0
RXD2
Wire Wire Line
	5000 3050 5250 3050
Wire Wire Line
	5000 3150 5250 3150
$Comp
L Interface_UART:MAX3485 U3
U 1 1 6119D4EF
P 8850 1400
F 0 "U3" H 8850 2081 50  0000 C CNN
F 1 "MAX3485" H 8850 1990 50  0000 C CNN
F 2 "Package_SO:SO-8_5.3x6.2mm_P1.27mm" H 8850 700 50  0001 C CNN
F 3 "https://datasheets.maximintegrated.com/en/ds/MAX3483-MAX3491.pdf" H 8850 1450 50  0001 C CNN
	1    8850 1400
	1    0    0    -1  
$EndComp
Wire Wire Line
	5000 2450 5250 2450
Text GLabel 5250 2250 2    50   Input ~ 0
RE
Wire Wire Line
	5000 2250 5250 2250
Text GLabel 8350 1400 0    50   Input ~ 0
RE
Text GLabel 5250 2450 2    50   Input ~ 0
DE
Text GLabel 8350 1500 0    50   Input ~ 0
DE
Text GLabel 8350 1300 0    50   Input ~ 0
RXD2
Text GLabel 8350 1600 0    50   Input ~ 0
TXD2
Wire Wire Line
	8350 1300 8450 1300
Wire Wire Line
	8350 1400 8450 1400
Wire Wire Line
	8350 1500 8450 1500
Wire Wire Line
	8350 1600 8450 1600
$Comp
L Device:C C6
U 1 1 611AE02C
P 7950 850
F 0 "C6" H 8065 896 50  0000 L CNN
F 1 "C" H 8065 805 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 7988 700 50  0001 C CNN
F 3 "~" H 7950 850 50  0001 C CNN
	1    7950 850 
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR0114
U 1 1 611B085A
P 7950 650
F 0 "#PWR0114" H 7950 500 50  0001 C CNN
F 1 "+3.3V" H 7965 823 50  0000 C CNN
F 2 "" H 7950 650 50  0001 C CNN
F 3 "" H 7950 650 50  0001 C CNN
	1    7950 650 
	1    0    0    -1  
$EndComp
Wire Wire Line
	7950 650  7950 700 
Wire Wire Line
	7950 700  8850 700 
Wire Wire Line
	8850 700  8850 900 
Connection ~ 7950 700 
$Comp
L power:GND #PWR0115
U 1 1 611B2D69
P 7950 1100
F 0 "#PWR0115" H 7950 850 50  0001 C CNN
F 1 "GND" H 7955 927 50  0000 C CNN
F 2 "" H 7950 1100 50  0001 C CNN
F 3 "" H 7950 1100 50  0001 C CNN
	1    7950 1100
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0116
U 1 1 611B35B8
P 8850 2100
F 0 "#PWR0116" H 8850 1850 50  0001 C CNN
F 1 "GND" H 8855 1927 50  0000 C CNN
F 2 "" H 8850 2100 50  0001 C CNN
F 3 "" H 8850 2100 50  0001 C CNN
	1    8850 2100
	1    0    0    -1  
$EndComp
Wire Wire Line
	7950 1000 7950 1100
Wire Wire Line
	8850 2100 8850 2000
$Comp
L Device:R R4
U 1 1 611B5CC0
P 9550 950
F 0 "R4" H 9620 996 50  0000 L CNN
F 1 "1k" H 9620 905 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 9480 950 50  0001 C CNN
F 3 "~" H 9550 950 50  0001 C CNN
	1    9550 950 
	1    0    0    -1  
$EndComp
$Comp
L Device:R R5
U 1 1 611B7418
P 9700 1900
F 0 "R5" H 9770 1946 50  0000 L CNN
F 1 "1k" H 9770 1855 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 9630 1900 50  0001 C CNN
F 3 "~" H 9700 1900 50  0001 C CNN
	1    9700 1900
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0117
U 1 1 611B8422
P 9700 2150
F 0 "#PWR0117" H 9700 1900 50  0001 C CNN
F 1 "GND" H 9705 1977 50  0000 C CNN
F 2 "" H 9700 2150 50  0001 C CNN
F 3 "" H 9700 2150 50  0001 C CNN
	1    9700 2150
	1    0    0    -1  
$EndComp
Wire Wire Line
	9550 800  9550 700 
Wire Wire Line
	9550 700  8850 700 
Connection ~ 8850 700 
Wire Wire Line
	9250 1300 9700 1300
Wire Wire Line
	9700 1300 9700 1500
Wire Wire Line
	9700 2150 9700 2050
Wire Wire Line
	9250 1600 9550 1600
Wire Wire Line
	9550 1600 9550 1400
$Comp
L Connector_Generic:Conn_01x03 J4
U 1 1 611BD4AA
P 10450 1500
F 0 "J4" H 10530 1542 50  0000 L CNN
F 1 "Conn_01x03" H 10530 1451 50  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x03_P2.54mm_Vertical" H 10450 1500 50  0001 C CNN
F 3 "~" H 10450 1500 50  0001 C CNN
	1    10450 1500
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0118
U 1 1 611BE7D2
P 10150 1700
F 0 "#PWR0118" H 10150 1450 50  0001 C CNN
F 1 "GND" H 10155 1527 50  0000 C CNN
F 2 "" H 10150 1700 50  0001 C CNN
F 3 "" H 10150 1700 50  0001 C CNN
	1    10150 1700
	1    0    0    -1  
$EndComp
Wire Wire Line
	10250 1600 10150 1600
Wire Wire Line
	10150 1600 10150 1700
Wire Wire Line
	10250 1500 9700 1500
Connection ~ 9700 1500
Wire Wire Line
	9700 1500 9700 1750
Wire Wire Line
	10250 1400 9550 1400
Connection ~ 9550 1400
Wire Wire Line
	9550 1400 9550 1100
$Comp
L Connector_Generic:Conn_01x04 J2
U 1 1 611C2F63
P 6450 2700
F 0 "J2" V 6414 2412 50  0000 R CNN
F 1 "Conn_01x04" V 6323 2412 50  0000 R CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x04_P2.54mm_Vertical" H 6450 2700 50  0001 C CNN
F 3 "~" H 6450 2700 50  0001 C CNN
	1    6450 2700
	0    -1   -1   0   
$EndComp
Text GLabel 6450 3050 3    50   Input ~ 0
SDA
Text GLabel 6550 3050 3    50   Input ~ 0
SCL
$Comp
L power:+3.3V #PWR0119
U 1 1 611C67D2
P 6350 3050
F 0 "#PWR0119" H 6350 2900 50  0001 C CNN
F 1 "+3.3V" H 6365 3223 50  0000 C CNN
F 2 "" H 6350 3050 50  0001 C CNN
F 3 "" H 6350 3050 50  0001 C CNN
	1    6350 3050
	-1   0    0    1   
$EndComp
$Comp
L power:GND #PWR0120
U 1 1 611C7B3E
P 6650 3050
F 0 "#PWR0120" H 6650 2800 50  0001 C CNN
F 1 "GND" H 6655 2877 50  0000 C CNN
F 2 "" H 6650 3050 50  0001 C CNN
F 3 "" H 6650 3050 50  0001 C CNN
	1    6650 3050
	1    0    0    -1  
$EndComp
Wire Wire Line
	6350 3050 6350 2900
Wire Wire Line
	6450 3050 6450 2900
Wire Wire Line
	6550 3050 6550 2900
Wire Wire Line
	6650 3050 6650 2900
$Comp
L Device:R R2
U 1 1 611CDF26
P 7350 2900
F 0 "R2" H 7420 2946 50  0000 L CNN
F 1 "2.2k" H 7420 2855 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 7280 2900 50  0001 C CNN
F 3 "~" H 7350 2900 50  0001 C CNN
	1    7350 2900
	1    0    0    -1  
$EndComp
$Comp
L Device:R R3
U 1 1 611CEA69
P 7550 2900
F 0 "R3" H 7620 2946 50  0000 L CNN
F 1 "2.2k" H 7620 2855 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 7480 2900 50  0001 C CNN
F 3 "~" H 7550 2900 50  0001 C CNN
	1    7550 2900
	1    0    0    -1  
$EndComp
Text GLabel 7350 3100 3    50   Input ~ 0
SDA
$Comp
L power:+3.3V #PWR0121
U 1 1 611CEDD3
P 7350 2650
F 0 "#PWR0121" H 7350 2500 50  0001 C CNN
F 1 "+3.3V" H 7365 2823 50  0000 C CNN
F 2 "" H 7350 2650 50  0001 C CNN
F 3 "" H 7350 2650 50  0001 C CNN
	1    7350 2650
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR0122
U 1 1 611CF7FB
P 7550 2650
F 0 "#PWR0122" H 7550 2500 50  0001 C CNN
F 1 "+3.3V" H 7565 2823 50  0000 C CNN
F 2 "" H 7550 2650 50  0001 C CNN
F 3 "" H 7550 2650 50  0001 C CNN
	1    7550 2650
	1    0    0    -1  
$EndComp
Wire Wire Line
	7350 3100 7350 3050
Wire Wire Line
	7350 2750 7350 2650
Wire Wire Line
	7550 3100 7550 3050
Wire Wire Line
	7550 2750 7550 2650
Text GLabel 7550 3100 3    50   Input ~ 0
SCL
$Comp
L Connector:USB_B_Micro J5
U 1 1 612541D1
P 800 6200
F 0 "J5" H 857 6667 50  0000 C CNN
F 1 "USB_B_Micro" H 857 6576 50  0000 C CNN
F 2 "Connector_USB:USB_Micro-B_Molex-105017-0001" H 950 6150 50  0001 C CNN
F 3 "~" H 950 6150 50  0001 C CNN
	1    800  6200
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0123
U 1 1 612598A0
P 800 6700
F 0 "#PWR0123" H 800 6450 50  0001 C CNN
F 1 "GND" H 805 6527 50  0000 C CNN
F 2 "" H 800 6700 50  0001 C CNN
F 3 "" H 800 6700 50  0001 C CNN
	1    800  6700
	1    0    0    -1  
$EndComp
Wire Wire Line
	800  6700 800  6600
$Comp
L power:+5V #PWR0124
U 1 1 6125BCA5
P 1250 5850
F 0 "#PWR0124" H 1250 5700 50  0001 C CNN
F 1 "+5V" H 1265 6023 50  0000 C CNN
F 2 "" H 1250 5850 50  0001 C CNN
F 3 "" H 1250 5850 50  0001 C CNN
	1    1250 5850
	1    0    0    -1  
$EndComp
Wire Wire Line
	1100 6000 1250 6000
Wire Wire Line
	1250 6000 1250 5850
Text GLabel 3600 5500 2    50   Input ~ 0
TXD0
Text GLabel 3600 5600 2    50   Input ~ 0
RXD0
$Comp
L Device:Q_NPN_BEC Q1
U 1 1 6126CE49
P 4300 6100
F 0 "Q1" H 4491 6146 50  0000 L CNN
F 1 "Q_NPN_BEC" H 4491 6055 50  0000 L CNN
F 2 "Package_TO_SOT_SMD:SOT-23" H 4500 6200 50  0001 C CNN
F 3 "~" H 4300 6100 50  0001 C CNN
	1    4300 6100
	1    0    0    -1  
$EndComp
$Comp
L Device:Q_NPN_BEC Q2
U 1 1 6126DAB5
P 4300 6700
F 0 "Q2" H 4491 6746 50  0000 L CNN
F 1 "Q_NPN_BEC" H 4491 6655 50  0000 L CNN
F 2 "Package_TO_SOT_SMD:SOT-23" H 4500 6800 50  0001 C CNN
F 3 "~" H 4300 6700 50  0001 C CNN
	1    4300 6700
	1    0    0    -1  
$EndComp
$Comp
L Device:R R7
U 1 1 6126DFB8
P 3850 6700
F 0 "R7" V 3643 6700 50  0000 C CNN
F 1 "1k" V 3734 6700 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 3780 6700 50  0001 C CNN
F 3 "~" H 3850 6700 50  0001 C CNN
	1    3850 6700
	0    1    1    0   
$EndComp
$Comp
L Device:R R6
U 1 1 6126EF31
P 3850 6100
F 0 "R6" V 3643 6100 50  0000 C CNN
F 1 "1k" V 3734 6100 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 3780 6100 50  0001 C CNN
F 3 "~" H 3850 6100 50  0001 C CNN
	1    3850 6100
	0    1    1    0   
$EndComp
Wire Wire Line
	4000 6100 4100 6100
Wire Wire Line
	4000 6700 4100 6700
Wire Wire Line
	4400 6300 4400 6400
Wire Wire Line
	4400 6400 3650 6400
Wire Wire Line
	3650 6400 3650 6700
Wire Wire Line
	3650 6700 3700 6700
Wire Wire Line
	4400 6900 3600 6900
Wire Wire Line
	3600 6900 3600 6100
Wire Wire Line
	3600 6100 3700 6100
Text GLabel 3300 5800 2    50   Input ~ 0
DTR
Text GLabel 3300 5400 2    50   Input ~ 0
RTS
Text GLabel 3550 6100 0    50   Input ~ 0
DTR
Text GLabel 3550 6400 0    50   Input ~ 0
RTS
Wire Wire Line
	3550 6100 3600 6100
Connection ~ 3600 6100
Wire Wire Line
	3550 6400 3650 6400
Connection ~ 3650 6400
Text GLabel 3150 2050 0    50   Input ~ 0
EN
Wire Wire Line
	3150 2050 3300 2050
Text GLabel 4550 5800 2    50   Input ~ 0
EN
Wire Wire Line
	4550 5800 4400 5800
Wire Wire Line
	4400 5800 4400 5900
Text GLabel 4600 6450 2    50   Input ~ 0
BOOT_MODE
Wire Wire Line
	4600 6450 4400 6450
Wire Wire Line
	4400 6450 4400 6500
$Comp
L Interface_USB:CP2102N-A01-GQFN24 U4
U 1 1 612956C4
P 2350 5800
F 0 "U4" H 2350 6881 50  0000 C CNN
F 1 "CP2102N-A01-GQFN24" H 2350 6790 50  0000 C CNN
F 2 "Package_DFN_QFN:QFN-24-1EP_4x4mm_P0.5mm_EP2.6x2.6mm" H 2800 5000 50  0001 L CNN
F 3 "https://www.silabs.com/documents/public/data-sheets/cp2102n-datasheet.pdf" H 2400 4750 50  0001 C CNN
	1    2350 5800
	1    0    0    -1  
$EndComp
Wire Wire Line
	1100 6200 1750 6200
Wire Wire Line
	1100 6300 1750 6300
Wire Wire Line
	1750 6100 1250 6100
Wire Wire Line
	1250 6100 1250 6000
Connection ~ 1250 6000
$Comp
L Device:R R8
U 1 1 612AAF28
P 1550 4900
F 0 "R8" H 1620 4946 50  0000 L CNN
F 1 "10k" H 1620 4855 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 1480 4900 50  0001 C CNN
F 3 "~" H 1550 4900 50  0001 C CNN
	1    1550 4900
	1    0    0    -1  
$EndComp
Wire Wire Line
	1750 5200 1550 5200
Wire Wire Line
	1550 5200 1550 5050
Wire Wire Line
	1550 4750 1550 4500
Wire Wire Line
	1550 4500 2250 4500
Wire Wire Line
	2350 4500 2350 4900
Wire Wire Line
	2250 4900 2250 4500
Connection ~ 2250 4500
Wire Wire Line
	2250 4500 2350 4500
$Comp
L power:+3.3V #PWR0125
U 1 1 612B676F
P 2350 4400
F 0 "#PWR0125" H 2350 4250 50  0001 C CNN
F 1 "+3.3V" H 2365 4573 50  0000 C CNN
F 2 "" H 2350 4400 50  0001 C CNN
F 3 "" H 2350 4400 50  0001 C CNN
	1    2350 4400
	1    0    0    -1  
$EndComp
Wire Wire Line
	2350 4400 2350 4500
Connection ~ 2350 4500
$Comp
L power:+3.3V #PWR0126
U 1 1 612BB2B7
P 1400 5750
F 0 "#PWR0126" H 1400 5600 50  0001 C CNN
F 1 "+3.3V" H 1415 5923 50  0000 C CNN
F 2 "" H 1400 5750 50  0001 C CNN
F 3 "" H 1400 5750 50  0001 C CNN
	1    1400 5750
	1    0    0    -1  
$EndComp
Wire Wire Line
	1400 5750 1400 5800
Wire Wire Line
	1400 5800 1750 5800
NoConn ~ 1750 5500
NoConn ~ 1750 5600
$Comp
L Device:R R9
U 1 1 612C86AB
P 3250 5500
F 0 "R9" V 3043 5500 50  0000 C CNN
F 1 "1k" V 3134 5500 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 3180 5500 50  0001 C CNN
F 3 "~" H 3250 5500 50  0001 C CNN
	1    3250 5500
	0    1    1    0   
$EndComp
$Comp
L Device:R R10
U 1 1 612C8FF0
P 3250 5600
F 0 "R10" V 3043 5600 50  0000 C CNN
F 1 "1k" V 3134 5600 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 3180 5600 50  0001 C CNN
F 3 "~" H 3250 5600 50  0001 C CNN
	1    3250 5600
	0    1    1    0   
$EndComp
Wire Wire Line
	2950 5500 3100 5500
Wire Wire Line
	2950 5600 3100 5600
Wire Wire Line
	3300 5400 2950 5400
Wire Wire Line
	3300 5800 2950 5800
Wire Wire Line
	3400 5500 3600 5500
Wire Wire Line
	3400 5600 3600 5600
NoConn ~ 2950 5200
NoConn ~ 2950 5300
NoConn ~ 2950 5700
NoConn ~ 2950 5900
NoConn ~ 2950 6100
NoConn ~ 2950 6200
NoConn ~ 2950 6300
NoConn ~ 2950 6400
$Comp
L power:GND #PWR0127
U 1 1 613053FA
P 2350 6800
F 0 "#PWR0127" H 2350 6550 50  0001 C CNN
F 1 "GND" H 2355 6627 50  0000 C CNN
F 2 "" H 2350 6800 50  0001 C CNN
F 3 "" H 2350 6800 50  0001 C CNN
	1    2350 6800
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0128
U 1 1 61305A50
P 2450 6800
F 0 "#PWR0128" H 2450 6550 50  0001 C CNN
F 1 "GND" H 2455 6627 50  0000 C CNN
F 2 "" H 2450 6800 50  0001 C CNN
F 3 "" H 2450 6800 50  0001 C CNN
	1    2450 6800
	1    0    0    -1  
$EndComp
Wire Wire Line
	2350 6800 2350 6700
Wire Wire Line
	2450 6800 2450 6700
$Comp
L Device:C C8
U 1 1 613245BF
P 1250 4700
F 0 "C8" H 1365 4746 50  0000 L CNN
F 1 "0.1u" H 1365 4655 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 1288 4550 50  0001 C CNN
F 3 "~" H 1250 4700 50  0001 C CNN
	1    1250 4700
	1    0    0    -1  
$EndComp
$Comp
L Device:C C7
U 1 1 61325822
P 950 4700
F 0 "C7" H 1065 4746 50  0000 L CNN
F 1 "0.1u" H 1065 4655 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 988 4550 50  0001 C CNN
F 3 "~" H 950 4700 50  0001 C CNN
	1    950  4700
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0129
U 1 1 61325B46
P 950 4950
F 0 "#PWR0129" H 950 4700 50  0001 C CNN
F 1 "GND" H 955 4777 50  0000 C CNN
F 2 "" H 950 4950 50  0001 C CNN
F 3 "" H 950 4950 50  0001 C CNN
	1    950  4950
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0130
U 1 1 6132615A
P 1250 4950
F 0 "#PWR0130" H 1250 4700 50  0001 C CNN
F 1 "GND" H 1255 4777 50  0000 C CNN
F 2 "" H 1250 4950 50  0001 C CNN
F 3 "" H 1250 4950 50  0001 C CNN
	1    1250 4950
	1    0    0    -1  
$EndComp
Wire Wire Line
	950  4550 950  4500
Wire Wire Line
	950  4500 1250 4500
Connection ~ 1550 4500
Wire Wire Line
	1250 4550 1250 4500
Connection ~ 1250 4500
Wire Wire Line
	1250 4500 1550 4500
Wire Wire Line
	1250 4950 1250 4850
Wire Wire Line
	950  4950 950  4850
NoConn ~ 1100 6400
NoConn ~ 700  6600
Text GLabel 7100 3750 0    50   Input ~ 0
SPI_CLK
Text GLabel 7100 3850 0    50   Input ~ 0
SPI_MOSI
Text GLabel 7100 3950 0    50   Input ~ 0
SPI_MISO
Text GLabel 7100 4050 0    50   Input ~ 0
SPI_CS_0
Text GLabel 7100 4150 0    50   Input ~ 0
RESET_ADE
Text GLabel 7100 4250 0    50   Input ~ 0
IRQ_ADE
Text GLabel 7100 4350 0    50   Input ~ 0
CF2_ADE
$Comp
L power:GND #PWR0131
U 1 1 613568FB
P 7100 4500
F 0 "#PWR0131" H 7100 4250 50  0001 C CNN
F 1 "GND" H 7105 4327 50  0000 C CNN
F 2 "" H 7100 4500 50  0001 C CNN
F 3 "" H 7100 4500 50  0001 C CNN
	1    7100 4500
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_01x10 J3
U 1 1 6135CD3E
P 7550 3950
F 0 "J3" H 7630 3942 50  0000 L CNN
F 1 "Conn_01x10" H 7630 3851 50  0000 L CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_1x10_P2.54mm_Vertical" H 7550 3950 50  0001 C CNN
F 3 "~" H 7550 3950 50  0001 C CNN
	1    7550 3950
	1    0    0    -1  
$EndComp
Wire Wire Line
	7100 3750 7350 3750
Wire Wire Line
	7100 3850 7350 3850
Wire Wire Line
	7100 3950 7350 3950
Wire Wire Line
	7100 4050 7350 4050
Wire Wire Line
	7100 4150 7350 4150
Wire Wire Line
	7100 4250 7350 4250
Wire Wire Line
	7100 4350 7350 4350
Wire Wire Line
	7100 4500 7100 4450
Wire Wire Line
	7100 4450 7350 4450
$Comp
L power:+5V #PWR0108
U 1 1 6118F534
P 6350 1000
F 0 "#PWR0108" H 6350 850 50  0001 C CNN
F 1 "+5V" H 6365 1173 50  0000 C CNN
F 2 "" H 6350 1000 50  0001 C CNN
F 3 "" H 6350 1000 50  0001 C CNN
	1    6350 1000
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR0132
U 1 1 6138ED27
P 7050 3450
F 0 "#PWR0132" H 7050 3300 50  0001 C CNN
F 1 "+5V" H 7065 3623 50  0000 C CNN
F 2 "" H 7050 3450 50  0001 C CNN
F 3 "" H 7050 3450 50  0001 C CNN
	1    7050 3450
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0133
U 1 1 6138F7AD
P 6600 3700
F 0 "#PWR0133" H 6600 3450 50  0001 C CNN
F 1 "GND" H 6605 3527 50  0000 C CNN
F 2 "" H 6600 3700 50  0001 C CNN
F 3 "" H 6600 3700 50  0001 C CNN
	1    6600 3700
	1    0    0    -1  
$EndComp
Wire Wire Line
	7350 3650 6600 3650
Wire Wire Line
	6600 3650 6600 3700
Wire Wire Line
	7050 3450 7050 3550
Wire Wire Line
	7050 3550 7350 3550
$Comp
L Connector_Generic:Conn_01x03 J6
U 1 1 6142D71B
P 9000 2950
F 0 "J6" H 9080 2992 50  0000 L CNN
F 1 "Conn_01x03" H 9080 2901 50  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x03_P2.54mm_Vertical" H 9000 2950 50  0001 C CNN
F 3 "~" H 9000 2950 50  0001 C CNN
	1    9000 2950
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_01x03 J7
U 1 1 6142E2C9
P 9000 3350
F 0 "J7" H 9080 3392 50  0000 L CNN
F 1 "Conn_01x03" H 9080 3301 50  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x03_P2.54mm_Vertical" H 9000 3350 50  0001 C CNN
F 3 "~" H 9000 3350 50  0001 C CNN
	1    9000 3350
	1    0    0    -1  
$EndComp
Text GLabel 8650 2850 0    50   Input ~ 0
TXD0
Text GLabel 8650 2950 0    50   Input ~ 0
RXD0
Text GLabel 8650 3050 0    50   Input ~ 0
BOOT_MODE
Text GLabel 8650 3250 0    50   Input ~ 0
EN
$Comp
L power:GND #PWR0134
U 1 1 6142ECFA
P 8700 3550
F 0 "#PWR0134" H 8700 3300 50  0001 C CNN
F 1 "GND" H 8705 3377 50  0000 C CNN
F 2 "" H 8700 3550 50  0001 C CNN
F 3 "" H 8700 3550 50  0001 C CNN
	1    8700 3550
	1    0    0    -1  
$EndComp
Wire Wire Line
	8800 2850 8650 2850
Wire Wire Line
	8800 2950 8650 2950
Wire Wire Line
	8800 3050 8650 3050
Wire Wire Line
	8800 3250 8650 3250
Wire Wire Line
	8800 3350 8700 3350
Wire Wire Line
	8700 3350 8700 3450
Wire Wire Line
	8800 3450 8700 3450
Connection ~ 8700 3450
Wire Wire Line
	8700 3450 8700 3550
$EndSCHEMATC