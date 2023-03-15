#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2); // Bu kodu kullanırken ekranda yazı çıkmaz ise 0x27 yerine 0x3f yazınız !!
void setup() {
  lcd.init();

}

void loop() {
 lcd.setCursor(0,0); // İlk satırın başlangıç noktası
 lcd.print("Huseyin"); 
 lcd.setCursor(0,1);
 lcd.print("Kusutoglu"); // İkinci satırın başlangıç noktası
 delay(2000);
 //ikinci yazı
 lcd.clear();
 lcd.noBacklight(); // LCD Ekran ışığını kapatır
 delay(2000);
 lcd.backlight(); // LCD Ekran ışığını açar
 lcd.setCursor(0,0); // İlk satırın başlangıç noktası
 lcd.print("Bilisim");
 lcd.setCursor(0,1); // İkinci satırın başlangıç noktası
 lcd.print("Hocasi"); 
 delay(2000);
 lcd.clear();
}
