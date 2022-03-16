#include "CarDetect.h"

bool CarDetect::car_in(Ultrasonic *ultrasonic)
{
    int dis = ultrasonic->read(Ultrasonic_Centimeters_Mod); 
    if(dis <= Trigger_Detect_CM) 
    {
        // wait car out the ultrasonic
        while(dis > Trigger_Detect_CM){ dis = ultrasonic->read(Ultrasonic_Centimeters_Mod); }
        return true;
    }
    else
    return false;
}