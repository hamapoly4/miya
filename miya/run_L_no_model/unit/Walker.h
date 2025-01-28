/******************************************************************************
 *  ファイル名：Walker.h
 *　　　　内容：Walkerクラスの定義
 *  　　作成日：2024/8/3
 *  　　作成者：近藤　悠太
 *****************************************************************************/

#ifndef EV3_APP_WALKER_H_
#define EV3_APP_WALKER_H_

#include "Motor.h"

class Walker {
private:
    const int PWM = 45;
    ev3api::Motor& mLeftWheel;
    ev3api::Motor& mRightWheel;

public:
    Walker(ev3api::Motor& leftwheel, ev3api::Motor& rightwheel);

    void Run(int turn);
};

#endif  // EV3_APP_WALKER_H_