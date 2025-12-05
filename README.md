# MQ135-DHT11-AirQuality-Monitor
A real-time Air Quality Monitoring System built using Arduino, MQ135 gas sensor, DHT11 temperature & humidity sensor, and a 0.96" OLED display.
It measures pollution levels and environmental data, then displays everything on the OLED while using LEDs and a buzzer to indicate GOOD, MODERATE, or BAD air quality.

🔍 Features

MQ135 gas sensor for air pollution detection

DHT11 temperature & humidity sensor

0.96" OLED display for real-time values

Green/Red LED indicators

Buzzer alert for dangerous air quality

Compact, low-cost, beginner-friendly design

Suitable for embedded systems & IoT learning

🛠 Hardware Used

Arduino UNO

MQ135 Air Quality Sensor

DHT11 Temperature & Humidity Sensor

0.96" I2C OLED Display (SSD1306)

Green LED, Red LED

Active Buzzer

10kΩ resistor (pull-up for DHT11)

Jumper wires & breadboard

📌 Pin Connections
MQ135 Sensor
MQ135 Pin	Arduino
AO	A0
VCC	5V
GND	GND
DO	(Not Used)
DHT11 (4-pin)
DHT11 Pin	Arduino
VCC	5V
DATA	D2
GND	GND
Pull-up	10k between DATA & VCC
OLED (I2C)
OLED Pin	Arduino
VCC	5V
GND	GND
SDA	A4
SCL	A5
LEDs & Buzzer
Component	Arduino Pin
Green LED	D3
Red LED	D4
Buzzer (+)	D5
Buzzer (–)	GND
🚦 Air Quality Logic
Status	Condition (MQ135 Raw)	LED/Buzzer Action
GOOD	≤ 100	Green ON
MODERATE	101–300	Green Fast Blink
BAD	> 300	Red ON + Beep
🖥 OLED Display Output
Temp: 28.3 C
Hum : 45.6 %
MQ135: 256
Air : MODERATE


Updates every ~300 ms.

📄 Code Summary

Reads MQ135 analog value

Reads temperature & humidity from DHT11

Classifies air quality into GOOD / MODERATE / BAD

Updates LEDs + buzzer based on air quality

Prints all values on the OLED (no Serial Monitor needed)

🚀 How to Use

Connect all components as per the wiring table

Install required libraries:

Adafruit SSD1306

Adafruit GFX

DHT sensor library

Upload the code to Arduino UNO

Power the board → OLED starts showing real-time values

Observe LEDs & buzzer for air quality indication

📦 Future Improvements (Optional Ideas)

Add ESP32 + Blynk/ThingSpeak for IoT dashboard

Log data to SD card

Add graphing on OLED

Add PM2.5 sensor (SDS011 or PMS5003)

Use non-blocking code (millis) for smoother UI

📚 Project Use Cases

Indoor pollution monitoring

Home/office air tracking

Embedded systems learning

IoT beginner project

College mini project or assignment
