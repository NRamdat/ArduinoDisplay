//YWROBOT
//Compatible with the Arduino IDE 1.0
//Library version:1.1
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

#include <SPI.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>

#define BME_SCK 13
#define BME_MISO 12
#define BME_MOSI 11
#define BME_CS 10

#define SEALEVELPRESSURE_HPA (1013.25)
Adafruit_BME280 bme(BME_CS, BME_MOSI, BME_MISO, BME_SCK);

LiquidCrystal_I2C lcd(0x27,20,4);  // set the LCD address to 0x27 for a 16 chars and 2 line display

const int AirValue = 614;   //you need to replace this value with Value_1
const int WaterValue = 255;  //you need to replace this value with Value_2
int intervals = (AirValue - WaterValue)/3;
int soilMoistureValue = 0;
int soilmoisturepercent = 0;

void setup()
{
  Serial.begin(9600);

  bme.begin(); 
  lcd.clear(); 
  lcd.init();                      // initialize the lcd 
  lcd.backlight();
}


void loop()
{
  printValuesMoisture();
}

void printValuesTempHumi() {
    lcd.setCursor(2.5,0);
    lcd.print("Temp: ");
    lcd.print(bme.readTemperature());
    lcd.print(" *C");  
    
    lcd.setCursor(2,1);
    lcd.print("Humi: ");
    lcd.print(bme.readHumidity());
    lcd.print(" %");

    delay(10000);
}

void printValuesMoisture() {
  int soilMoistureValue = analogRead(A0);
  soilmoisturepercent = map(soilMoistureValue, AirValue, WaterValue, 0, 100);
  Serial.print("The moisture: ");
  Serial.println(soilmoisturepercent);

  lcd.setCursor(2.5,0);
  lcd.print("Vochtigheid: ");
  lcd.setCursor(2.5,1);
  lcd.print(soilmoisturepercent);
  lcd.print("%");
  delay(250);
  lcd.clear();

 
}
