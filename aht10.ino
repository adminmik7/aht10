#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_AHTX0.h>
#include <LiquidCrystal_I2C.h>

Adafruit_AHTX0 aht;
LiquidCrystal_I2C lcd(0x27, 20, 4); // LCD 2004, address 0x27

// Project Version
#define VERSION "1.5.0"

// Custom LCD Icons
byte tempIcon[8] = {
  B00100,
  B01010,
  B01010,
  B01010,
  B01010,
  B10001,
  B10001,
  B01110
};

byte dropIcon[8] = {
  B00100,
  B00100,
  B01010,
  B01010,
  B10001,
  B10001,
  B10001,
  B01110
};

void setup() {
  Serial.begin(9600);
  delay(1000);
  
  Serial.print("AHT10 Monitor v");
  Serial.println(VERSION);

  // Register custom characters
  lcd.createChar(0, tempIcon);
  lcd.createChar(1, dropIcon);

  // LCD Initialization
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("AHT10 Monitor");
  lcd.setCursor(0, 1);
  lcd.print("Ver: ");
  lcd.print(VERSION);
  lcd.setCursor(0, 2);
  lcd.print("Starting...");

  if (!aht.begin()) {
    Serial.println("Could not find AHT10. Check wiring!");
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("AHT10 Error!");
    while (1) delay(10);
  }
  Serial.println("AHT10 found!");
  delay(1000);
  lcd.clear();
}

void loop() {
  sensors_event_t humidity, temp;
  aht.getEvent(&humidity, &temp);

  // Вывод в Serial
  Serial.print("Temperature: ");
  Serial.print(temp.temperature);
  Serial.print(" *C\t");
  
  Serial.print("Humidity: ");
  Serial.print(humidity.relative_humidity);
  Serial.println(" %");

  // Вывод на LCD 2004 с иконками
  lcd.setCursor(0, 1);
  lcd.write(byte(0)); // Иконка термометра
  lcd.print(" Temp: ");
  lcd.print(temp.temperature, 1);
  lcd.write(B11011111); // Символ градуса °
  lcd.print("C   ");

  lcd.setCursor(0, 2);
  lcd.write(byte(1)); // Иконка капли
  lcd.print(" Hum: ");
  lcd.print(humidity.relative_humidity, 1);
  lcd.print("%    ");

  delay(2000);
}
