#include "t_syslog.h"

#include "RoboBody.h"
#include "RoboSpec.h"

/**********************************************************************
 * Wheel関連メソッド
 **********************************************************************/

Wheel::Wheel(ePortM port) : motor(port) {
    syslog(LOG_NOTICE,"Wheel(ePortM port) TASK START");
    lastCount = 0;
    syslog(LOG_NOTICE,"Wheel(ePortM port) TASK END");
}


int32_t 
Wheel::getDelta(){
    syslog(LOG_NOTICE,"getDelta() TASK START");
    int32_t count = motor.getCount();
    int32_t delta = count - lastCount;
    lastCount = count;
    syslog(LOG_NOTICE,"getDelta() TASK END");
    return delta;
}


/**********************************************************************
 * RoboBody関連メソッド
 **********************************************************************/
RoboBody::RoboBody() : left(PORT_C),right(PORT_B), colorSensor(PORT_2), touchSensor(PORT_1) {
        // Do Nothing
        syslog(LOG_NOTICE,"RoboBody() TASK START");
        syslog(LOG_NOTICE,"RoboBody() TASK END");
}

/**
 * モーターの回転数から新しい位置を計算する。
 */
const Position&
RoboBody::calcNewPosition(){
    syslog(LOG_NOTICE,"calcNewPosition() TASK START");
    double leftMeter = (double)left.getDelta() * RoboSpec::LEFT_WHEEL / 360.0;
    double rightMeter = (double)right.getDelta() * RoboSpec::RIGHT_WHEEL / 360.0;

    position.addDistance(leftMeter,rightMeter);
    syslog(LOG_NOTICE,"calcNewPosition() TASK END");

    return position;
}

void
RoboBody::setPower(int8_t leftPower, int8_t rightPower){
    syslog(LOG_NOTICE,"setPower(int8_t leftPower, int8_t rightPower) TASK START");
    calcNewPosition();
    left.setPower(leftPower);
    right.setPower(rightPower);
    syslog(LOG_NOTICE,"setPower(int8_t leftPower, int8_t rightPower) TASK END");
}
