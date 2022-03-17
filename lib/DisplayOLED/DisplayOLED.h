#ifndef DISPLAY_OLED_LIB
#define DISPLAY_OLED_LIB

#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

class Multi_OLED
{
public:
    Multi_OLED(Adafruit_SSD1306*);
    ~Multi_OLED();

    void display(int index, const uint8_t bmp[]);
    void clear(int index);

private:
    Adafruit_SSD1306* oled_obj;
;

    void TCA9548A(uint8_t bus);

};




#endif 