#ifndef ROBO_BODY
#define ROBO_BODY
#include "t_syslog.h"

#include "Motor.h"       
#include "ColorSensor.h"
#include "TouchSensor.h" 
#include "Position.h"

/**
 * 車輪クラス
 **/
class Wheel{
public:
    Wheel(ePortM port);

    int32_t getDelta();

    inline 
    void setPower(int8_t power){
        syslog(LOG_NOTICE,"setPower(int8_t power) TASK START");
        motor.setPWM(power);
        syslog(LOG_NOTICE,"setPower(int8_t power) TASK END");
    };

    inline
    void reset(){
        syslog(LOG_NOTICE,"reset() TASK START");
        lastCount = 0;
        motor.reset();
        syslog(LOG_NOTICE,"reset() TASK END");
    }
    
public:
    ev3api::Motor motor;
    int32_t lastCount;   
};


/**
 * ロボット本体
 **/
class RoboBody{
public:
    RoboBody();

    const Position& calcNewPosition();

    inline
    Position& getPosition(){ return position; }


    void setPower(int8_t leftPower, int8_t rightPower);

    inline 
    void getColor(rgb_raw_t& rawColor){
        syslog(LOG_NOTICE,"getColor(rgb_raw_t& rawColor) TASK START");
        colorSensor.getRawColor(rawColor);
        syslog(LOG_NOTICE,"getColor(rgb_raw_t& rawColor) TASK END");
    }

    inline 
    colorid_t getColorNumber(){
        syslog(LOG_NOTICE,"getColorNumber() TASK START");
        if(colorSensor.getColorNumber() == COLOR_NONE){
            return COLOR_WHITE;
        } else {
            return colorSensor.getColorNumber();
        }  
    }

    inline
    bool isButtonPushed(){
        syslog(LOG_NOTICE,"isButtonPushed() TASK START");
        return touchSensor.isPressed();
    }

protected:

    Position position;

    Wheel left;
    Wheel right;
    ev3api::ColorSensor colorSensor;
    ev3api::TouchSensor touchSensor;

};

#endif // ROBO_BODY