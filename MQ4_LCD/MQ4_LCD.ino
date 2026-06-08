#include <Wire.h>
#include <LiquidCrystal_I2C.h>

//liquid crystal LCD 1602 on i2c
LiquidCrystal_I2C lcd(0x27, 16, 2);

#define MQ4ANALOG A0
#define MQ4DIGITAL 8

void display_data(int value, int present)
{
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("GAS value: ");
  lcd.print(value);
  lcd.setCursor(0,1);
  if (present == LOW)
  {
    lcd.print("Gas detected");
  }
  else
  {
    lcd.print("Gas not present");
  }
}

void setup()
{
  pinMode(MQ4DIGITAL, INPUT);
  lcd.begin();
  //lcd.noBacklight();
  lcd.setCursor(0,0);
}

void loop()
{
  int present = digitalRead(MQ4DIGITAL);
  int value = analogRead(MQ4ANALOG);
  display_data(value, present);
  delay(1000);
}