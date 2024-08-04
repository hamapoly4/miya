/******************************************************************************
 *  ファイル名：Runner.cpp
 *　　　　内容：Runnerクラスの定義
 *  　　作成日：2024/8/3
 *  　　作成者：近藤　悠太
 *****************************************************************************/

#ifndef EV3_APP_RUNNER_H_
#define EV3_APP_RUNNER_H_

/* ヘッダファイルのインクルード */
#include "SonarSensor.h"
#include "Calculation.h"
#include "Walker.h"

/*----------------------------------------------------
*                  Runnerクラスの定義
*-----------------------------------------------------*/
class Runner {
private:
    const ev3api::SonarSensor& mSonarSensor;    /* 超音波センサのconst参照オブジェクト */
    Calculation& mCalculation;
    Walker& mWalker;

    /* メンバ変数宣言 */
    unsigned char mstrflg;   /* 走行開始フラグ */

public:
    /* コンストラクタ宣言 */
    Runner(const ev3api::SonarSensor& sonarsensor,
            Calculation& calculation, Walker& walker);

    
    /* L字走行をするメンバ関数宣言 */
    void runL();

    /* 走行開始の判断をするメンバ関数宣言 */
    bool runStart();
};

#endif  // EV3_APP_RUNNER_H_
