#include "DisplayOLED.h"

Multi_OLED::Multi_OLED(Adafruit_SSD1306* input_display)
{
    this->oled_obj = input_display;
}

Multi_OLED::~Multi_OLED()
{
}

void Multi_OLED::TCA9548A(uint8_t bus)
{
    Wire.beginTransmission(0x70);  // TCA9548A address
    Wire.write(1 << bus);          // send byte to select bus
    Wire.endTransmission();
    Serial.print(bus);
}

void Multi_OLED::display(int index, const uint8_t bmp [])
{
    TCA9548A(index);
	if(!this->oled_obj->begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
		Serial.println(F("SSD1306 allocation failed"));
		for(;;);
	}

    TCA9548A(index);
	this->oled_obj->clearDisplay();
	this->oled_obj->drawBitmap(0, 0, bmp, 128, 64, 1);
	this->oled_obj->display();  // 要有這行才會把文字顯示出來
}

void Multi_OLED::clear(int index)
{
    TCA9548A(index);
	if(!this->oled_obj->begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
		Serial.println(F("SSD1306 allocation failed"));
		for(;;);
	}

    TCA9548A(index);
    this->oled_obj->clearDisplay();
}