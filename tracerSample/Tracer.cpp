#include "Tracer.h"

#include "Env.h"

Tracer::Tracer(LineSide side){
    lineSide = side;
    grayBrightness = GRAY_COLOR;
    lastBrightness = -1; // 負の値にして有効でないことを示す        
}

void
Tracer::calcOnOff(int8_t& leftPower, int8_t& rightPower,int8_t maxPower,const rgb_raw_t& rawColor){

    int brightness = getBrightness(rawColor);

    // 右エッジをトレースするつもりで計算
    if(grayBrightness < brightness){
        // 白フロア上にいる
        leftPower = 0;
        rightPower = maxPower;
    } else {
        // 黒線上にいる
        leftPower = maxPower;
        rightPower = 0;
    }
    
    // 左エッジトレースなら、左右のパワーをスワップ
    if(lineSide == LEFT){
        int8_t power = leftPower;
        leftPower = rightPower;
        rightPower = power;
    }

    lastBrightness = brightness;

    return;
}


#define COLOR_WIDTH 100.0
void
Tracer::calcPID(int8_t& leftPower, int8_t& rightPower,int8_t maxPower,const rgb_raw_t& rawColor){

    int brightness = getBrightness(rawColor);

    // 右エッジをトレースするつもりで計算
    if(grayBrightness < brightness){
        double diff = brightness - grayBrightness;
        // 白フロア上にいる
        leftPower = (double)maxPower * (1.0 - diff / COLOR_WIDTH);
        rightPower = maxPower;
    } else {
        double diff = grayBrightness - brightness;
        // 黒線上にいる
        leftPower = maxPower;
        rightPower =  (double)maxPower * (1.0 - diff / COLOR_WIDTH);
    }
    
    // 左エッジトレースなら、左右のパワーをスワップ
    if(lineSide == LEFT){
        int8_t power = leftPower;
        leftPower = rightPower;
        rightPower = power;
    }

    lastBrightness = brightness;
    
    return;
}

void 
Tracer::moveRoboOnOf(RoboBody& robo, int8_t maxPower){
    rgb_raw_t rawColor;
    robo.getColor(rawColor);

    int8_t leftPower, rightPower;
    calcOnOff(leftPower,rightPower,maxPower,rawColor);
    robo.setPower(leftPower, rightPower);
}

void 
Tracer::moveRoboPID(RoboBody& robo, int8_t maxPower){
    rgb_raw_t rawColor;
    robo.getColor(rawColor);

    int8_t leftPower, rightPower;
    calcPID(leftPower,rightPower,maxPower,rawColor);
    robo.setPower(leftPower, rightPower);
}
