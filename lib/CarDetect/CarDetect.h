#ifndef CARDETERCT_LIB
#define CARDETERCT_LIB

#define Ultrasonic_Centimeters_Mod CM // CM　or INC
#define Trigger_Detect_CM 7
#include <Ultrasonic.h>



namespace CarDetect {

    bool car_in(Ultrasonic* ultrasonic);


};






#endif