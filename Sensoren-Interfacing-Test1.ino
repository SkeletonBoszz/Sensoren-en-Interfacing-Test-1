#include <Wire.h>
#include <BH1750.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2); // I2C address 0x27, 16 column and 2 rows

bool LCDstate = true;

BH1750 lightMeter;

float sensorValue;
float temperatureC;
float voltageOut;

#define lichtsensor 17

#define tempsensor 32

void setup() {
  Serial.begin(9600);
  pinMode(lichtsensor, OUTPUT);
  pinMode(tempsensor, INPUT);

  Wire.begin();

  lightMeter.begin();

  lcd.init();
  lcd.clear();
  lcd.backlight();
}
void loop() {
  float Lux = lightMeter.readLightLevel();

  Serial.print("Light Value: ");
  Serial.print(Lux);
  Serial.print("||");
  Serial.print("Temperature: ");
  Serial.println(temperatureC);
  Serial.println("---------------------------------");

  sensorValue = analogRead(tempsensor);
  voltageOut = (sensorValue * 3300) / 4095;  // 3300,  ||   4096
  temperatureC = voltageOut / 10;

  lcd.setCursor(2, 0);
  lcd.print(Lux);
  lcd.print("lux");
  lcd.setCursor(2, 1);
  lcd.print(temperatureC);
  lcd.print("C");

  delay(1000);
}