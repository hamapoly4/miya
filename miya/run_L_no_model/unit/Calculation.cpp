/******************************************************************************
 *  ファイル名：Calculation.cpp
 *　　　　内容：Calculationクラスの実施
 *  　　作成日：2024/8/3
 *  　　作成者：近藤　悠太
 *****************************************************************************/

#include "Calculation.h"

using namespace ev3api;

/*-------------------------------------------------------
*                  コンストラクタ定義
---------------------------------------------------------*/
Calculation::Calculation(const ColorSensor& colorsensor)
    : mColorSensor(colorsensor)
{
    ;
}

/*-------------------------------------------------------
*                   メンバ関数定義
---------------------------------------------------------*/
int Calculation::CalcP()    // P演算
{
    diff = mColorSensor.getBrightness() - target;
    p_value = KP * diff;
    return p_value;
}

int Calculation::CalcI()    // I演算
{
    static int sum = 0;
    static unsigned char i = 0;

    sum += diff;
    i_value = sum * KI;

    i++;
    if (i >= 10)
    {
        sum = 0;
        i = 0;
    }

    return i_value;
}

int Calculation::CalcD()    // D演算
{
    static int old_diff = 0;

    d_value = (diff - old_diff) * KD;
    old_diff = diff;

    return d_value;
}

int Calculation::ControlPID()   // PID制御から制御値を求める
{
    turn = CalcP() + CalcI() + CalcD();
    return turn;
}