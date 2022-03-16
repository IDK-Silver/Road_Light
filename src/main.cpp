#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <ImageDatas.h>
#include <Ultrasonic.h>
#include <CarDetect.h>
#include <SendMessage.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

const char* SSID = "ABCD";
const char* WiFi_PassWord =  "kc70491533";


void TCA9548A(uint8_t bus){
  Wire.beginTransmission(0x70);  // TCA9548A address
  Wire.write(1 << bus);          // send byte to select bus
  Wire.endTransmission();
  Serial.print(bus);
}


void setup() 
{
  Serial.begin (115200);             // Serial Port begin
  Wire.begin();
  display.clearDisplay();

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


void loop()
{   
	Ultrasonic* ultrasonic_in = new Ultrasonic(13, 12);
	Ultrasonic* ultrasonic_out = new Ultrasonic(26, 27);

	// DeBug
	Serial.println(ultrasonic_in->read());
	Serial.println(ultrasonic_out->read());

  
  	delay(150);

	if (CarDetect::car_in(ultrasonic_in))
	{
		Serial.println("[Main]	:Car In");
		SendMessage::send_msg(1);
		delay(1000);
	}


	if (CarDetect::car_in(ultrasonic_out))
	{
		Serial.println("[Main]	:Car Out");
		SendMessage::send_msg(-1);
		delay(1000);
	}
}
