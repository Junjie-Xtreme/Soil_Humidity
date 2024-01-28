/*
 * 5.5V A0 MAXrange 1023 Humidity: 100% @ 355
 */

#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#define SensorPin A0

LiquidCrystal_I2C lcd(0x27,16,2);  // 定义LCD的地址为0x27，16列2行
float sensorValue = 0;
int relayPin = 8; //继电器引脚
int humidity = 0; //湿度

void setup() {
  pinMode(relayPin, OUTPUT);
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
}

void loop() {
  sensorValue = analogRead(8);
  Serial.println(sensorValue);
  if (sensorValue < 355) {
    humidity = 100;
  }
  else {
    humidity = 100-((sensorValue-355)/6.63);
  }
  lcd.print("HUMIDITY:");
  lcd.print(humidity);
  lcd.print("%");
  
  if (humidity < 40) {
    digitalWrite(relayPin, HIGH);
    Serial.println("水泵在工作");
    lcd.setCursor(0,1);
    lcd.print("PUMP IS WORKING");
  }
  else {
    digitalWrite(relayPin, LOW);
    Serial.println("水泵不在工作");
    lcd.setCursor(0,1);
    lcd.print("PUMP IS DEAD");
  }

  delay(1000);
  lcd.clear();
}
