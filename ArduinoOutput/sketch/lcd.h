#line 1 "c:\\Users\\sm-pc\\Desktop\\solux_arduino\\lcd.h"
#ifndef LCD_H
#define LCD

#include "Arduino.h"
#include <LiquidCrystal_I2C.h> 

class Lcd {
public:
    Lcd(uint8_t lcd_Addr, uint8_t lcd_cols, uint8_t lcd_rows);
    void setup();
    void printDistance(long distance);
private:
    LiquidCrystal_I2C lcd;
};

#endif