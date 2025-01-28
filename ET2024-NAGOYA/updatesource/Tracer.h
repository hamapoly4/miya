#ifndef TRACER_H
#define TRACER_H

#include "ColorSensor.h" 
#include "RoboBody.h"

enum LineSide{
    LEFT,
    RIGHT
};

class Tracer{
public:
    Tracer(LineSide side = RIGHT);

    void calcOnOff(int8_t& leftPower, int8_t& rightPower,int8_t maxPower,const rgb_raw_t& rawColor);

    void calcPID(int8_t& leftPower, int8_t& rightPower,int8_t maxPower,const rgb_raw_t& rawColor);

    void changePID(int8_t& leftPower, int8_t& rightPower,int8_t maxPower,const rgb_raw_t& rawColor);

    void moveRoboOnOf(RoboBody& robo, int8_t maxPower);

    void moveRoboPID(RoboBody& robo,int8_t maxPower);

    void changemoveRoboPID(RoboBody& robo,int8_t maxPower);

    inline
    static int getBrightness(const rgb_raw_t& rawColor){
        // 青線部分の影響を排除する為、、blueは足さない
        return (rawColor.r + rawColor.g);
    }

    static int getBrightness2(const rgb_raw_t& rawColor){
        //
        return (rawColor.r + rawColor.g + rawColor.b);
    }

    inline
    int getLastBrightness(){
        return lastBrightness;
    }

protected:
    LineSide lineSide;
    int grayBrightness;

    int lastBrightness;
};

#endif // TRACER_H