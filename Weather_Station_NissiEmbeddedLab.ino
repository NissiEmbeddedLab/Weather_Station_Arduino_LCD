// Nissi Embedded Lab
// Pavoorchatram 627808
// Written by L.Boaz
// Released under an MIT license.
// https://github.com/NissiEmbeddedLab
// https://create.arduino.cc/projecthub/boaz
// https://www.hackster.io/boaz

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <Adafruit_BMP085.h>
#define seaLevelPressure_hPa 1013.25
Adafruit_BMP085 bmp;
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>

#define DHTPIN 2
#define DHTTYPE    DHT11
DHT_Unified dht(DHTPIN, DHTTYPE);

uint32_t delayMS;
LiquidCrystal_I2C lcd(0x27, 16, 2);
unsigned int bp;
void setup()
{
  Serial.begin(9600);
  dht.begin();
  Serial.println(F("DHTxx Unified Sensor Example")); // Print temperature sensor details.
  sensor_t sensor;
  dht.temperature().getSensor(&sensor);
  delayMS = sensor.min_delay / 1000;
  if (!bmp.begin())
  {
    Serial.println("Could not find a valid BMP085 sensor, check wiring!");
    while (1) {}
  }
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("NissiEmbeddedLab");
  delay(500);
  lcd.setCursor(0, 1);
  lcd.print("Weather Station");
  delay(2000);
  Serial.begin(9600);
  if (!bmp.begin())
  {
    lcd.println("No BMP180");
    while (1)
    {
    }
  }
}


void loop()
{
  delay(delayMS);
  sensors_event_t event;
  dht.temperature().getEvent(&event);
  if (isnan(event.temperature))
  {
    Serial.println(F("Error reading temperature!"));
  }
  else
  {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Temp in deg C");
    lcd.setCursor(0, 1);
    lcd.print(event.temperature);
    delay(2000);
  }
  dht.humidity().getEvent(&event);
  if (isnan(event.relative_humidity))
  {
    Serial.println(F("Error reading humidity!"));
  }
  else
  {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Humidity in %");
    lcd.setCursor(0, 1);
    lcd.print(event.relative_humidity);
    delay(2000);
  }
  bp = bmp.readPressure();
  Serial.println(bp);
  if (bp > 102268)
  {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Hign Pressure");
    lcd.setCursor(0, 1);
    lcd.print("Clear Sky");
    delay(2000);
  }
  else if (bp > 100914 && bp < 102268)
  {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Normal Pressure");
    lcd.setCursor(0, 1);
    lcd.print("Steady Weather");
    delay(2000);
  }
  else if (bp > 1009 && bp < 100914)
  {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Low Pressure");
    lcd.setCursor(0, 1);
    lcd.print("Cloudy & Rainy");
    delay(2000);
  }
  else
  {
  }
  lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Pressure in Pa");
    lcd.setCursor(0, 1);
    lcd.print(bmp.readPressure());
    delay(2000);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("SeaLevel P in Pa");
    lcd.setCursor(0, 1);
    lcd.print(bmp.readSealevelPressure());
    delay(2000);
}
