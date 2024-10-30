#include "PDcon.h"

using namespace ev3api;

GyroSensor PDcon::PDgyro(PORT_4);

PDcon::PDcon(unsigned char runmethod, int threathold, float Pgain, float Igain, float Dgain)
    : mRunmethod(runmethod), mthreathold(threathold),
      mPgain(Pgain), mIgain(Igain), mDgain(Dgain), mold_diff(0), angle_reset(true)
{
    mColorDetect = new ColorDetect();
}

PDcon::~PDcon()
{
    delete mColorDetect;
}

int PDcon::getTurn()
{
    if (angle_reset == true)
    {
        PDgyro.reset();
        angle_reset = false;
        return 0;
    }
    
    calcTurn();
    return mturn;
}

void PDcon::calcTurn()
{
    calcP();
    calcI();
    calcD();
    mturn = mP_value + mI_value + mD_value;
}

void PDcon::calcP()
{
    if (mRunmethod == STRAIGHT)
    {
        mdiff = PDgyro.getAngle() - mthreathold;
    }
    else if (mRunmethod == LINETRACE)
    {
        mColorDetect->convHSV();
        mdiff = mColorDetect->getS() - mthreathold;
    }

    mP_value = mdiff * mPgain;
}

void PDcon::calcI()
{
    sum += mdiff;
    mI_value = sum * mIgain;
    i++;
    if (i >= 20)
    {
        sum = 0;
        i = 0;
    }

}

void PDcon::calcD()
{
    mD_value = (mdiff - mold_diff) * mDgain;
    mold_diff = mdiff;
}
