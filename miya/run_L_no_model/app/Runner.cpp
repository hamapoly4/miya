/******************************************************************************
 *  ファイル名：Runner.cpp
 *　　　　内容：Runnerクラスの実施
 *  　　作成日：2024/8/3
 *  　　作成者：近藤　悠太
 *****************************************************************************/

#include "Runner.h"

using namespace ev3api;

/*--------------------------------------------------------------------------------------------
*                                   コンストラクタ定義
----------------------------------------------------------------------------------------------*/
Runner::Runner(const SonarSensor& sonarsensor, Calculation& calculation, Walker& walker)
  : mSonarSensor(sonarsensor), mCalculation(calculation), mWalker(walker), mstrflg(false)
{
  ;
}

/*-------------------------------------------------------
*                   メンバ関数定義
---------------------------------------------------------*/
/* L字走行をするメンバ関数定義 */
void Runner::runL ()
{
  /* 走行を開始するか判定 */
  if (runStart() == false)
  {
    return;  /* 走行を開始しない */
  }

  mWalker.Run(mCalculation.ControlPID());
}

/* 走行開始の判断をするメンバ関数定義 */
bool Runner::runStart ()
{
  int16_t sdist; /* 超音波センサの距離に関する変数 */
  sdist = mSonarSensor.getDistance();  /* 障害物との距離を取得 */

  /* 障害物との距離が-1cmより大きく、5cm未満か判定 */
  if (-1 < sdist && sdist < 5)
  {
    mstrflg = true;   /* 走行開始フラグを立てる */
  }
  return mstrflg;   /* 走行開始フラグの状態を返す */
}
