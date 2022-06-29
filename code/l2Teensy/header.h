#include <HardwareSerial.h>
#include <Arduino.h>

//LED
#define stmLED 39
#define teensyLED  

//PWM
#define FLPWM 6
#define FRPWM 9
#define BLPWM 10
#define BRPWM 11

//DIR
#define FLDIR 2
#define FRDIR 3
#define BLDIR 4
#define BRDIR 5

//Serial
#define irSerial Serial1
#define camSerial Serial2
#define btSerial Serial3
#define serialLayer4 Serial4
#define serialLayer1 Serial5

//Others
#define ESC_LV 12
#define SOL_LV 13