#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Adafruit_INA219.h>
#include <Adafruit_ADS1015.h>
LiquidCrystal_I2C lcd(0x27,16,2);
Adafruit_INA219 ina219;
Adafruit_ADS1115 ads(0x48);

void setup() {
  /* 
  pinMode(13, INPUT);
  pinMode(, OUTPUT);
  pinMode(8, INPUT);
  pinMode(, OUTPUT); */
  pinMode(2, INPUT);
  pinMode(3, OUTPUT);
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  Wire.begin();
  ina219.begin();
  ina219.setCalibration_32V_2A();
  ads.begin();
  ads.setGain(GAIN_TWOTHIRDS);
}

void loop() {
  /*
  if(digitalRead(13)) digitalWrite(pin, HIGH);
  if(digitalRead(8)) digitalWrite(pin, HIGH);*/
  if(digitalRead(2)==1){
    digitalWrite(3, HIGH);
  }
  else{
    digitalWrite(3, LOW);
  }
  float shuntvoltage = ina219.getShuntVoltage_mV();
  float busvoltage = ina219.getBusVoltage_V();
  float current_mA = (ina219.getCurrent_mA())*(-1);
  float power_mW = ina219.getPower_mW();
  float loadvoltage = busvoltage + (shuntvoltage / 1000);
  int16_t adc0;
  adc0 = ads.readADC_SingleEnded(0);
  float Voltage = (adc0 * 0.1875)/1000;
  lcd.setCursor(0,0);
  lcd.print("V=");
  lcd.print(loadvoltage);
  lcd.setCursor(7,0);
  lcd.print("I=");
  lcd.print(current_mA);
  lcd.print(" mA");
  lcd.setCursor(0,1);
  lcd.print("ADS1115=");
  lcd.print(Voltage,4);
  delay(500);
  lcd.clear();
}
