#include <Adafruit_ADS1015.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
// Iniciar address 0x27 y 0x48
LiquidCrystal_I2C lcd(0x27, 16, 2);
Adafruit_ADS1115 ads(0x48);
float Voltage = 0.0;

void setup(void)
{ // initializar Serial/ADS/LCD
Serial.begin(9600);
ads.begin();
lcd.init();

// Encender Pantalla e imprimir en pantalla.
lcd.backlight(); 
lcd.setCursor(0,0); lcd.print("ADS1115");
lcd.setCursor(0,1); lcd.print("i2C LCD");
}

void loop(void)
{
int16_t adc0;
adc0 = ads.readADC_SingleEnded(0);
Voltage = (adc0 * 0.1875)/1000;

Serial.print("AIN0: ");
Serial.print(adc0);
Serial.print("Voltage: ");
Serial.println(Voltage, 4);

delay(100);
lcd.setCursor(0, 1);
lcd.print(Voltage, 4); // Variable a imprimir.
}
