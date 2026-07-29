#include<Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

// Pins
const int acsPin = A0;
const int buzzer = 7;
const int relay = 2;

// إعدادات حساس ACS712
float sensitivity = 0.185; // حساسية 185mV/A لـ ACS712 5A
float offset = 2.5;        // الجهد الوسطي 2.5V

void setup() {
lcd.init();
  lcd.backlight();

  pinMode(buzzer, OUTPUT);
  pinMode(relay, OUTPUT);
  digitalWrite(relay, HIGH); // الجهاز يعمل

  lcd.setCursor(0,0);
  lcd.print("Power Monitor");
}

void loop() {

  int sensorValue = analogRead(acsPin);
  float voltage = (sensorValue * 5.0) / 1023.0;
  
  float current = (voltage - offset) / sensitivity; 
  if(current < 0) current = 0; // إزالة الضوضاء السلبية

  lcd.setCursor(0,1);
  lcd.print("I=");
  lcd.print(current, 2);
  lcd.print(" A     ");

  // *** حماية من الحمل الزائد ***
  if(current > 3.0) {
    digitalWrite(buzzer, HIGH);
    digitalWrite(relay, LOW);     // فصل الجهاز
    lcd.setCursor(0,0);
    lcd.print("Overload !!!    ");
  } else {
    digitalWrite(buzzer, LOW);
    digitalWrite(relay, HIGH);    // الجهاز شغال
    lcd.setCursor(0,0);
    lcd.print("Power Monitor   ");
  }

  delay(500);
}
