//ADS1115: Link -->  https://wolles-elektronikkiste.de/en/ads1115-a-d-converter-with-amplifier
//INA226: Link -->  https://wolles-elektronikkiste.de/en/ina226-current-and-power-sensor
//Excel Stream --> https://www.hackster.io/HackingSTEM/stream-data-from-arduino-into-excel-f1bede

#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);
#include <OneWire.h>

#include <ADS1115_WE.h>
ADS1115_WE adc = ADS1115_WE(0x48);

#include <INA226_WE.h>
INA226_WE ina226 = INA226_WE(0x40);

void setup() {
  Serial.begin(9600);
  Wire.begin();
  lcd.init();
  lcd.backlight();
  adc.init();
  ina226.init();
  
  Serial.println("Test Starting!");
  Serial.println(" ");
  lcd.print("Test Starting!");
  delay(5000);
  lcd.clear();
  //BAĞLANTI KONTROLÜ /////////////////////////////////////////////////////

  if (!adc.init()) {
    Serial.println("ADS1115 not connected!");
    lcd.setCursor(0, 0);  //İlk satırın başlangıç noktası
    lcd.print("ADS1115 Not Connected!");
  } else {
    lcd.setCursor(0, 0);
    Serial.println("ADS1115 Connected!");
    lcd.print("ADS1115 Connected!");
  }
  if (!ina226.init()) {
    Serial.println("INA226 not connected!");
    lcd.setCursor(0, 1);  //İlk satırın başlangıç noktası
    lcd.print("INA226 Not Connected!");
  } else {
    Serial.println("INA226 Connected!");
    lcd.setCursor(0, 1);
    lcd.print("INA226 Connected!");
  }
  Serial.println(" ");
  delay(5000);

  //BAĞLANTI KONTROLÜ SONU /////////////////////////////////////////////////////

  //ADS AYARLARI/////////////////////////////////////////////////////

  /* Set the voltage range of the ADC to adjust the gain
   * Please note that you must not apply more than VDD + 0.3V to the input pins!
   * 
   * ADS1115_RANGE_6144  ->  +/- 6144 mV
   * ADS1115_RANGE_4096  ->  +/- 4096 mV
   * ADS1115_RANGE_2048  ->  +/- 2048 mV (default)
   * ADS1115_RANGE_1024  ->  +/- 1024 mV
   * ADS1115_RANGE_0512  ->  +/- 512 mV
   * ADS1115_RANGE_0256  ->  +/- 256 mV
   */
  adc.setVoltageRange_mV(ADS1115_RANGE_6144);  //comment line/change parameter to change range
  /* Set the inputs to be compared
   *  
   *  ADS1115_COMP_0_1    ->  compares 0 with 1 (default)
   *  ADS1115_COMP_0_3    ->  compares 0 with 3
   *  ADS1115_COMP_1_3    ->  compares 1 with 3
   *  ADS1115_COMP_2_3    ->  compares 2 with 3
   *  ADS1115_COMP_0_GND  ->  compares 0 with GND
   *  ADS1115_COMP_1_GND  ->  compares 1 with GND
   *  ADS1115_COMP_2_GND  ->  compares 2 with GND
   *  ADS1115_COMP_3_GND  ->  compares 3 with GND
   */
  adc.setCompareChannels(ADS1115_COMP_0_GND);  //uncomment if you want to change the default
  /* Set number of conversions after which the alert pin will assert
   * - or you can disable the alert 
   *  
   *  ADS1115_ASSERT_AFTER_1  -> after 1 conversion
   *  ADS1115_ASSERT_AFTER_2  -> after 2 conversions
   *  ADS1115_ASSERT_AFTER_4  -> after 4 conversions
   *  ADS1115_DISABLE_ALERT   -> disable comparator / alert pin (default) 
   */
  adc.setAlertPinMode(ADS1115_DISABLE_ALERT);  //uncomment if you want to change the default
  /* Set the conversion rate in SPS (samples per second)
   * Options should be self-explaining: 
   * 
   *  ADS1115_8_SPS 
   *  ADS1115_16_SPS  
   *  ADS1115_32_SPS 
   *  ADS1115_64_SPS  
   *  ADS1115_128_SPS (default)
   *  ADS1115_250_SPS 
   *  ADS1115_475_SPS 
   *  ADS1115_860_SPS 
   */
  adc.setConvRate(ADS1115_128_SPS);  //uncomment if you want to change the default
  /* Set continuous or single shot mode:
   * 
   *  ADS1115_CONTINUOUS  ->  continuous mode
   *  ADS1115_SINGLE     ->  single shot mode (default)
   */
  //adc.setMeasureMode(ADS1115_CONTINUOUS); //uncomment if you want to change the default
  /* Choose maximum limit or maximum and minimum alert limit (window) in volts - alert pin will 
   *  assert when measured values are beyond the maximum limit or outside the window 
   *  Upper limit first: setAlertLimit_V(MODE, maximum, minimum)
   *  In max limit mode the minimum value is the limit where the alert pin assertion will be 
   *  be cleared (if not latched)  
   * 
   *  ADS1115_MAX_LIMIT
   *  ADS1115_WINDOW
   * 
   */
  //adc.setAlertModeAndLimit_V(ADS1115_MAX_LIMIT, 3.0, 1.5); //uncomment if you want to change the default

  /* Enable or disable latch. If latch is enabled the alert pin will assert until the
   * conversion register is read (getResult functions). If disabled the alert pin assertion
   * will be cleared with next value within limits. 
   *  
   *  ADS1115_LATCH_DISABLED (default)
   *  ADS1115_LATCH_ENABLED
   */
  //adc.setAlertLatch(ADS1115_LATCH_ENABLED); //uncomment if you want to change the default
  /* Sets the alert pin polarity if active:
   *  
   * ADS1115_ACT_LOW  ->  active low (default)   
   * ADS1115_ACT_HIGH ->  active high
   */
  //adc.setAlertPol(ADS1115_ACT_LOW); //uncomment if you want to change the default

  /* With this function the alert pin will assert, when a conversion is ready.
   * In order to deactivate, use the setAlertLimit_V function  
   */
  //adc.setAlertPinToConversionReady(); //uncomment if you want to change the default
  //Serial.println("ADS1115 Example Sketch - Single Shot Mode");
  //Serial.println("Channel / Voltage [V]: ");
  //Serial.println();

  //ADS AYARLARI SONU /////////////////////////////////////////////////////

  //INA AYARLARI /////////////////////////////////////////////////////

  /* Set Number of measurements for shunt and bus voltage which shall be averaged
  * Mode *     * Number of samples *
  AVERAGE_1            1 (default)
  AVERAGE_4            4
  AVERAGE_16          16
  AVERAGE_64          64
  AVERAGE_128        128
  AVERAGE_256        256
  AVERAGE_512        512
  AVERAGE_1024      1024
  */
  ina226.setAverage(AVERAGE_16);  // choose mode and uncomment for change of default

  /* Set conversion time in microseconds
     One set of shunt and bus voltage conversion will take: 
     number of samples to be averaged x conversion time x 2
     
     * Mode *         * conversion time *
     CONV_TIME_140          140 µs
     CONV_TIME_204          204 µs
     CONV_TIME_332          332 µs
     CONV_TIME_588          588 µs
     CONV_TIME_1100         1.1 ms (default)
     CONV_TIME_2116       2.116 ms
     CONV_TIME_4156       4.156 ms
     CONV_TIME_8244       8.244 ms  
  */
  ina226.setConversionTime(CONV_TIME_1100);  //choose conversion time and uncomment for change of default

  /* Set measure mode
  POWER_DOWN - INA226 switched off
  TRIGGERED  - measurement on demand
  CONTINUOUS  - continuous measurements (default)
  */
  ina226.setMeasureMode(CONTINUOUS);  // choose mode and uncomment for change of default

  /* Set Current Range
    * Mode *   * Max Current *
     MA_400          400 mA
     MA_800          800 mA (default)
  */
  ina226.setCurrentRange(MA_800);  // choose gain and uncomment for change of default

  /* If the current values delivered by the INA226 differ by a constant factor
     from values obtained with calibrated equipment you can define a correction factor.
     Correction factor = current delivered from calibrated equipment / current delivered by INA226
  */
  ina226.setCorrectionFactor(0.95);

  //Serial.println("INA226 Current Sensor Example Sketch - Continuous");
   //ina226.waitUntilConversionCompleted(); //if you comment this line the first data might be zero

  //INA AYARLARI SONU /////////////////////////////////////////////////////
}
void loop() {
  float ADSvoltage = 0;
  ADSvoltage = readChannel(ADS1115_COMP_0_GND);
  float INAshuntVoltage_mV = 0.0;
  float INAloadVoltage_V = 0.0;
  float INAbusVoltage_V = 0.0;
  float INAcurrent_mA = 0.0;
  float INApower_mW = 0.0;
  float INAresistance;
  ina226.readAndClearFlags();
  INAshuntVoltage_mV = ina226.getShuntVoltage_mV();
  INAbusVoltage_V = ina226.getBusVoltage_V();
  INAcurrent_mA = ina226.getCurrent_mA();
  INApower_mW = ina226.getBusPower();
  INAloadVoltage_V = INAbusVoltage_V + (INAshuntVoltage_mV / 1000);
  INAresistance = (INAbusVoltage_V / INAcurrent_mA) * 1000;
  //SERİ PORT////////
  Serial.print("ADS1115: ");
  Serial.print(ADSvoltage, 4);
  Serial.println(" mV");
  Serial.println("");
  Serial.print("Shunt Voltage [mV]: ");
  Serial.println(INAshuntVoltage_mV, 4);
  Serial.print("Bus Voltage [V]: ");
  Serial.println(INAbusVoltage_V, 4);
  Serial.print("Load Voltage [V]: ");
  Serial.println(INAloadVoltage_V), 4;
  Serial.print("Current[mA]: ");
  Serial.println(INAcurrent_mA);
  Serial.print("Bus Power [mW]: ");
  Serial.println(INApower_mW);
  Serial.print("INAResistance: ");
  Serial.println(INAresistance);
  Serial.println(" ");

 //LCD Ekran/////////
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("ADS:");
  lcd.println(ADSvoltage);
  //lcd.print(" mV");
  lcd.setCursor(0, 1);
  lcd.println("INA Res.");
  Serial.println(INAresistance);
  delay(500);
}
  float readChannel(ADS1115_MUX channel) {
  float ADSvoltage = 0;
  adc.setCompareChannels(channel);
  adc.startSingleMeasurement();
  while (adc.isBusy()) {}
  ADSvoltage = adc.getResult_mV();  // alternative: getResult_mV for Millivolt
  return ADSvoltage;
}
