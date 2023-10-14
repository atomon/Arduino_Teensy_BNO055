/*  BNO055 class
 * 
 *  Date  : 2023.10.07
 *  Auther: atomon
 * 
 *  Default Args:
 *      debug = false
 *      id    = 0x28
 * 
 */

#ifndef BNO055_H
#define BNO055_H


#include <Arduino.h>

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>


class BNO055: public Adafruit_BNO055
{
    private:

        double w, x, y, z;
        
        double roll, pitch, yaw;  // radian
        
        double roll_deg, pitch_deg, yaw_deg;  // degree

        double roll_offset=.0, pitch_offset=.0, yaw_offset=.0;
        
        String units_str[2] = {" [rad]", " [deg]"};

    public:

        enum Unit:byte
        {
            rad,
            deg
        };
        
        BNO055();
        BNO055(int id);

        void set(bool debug=false);

        void reset();

        void read_euler(bool debug=false);

        float get_roll(byte unit, bool debug=false);
        float get_pitch(byte unit, bool debug=false);
        float get_yaw(byte unit, bool debug=false);
};

#endif
