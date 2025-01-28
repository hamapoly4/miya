#ifndef ___CLASS_PDCON
#define ___CLASS_PDCON	// インクルードカード

#include "GyroSensor.h"
#include "ColorDetect.h"

class PDcon {
private:
    static ev3api::GyroSensor PDgyro;
    ColorDetect* mColorDetect;

    enum eRun { STRAIGHT, LINETRACE, };

    int mthreathold;
    int mdiff;
    int mold_diff;
    float mPgain;
    float mIgain;
    float mDgain;
    int mP_value;
    int mI_value;
    int mD_value;
    int mturn;
    int sum;
    int i;
    unsigned char mRunmethod;
    bool angle_reset;

public:
    PDcon(unsigned char runmethod, int threathold, float Pgain, float Igain, float Dgain);
    ~PDcon();
    int getTurn();
    void calcTurn();
    void calcP();
    void calcI();
    void calcD();
};

#endif // ___CLASS_PDCON
