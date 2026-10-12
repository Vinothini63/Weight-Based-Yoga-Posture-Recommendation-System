# 🧘 Weight-Based Yoga Posture Recommendation System

## 📌 Project Overview
This project uses an Arduino, an HX711 load cell amplifier, and a load cell to measure weight. Based on predefined weight ranges in the program, it displays a suggested yoga posture on a 16x2 I2C LCD.

## ✨ Features
- ⚖️ Load cell weight measurement
- 📟 Real-time readings on an I2C LCD
- 🧘 Yoga posture suggestions based on configured ranges
- 🔧 Tare function to reset the scale
- 🔌 Serial Monitor output for debugging

## 🛠️ Components Required
- Arduino-compatible microcontroller
- Load cell
- HX711 load cell amplifier module
- 16x2 I2C LCD
- Jumper wires
- Breadboard and power supply

## 💻 Technologies and Libraries
- Arduino C/C++
- HX711_ADC library
- LiquidCrystal_I2C library
- EEPROM library (included conditionally)

## ⚙️ Working Principle
1. The load cell detects a force applied to it.
2. The HX711 module converts the sensor signal into digital readings.
3. The Arduino processes the readings using a calibration factor.
4. The LCD displays the measured value.
5. The program suggests a predefined yoga posture when the reading falls within configured ranges.

## 🧘 Posture Suggestions in the Code
- 20–40: Vajrasanam
- 40–80: Badmasanam
- 80–100: Sirasasanam

These ranges use the program's calculated value (`i * 100`) and should be calibrated and verified before use.

## 🚀 How to Run
1. Install the Arduino IDE.
2. Install the `HX711_ADC` and compatible `LiquidCrystal_I2C` libraries.
3. Connect the load cell to the HX711 module.
4. Connect the HX711 data and clock pins to Arduino pins 4 and 5.
5. Connect the I2C LCD using the correct I2C wiring for your board.
6. Upload the sketch and open Serial Monitor at **57600 baud**.

## ⚠️ Important Note
This project demonstrates weight measurement and rule-based yoga suggestions. Weight alone cannot determine which yoga posture is suitable or safe for an individual. Choose yoga postures based on appropriate instruction and individual ability.

## 🔮 Future Improvements
- Display weight units consistently.
- Improve calibration and measurement stability.
- Add a menu for selecting different modes.
- Provide posture guidance independently of weight.

## 👨‍💻 Project Category
Arduino | Embedded Systems | Load Cell | Weight Measurement | LCD Display

