#include <Arduino.h>
#include <BNO055.hpp>


BNO055 bno;

float roll, pitch, yaw;

void setup(void)
{
    bno.set(true);
    
    Serial.begin(9600);
    while(!Serial);
}

void loop(void)
{
    bno.read_euler();
    
    roll = bno.get_roll(bno.Unit::rad);
    pitch = bno.get_pitch(bno.Unit::rad);
    yaw = bno.get_yaw(bno.Unit::rad);
    Serial.printf("roll: % f, pitch: % f, yaw: % f [rad]  ", roll, pitch, yaw);

    roll = bno.get_roll(bno.Unit::deg);
    pitch = bno.get_pitch(bno.Unit::deg);
    yaw = bno.get_yaw(bno.Unit::deg);
    Serial.printf("roll: % f, pitch: % f, yaw: % f [deg]\n", roll, pitch, yaw);

    delay(100);
}
