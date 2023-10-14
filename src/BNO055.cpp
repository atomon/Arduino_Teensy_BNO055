#include "BNO055.hpp"


// Check I2C device address and correct line below (by default address is 0x29 or 0x28)
BNO055::BNO055() : Adafruit_BNO055(55, 0x28, &Wire){}
BNO055::BNO055(int id) : Adafruit_BNO055(55, id, &Wire){}


void BNO055::set(bool debug)
{
    if(!this->begin(adafruit_bno055_opmode_t::OPERATION_MODE_IMUPLUS)){
        /* There was a problem detecting the BNO055 ... check your connections */
        if(debug) Serial.println("Ooops, no BNO055 detected ... Check your wiring or I2C ADDR!");
    }
    this->setExtCrystalUse(true);
}

void BNO055::reset()
{
    this->read_euler();
    roll_offset += this->get_roll(this->Unit::rad);
    pitch_offset += this->get_pitch(this->Unit::rad);
    yaw_offset += this->get_yaw(this->Unit::rad);
}


void BNO055::read_euler(bool debug)
{
    imu::Quaternion quat = this->getQuat();
 
    /* read the quat data */
    w = quat.w();
    x = quat.x();
    y = quat.y();
    z = quat.z();
    
    double ysqr = y * y;
    
    // roll (x-axis rotation)
    double t0 = +2.0 * (w * x + y * z);
    double t1 = +1.0 - 2.0 * (x * x + ysqr);
    roll = atan2(t0, t1);

    // pitch (y-axis rotation)
    double t2 = +2.0 * (w * y - z * x);
    t2 = t2 > 1.0 ? 1.0 : t2;
    t2 = t2 < -1.0 ? -1.0 : t2;
    pitch = asin(t2);

    // yaw (z-axis rotation)
    double t3 = +2.0 * (w * z + x * y);
    double t4 = +1.0 - 2.0 * (ysqr + z * z);  
    yaw = atan2(t3, t4);

    // offset
    roll -= roll_offset;
    pitch -= pitch_offset;
    yaw -= yaw_offset;

    // radian to degree
    roll_deg = roll * 57.2957795131;
    pitch_deg = pitch * 57.2957795131;
    yaw_deg = yaw * 57.2957795131;
    
    // view angle for debug
    if(debug)
    {
        Serial.print("roll: ");
        Serial.print(roll, 2);
        Serial.print(" pitch: ");
        Serial.print(pitch, 2);
        Serial.print(" yaw: ");
        Serial.println(yaw, 2);

    }
}


float BNO055::get_roll(byte unit, bool debug)
{
    float roll_val;

    if(unit) roll_val = this->roll_deg;
    else       roll_val = this->roll;
    
    if(debug) Serial.printf("roll: %f %s\n", roll_val, this->units_str[unit].c_str());
    return roll_val;
}


float BNO055::get_pitch(byte unit, bool debug)
{
    float pitch_val;

    if(unit) pitch_val = this->pitch_deg;
    else       pitch_val = this->pitch;

    if(debug) Serial.printf("pitch: %f %s\n", pitch_val, this->units_str[unit].c_str());
    return pitch_val;
}


float BNO055::get_yaw(byte unit, bool debug)
{
    float yaw_val;

    if(unit) yaw_val = this->yaw_deg;
    else       yaw_val = this->yaw;

    if(debug) Serial.printf("yaw: %f %s\n", yaw_val, this->units_str[unit].c_str());
    return yaw_val;
}