#include <WiFi.h>
#include <HTTPClient.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "./image_data.h"

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

const char* ssid = "ABCD";
const char* password =  "kc70491533";

int trigPin = 13;                  //Trig Pin
int echoPin = 12;
int trigPin2 = 26;                  //Trig Pin
int echoPin2 = 27;

int value1 = 1;
int value2 = 0;
int value3 = 0;

//------------define---------------

void TCA9548A(uint8_t bus){
  Wire.beginTransmission(0x70);  // TCA9548A address
  Wire.write(1 << bus);          // send byte to select bus
  Wire.endTransmission();
  Serial.print(bus);
}

// -----------function--------------

int car = 0;

bool car_in = false;

void setup() {
  Serial.begin (115200);             // Serial Port begin
  pinMode(13, OUTPUT);        // 定義輸入及輸出 
  pinMode(12, INPUT);
  pinMode(26, OUTPUT);
  pinMode(27, INPUT);
  Wire.begin();
  display.clearDisplay();

  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
 
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  Serial.println("\nConnected to the WiFi network");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  
}

int get_distance(int tr, int ec)
{
  digitalWrite(tr, LOW);
  delayMicroseconds(5);
  digitalWrite(tr, HIGH);     // 給 Trig 高電位，持續 10微秒
  delayMicroseconds(10);
  digitalWrite(tr, LOW);

  pinMode(ec, INPUT);             // 讀取 echo 的電位
  double distance = pulseIn(ec, HIGH);   // 收到高電位時的時間
 
  int cm = (distance/2) / 29.1;
  return cm;
}

int car_check()
{
    int dis = get_distance(13, 12); 
    if(dis <= 7){
    Serial.println("found it!");
    car_in = true;
    while(dis > 7){
    Serial.print(car);
    
    dis = get_distance(13, 12); 
    }

    car = 1;
    Serial.print(car);
    return car;
    
  }else{
    car = 0;
    Serial.println("not found!");
    return car;
  }
}

int car_check2()
{
    int dis = get_distance(26, 27); 
    if(dis <= 7){
    Serial.println("found it!");
    car_in = true;
    while(dis > 7){
    Serial.print(car);
    
    dis = get_distance(26, 27); 
    }

    car = 1;
    Serial.print(car);
    return car;
    
  }else{
    car = 0;
    Serial.println("not found!");
    return car;
  }
}

int send_msg(int msg){
   if ((WiFi.status() == WL_CONNECTED)) { //Check the current connection status
  
    HTTPClient http;
    char str_val1 = value1;

    if (msg == 1){
      char someText[] = "https://script.google.com/macros/s/AKfycbzPnBbPCBfgZ-tsRfxqs1M6yDmLzhMVkilo8Ida7MU89yFU5otktOChjIHOk6h2fDhifw/exec?value1=0";
      someText[122] = msg + '0';  // add '0' to convert to ascii
      Serial.println("getgetgetget");
      http.begin(someText);
      int httpCode = http.GET();
    }else {
      char someText[] = "https://script.google.com/macros/s/AKfycbzPnBbPCBfgZ-tsRfxqs1M6yDmLzhMVkilo8Ida7MU89yFU5otktOChjIHOk6h2fDhifw/exec?value1=-0";
      someText[123] = 1 + '0';
      Serial.println("getgetgetget");
      http.begin(someText);
      int httpCode = http.GET();
    }
    
    
    
}
}

void loop()
{   
//  HC_1();
//  Serial.print(cm);
//  Serial.print("cm----");
//  HC_2();
//  Serial.print(cm2);
//  Serial.println("cm");

  int dis = get_distance(13, 12);
  int dis2 = get_distance(26, 27);
  Serial.println(dis);
  Serial.println(dis2);
  
  delay(150);

  int car = car_check();
  if (car == 1){
    Serial.println("----------");
    delay(1000);
    send_msg(1);
    delay(500);
    
  }

  int car2 = car_check2();
  if (car2 == 1){
    Serial.println("----------");
    delay(1000);
    send_msg(-1);
    delay(500);
  }

  
}
