// tag::walker_def[]
#include "t_syslog.h"

#include "app.h"
#include "util.h"
#include "Clock.h"

#include "RoboBody.h"
#include "Tracer.h"

bool moveRobo(RoboBody& robo, Tracer& tracer);

void main_task(intptr_t unused) {

  // TOPPAN(?)の立ち上がりを待つ。引数はタイムアウトの数値（最大２秒?待つ）
  tslp_tsk(2000000);

  syslog(LOG_NOTICE,"MAIN TASK START************************");

  ev3api::Clock clock;

  RoboBody robo;
  Tracer tracer;

  // ボタンが押されるのを待つ
  do{
    bool isPushed = robo.isButtonPushed();
    if(isPushed){
      break;
    }

    clock.sleep(100000);
    break;

  }while(true);


  syslog(LOG_NOTICE,"ROBOT HAS STARTED！************************");
  int loopCount = 0;
  bool doContinue = true;
  do{
    int brightness = tracer.getLastBrightness();
    syslog(LOG_NOTICE,"Brightness:%d",brightness);

    Position& position = robo.getPosition();
    syslog(LOG_NOTICE,position.toString());
    
    syslog(LOG_NOTICE,"loopCount:%d",loopCount);
    
    doContinue = moveRobo(robo, tracer);
    
    if(!doContinue){
      break;
    }

    loopCount++;
    /*
    if(loopCount % 1000 == 0){
      int brightness = tracer.getLastBrightness();
      syslog(LOG_NOTICE,"Brightness:%d",brightness);

      Position& position = robo.getPosition();
      syslog(LOG_NOTICE,position.toString());
    }
    */

    clock.sleep(4000);

  }while(true);

  ext_tsk();
}

// 今、コースのどの区間にいるのかを表す変数
static int phase = 0;

bool moveRobo(RoboBody& robo, Tracer& tracer){
  const Position& position = robo.calcNewPosition();

  bool doContinue = true;
  // 以下 positionにより、出力と終了判定を行う。
  ONCE_MORE:
  switch(phase){
    case 0: // スタート直後
      if(0.8 < position.x){ // 最初の直線を過ぎたら次のフェーズに
        syslog(LOG_NOTICE,"case 0 START************************");
        phase = 1;
        goto ONCE_MORE;
      }
      tracer.moveRoboPID(robo,70); // 全速力で走る
      break;

    case 1: // 最初のカーブ
      if(2.5 < position.y){ // ゴールを過ぎたら次のフェーズに
        syslog(LOG_NOTICE,"case 1 START************************");
        phase = 2;
        goto ONCE_MORE;
      }
      tracer.moveRoboPID(robo,50); // ちょっとスピードを抑える 
      break;
    
    case 2: // ゴール後の走り
      if(2.5 < position.y && 0.9 < position.x){ // 難所直前に着たら次のフェーズに
        syslog(LOG_NOTICE,"case 2 START************************");
        phase = 3;
        goto ONCE_MORE;
      }
      tracer.moveRoboOnOf(robo,40); // オンオフ制御で確実に進む
      break;

    case 3: // 難所直前
      // 今回はここで止まる…あとは任せた！
      syslog(LOG_NOTICE,"case 3 START************************");
      //robo.setPower(0,0);
      tracer.moveRoboOnOf(robo,50); // 
      //doContinue = false;
      break;

  }  

  return doContinue;
}

// end::main_task[]
