#include "SendMessage.h"

int SendMessage::send_msg(int status)
{
    if ((WiFi.status() == WL_CONNECTED)) 
    { //Check the current connection status
  
        HTTPClient http;

        // switch (status)
        // {
        // case 1:
        //     char someText[] = "https://script.google.com/macros/s/AKfycbzPnBbPCBfgZ-tsRfxqs1M6yDmLzhMVkilo8Ida7MU89yFU5otktOChjIHOk6h2fDhifw/exec?value1=0";
        //     someText[122] = status + '0';  // add '0' to convert to ascii
        //     Serial.println("getgetgetget");
        //     http.begin(someText);
        //     http.GET();
        //     break;

        // case 2:
        //     char someText[] = "https://script.google.com/macros/s/AKfycbzPnBbPCBfgZ-tsRfxqs1M6yDmLzhMVkilo8Ida7MU89yFU5otktOChjIHOk6h2fDhifw/exec?value1=-0";
        //     someText[123] = 1 + '0';
        //     Serial.println("getgetgetget");
        //     http.begin(someText);
        //     http.GET();
        //     break;

        // }
    }
    return 0;
};
