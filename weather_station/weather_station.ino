#include "LowPower.h"

#include <Digital_Light_TSL2561.h>
#include "seeed_bme680.h"
#include "DS1307.h"

#include <SD.h>

// BME sensor (temp, pressure, humidity, gas)
#define BME_I2C_ADDR  uint8_t(0x76)
Seeed_BME680 bme680(BME_I2C_ADDR);

// DS1307 object (RTC)
DS1307 clock;

// Result file
File dataFile;

void setup() {
  // Wire on
  Wire.begin();
  // Rate for serial
  Serial.begin(9600);
  // Hang until Serial start
  while (!Serial);

  // Initialize BME sensor
  while (!bme680.init()) {
    delay(10000);
  }
  // Initialize digital light sensor
  TSL2561.init();
  // Initialize RTC
  //clock.begin();

  if (!SD.begin(4)) {
    while (1);
  }
}

void loop() {
  if (bme680.read_sensor_data()) {
    return;
  }

  // Create/Open the file
  dataFile = SD.open("RELEVES.CSV", FILE_WRITE);
  // Check if the file is newly created
  if(dataFile.size()==0)
  {
    Serial.println("Create a file");
    // We need to put the header in it
    dataFile.println("date,temperature(°C),pression(KPa),humidité(%),lumière");
  }

  writeTime(&dataFile);

  writeTemperaturePressureAndHumidityMeasures(&dataFile);

  writeLuxMeasure(&dataFile);
  
  dataFile.close();

  sleep();
//  file->print("The Light value is: ");
//  Serial.println(TSL2561.readVisibleLux());
//
//  file->print("The Infrared value is: ");
//  Serial.println(TSL2561.readIRLuminosity());  //read Infrared channel value only, not convert to lux.
// 
//  file->print("The Full Spectrum value is: ");
//  Serial.println(TSL2561.readFSpecLuminosity());///read Full Spectrum channel value only,  not convert to lux.
}

void sleep()
{
  unsigned int count = 0;
  while(count<2){
    ++count;
    LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF);
  }
}

void writeTime(File *file) {
  clock.getTime();

  
  writeMeasure(file,clock.hour);
  file->print(':');
  writeMeasure(file,clock.minute);
  file->print(':');
  writeMeasure(file,clock.second);
  file->print(' ');
  writeMeasure(file,clock.dayOfMonth);
  file->print('/');
  writeMeasure(file,clock.month);
  file->print('/');
  file->print(clock.year+2000);
  file->print(',');
}

void writeMeasure(File *file, uint8_t &number) {
  if(number<10)
  {
    file->print('0');
  }
  file->print(number);
}

void writeTemperaturePressureAndHumidityMeasures(File *file) {
  file->print(bme680.sensor_result_value.temperature);
  file->print(',');
  file->print(bme680.sensor_result_value.pressure/1000.0);
  file->print(',');
  file->print(bme680.sensor_result_value.humidity);
  file->print(',');
}

void writeLuxMeasure(File *file) {
    file->println(TSL2561.readFSpecLuminosity());
}
