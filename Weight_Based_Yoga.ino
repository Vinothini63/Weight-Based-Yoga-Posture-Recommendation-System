
/* -------------------------------------------------------------------------------------
   HX711_ADC Arduino library for HX711 24-Bit Analog-to-Digital Converter for Weight Scales
   Olav Kallhovd, Sept 2017
------------------------------------------------------------------------------------- */

#include <LiquidCrystal_I2C.h>
#include <HX711_ADC.h>

#if defined(ESP8266) || defined(ESP32) || defined(AVR)
#include <EEPROM.h>
#endif

LiquidCrystal_I2C lcd(0x27, 16, 2);

// Pins
const int HX711_dout = 4;
const int HX711_sck = 5;

// HX711 constructor
HX711_ADC LoadCell(HX711_dout, HX711_sck);

const int calVal_eepromAdress = 0;
unsigned long t = 0;

void setup() {
  Serial.begin(57600);
  delay(10);

  lcd.init();
  lcd.backlight();

  lcd.setCursor(0, 0);
  lcd.print("Weight Based");

  lcd.setCursor(0, 1);
  lcd.print("Yoga");

  Serial.println();
  Serial.println("Starting...");

  LoadCell.begin();

  // LoadCell.setReverseOutput();

  float calibrationValue;
  calibrationValue = 94696.0;

  #if defined(ESP8266) || defined(ESP32)
  // EEPROM.begin(512);
  #endif

  // EEPROM.get(calVal_eepromAdress, calibrationValue);

  unsigned long stabilizingtime = 2000;
  boolean _tare = true;

  LoadCell.start(stabilizingtime, _tare);

  if (LoadCell.getTareTimeoutFlag()) {
    Serial.println("Timeout, check MCU>HX711 wiring and pin designations");
    while (1);
  } else {
    LoadCell.setCalFactor(calibrationValue);
    Serial.println("Startup is complete");
  }

  delay(3000);
  lcd.clear();
}

void loop() {
  static boolean newDataReady = 0;
  const int serialPrintInterval = 0;

  // Check for new data and start the next conversion
  if (LoadCell.update())
    newDataReady = true;

  // Get smoothed value from the dataset
  if (newDataReady) {
    if (millis() > t + serialPrintInterval) {
      float i = LoadCell.getData();

      Serial.print("Load_cell output val: ");
      Serial.println(i);

      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Weight:");

      lcd.setCursor(10, 0);
      lcd.print(i * 100);
      lcd.print("g");

      if ((i * 100) > 20 && (i * 100) < 40) {
        lcd.setCursor(0, 1);
        lcd.print("Do:");

        lcd.setCursor(5, 1);
        lcd.print("Vajrasanam");

        Serial.println("Vajrasanam");
      }
      else if ((i * 100) > 40 && (i * 100) < 80) {
        lcd.setCursor(0, 1);
        lcd.print("Do:");

        lcd.setCursor(5, 1);
        lcd.print("Badmasanam");

        Serial.println("Badmasanam");
      }
      else if ((i * 100) > 80 && (i * 100) < 100) {
        lcd.setCursor(0, 1);
        lcd.print("Do:");

        lcd.setCursor(5, 1);
        lcd.print("Sirasasanam");

        Serial.println("Sirasasanam");
      }

      newDataReady = 0;
      t = millis();
    }
  }

  // Receive command from Serial Monitor; send 't' to initiate tare
  if (Serial.available() > 0) {
    char inByte = Serial.read();

    if (inByte == 't')
      LoadCell.tareNoDelay();
  }

  // Check whether tare operation is complete
  if (LoadCell.getTareStatus() == true) {
    Serial.println("Tare complete");
  }

  delay(500);
}
