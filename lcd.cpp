#include "Arduino.h"
#include "Lcd.h"

Lcd::Lcd(uint8_t lcd_Addr,uint8_t lcd_cols,uint8_t lcd_rows): lcd(LiquidCrystal_I2C(lcd_Addr, lcd_cols, lcd_rows)) {}

void Lcd::setup() {
    lcd.init();
    lcd.backlight(); 
    lcd.setCursor(0, 0);
}

void Lcd::printDistance(long distance) {
    int j = (distance % 10000) / 1000; //1000의 자리 
    int k = (distance % 1000) / 100; //100의 자리 
    int l = (distance % 100) / 10; //10의 자리 
    int m = (distance % 10); //1의 자리 

    lcd.setCursor(0, 1); //커서 첫번째칸 두번째줄 위치 
    lcd.print("Distance: ");
    lcd.print(j);
    lcd.print(k);
    lcd.print(l);
    lcd.print(m);
    lcd.print("cm");
}

void Lcd::printstr(String str) {
    lcd.setCursor(0, 0);
    lcd.printstr("                "); //기존 문자열 출력되어있는 경우, erase 역할
    lcd.setCursor(0, 0);
    lcd.printstr(str.c_str());
}