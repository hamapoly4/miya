/******************************************************************************
 *  ファイル名：Runner.h
 *　　　　内容：Runnerクラスの定義
 *  　　作成日：2024/8/3
 *  　　作成者：近藤　悠太
 *****************************************************************************/

#ifndef EV3_APP_CALCULATION_H_
#define EV3_APP_CALCULATION_H_

/* ヘッダファイルのインクルード */
#include "ColorSensor.h"

class Calculation {
private:
    /* constメンバ変数定義 */
    const ev3api::ColorSensor& mColorSensor;
    const float KP = 0.50;  // Pゲイン
    const float KI = 0.03;  // Iゲイン
    const float KD = 2;     // Dゲイン
    const int target = 38;  // 目標値

    /* メンバ変数宣言 */
    int p_value;    // P制御から求めた値
    int i_value;    // I制御から求めた値
    int d_value;    // D制御から求めた値
    int turn;       // 制御値
    int diff;       // 偏差

public:
    /* コンストラクタ宣言 */
    Calculation(const ev3api::ColorSensor& colorsensor);

    /* メンバ関数宣言 */
    int CalcP();    // P演算
    int CalcI();    // I演算
    int CalcD();    // D演算
    int ControlPID();   // PID制御から制御値を求める

};

#endif  // EV3_APP_CALCULATION_H_
