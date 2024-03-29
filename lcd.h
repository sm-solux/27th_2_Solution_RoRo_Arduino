#ifndef LCD_H
#define LCD

#include "Arduino.h"
#include <LiquidCrystal_I2C.h> 

class Lcd {
public:
    Lcd(uint8_t lcd_Addr, uint8_t lcd_cols, uint8_t lcd_rows);
    void setup();
    void printDistance(long distance);
    void printstr(String str);
private:
    LiquidCrystal_I2C lcd;
};

#endif