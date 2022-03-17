#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <ImageDatas.h>
#include <Ultrasonic.h>
#include <CarDetect.h>
#include <SendMessage.h>
#include <DisplayOLED.h>


#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64


const char* SSID = "ABCD";
const char* WiFi_PassWord =  "kc70491533";


void setup() 
{
  Serial.begin(9600);             // Serial Port begin
  Wire.begin();


  WiFi.begin(SSID, WiFi_PassWord);
  Serial.print("Connecting to WiFi");
 
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  Serial.println("\nConnected to the WiFi network");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  
}

Adafruit_SSD1306* display = new Adafruit_SSD1306(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
Multi_OLED* multi_oled = new Multi_OLED(display);
Ultrasonic* ultrasonic_in = new Ultrasonic(13, 12);
Ultrasonic* ultrasonic_out = new Ultrasonic(26, 27);

void loop()
{   
	// DeBug
	Serial.println(String("Ultrasonic In  :") + ultrasonic_in->read());
	Serial.println(String("Ultrasonic Out :") + ultrasonic_out->read());
  	delay(150);

	if (CarDetect::car_in(ultrasonic_in))
	{
		Serial.println("[Main]	:Car In");
		multi_oled->display(5, ImageData::logo_come_car);
		multi_oled->display(4, ImageData::logo_front_car);
		SendMessage::send_msg(1);
		delay(1000);
		multi_oled->clear(5);
		multi_oled->clear(4);
	}


	if (CarDetect::car_in(ultrasonic_out))
	{
		Serial.println("[Main]	:Car Out");
		multi_oled->display(2, ImageData::logo_come_car);
		multi_oled->display(3, ImageData::logo_front_car);
		SendMessage::send_msg(-1);
		delay(1000);
		multi_oled->clear(2);
		multi_oled->clear(3);
	}


}
