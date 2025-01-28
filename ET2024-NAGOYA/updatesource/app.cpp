// tag::walker_def[]
#include "t_syslog.h"

#include "app.h"
#include "util.h"
#include "Clock.h"

#include "RoboBody.h"
#include "Tracer.h"
#include "ColorSensor.h"

bool moveRobo(RoboBody& robo, Tracer& tracer);

void main_task(intptr_t unused) {

    // TOPPAN(?)の立ち上がりを待つ。引数はタイムアウトの数値（最大２秒?待つ）
    tslp_tsk(2000000);

    syslog(LOG_NOTICE,"MAIN TASK START_1************************");

    ev3api::Clock clock;
    syslog(LOG_NOTICE,"MAIN TASK START_2************************");

    RoboBody robo;

    syslog(LOG_NOTICE,"MAIN TASK START_3************************");

    Tracer tracer;

    syslog(LOG_NOTICE,"MAIN TASK START_4************************");

    // ボタンが押されるのを待つ
  do{
      syslog(LOG_NOTICE,"do start_1************************");

      RoboBody robo;
      bool isPushed = robo.isButtonPushed();

      syslog(LOG_NOTICE,"do start_2************************");

      if(isPushed){
        syslog(LOG_NOTICE,"ButtonPushed True************************");
        break;
      }
      else{
        syslog(LOG_NOTICE,"ButtonPushed False************************");
        break;
      }

      clock.sleep(100000);

    }while(true);


    syslog(LOG_NOTICE,"ROBOT HAS STARTED！************************");
    int loopCount = 0;
    bool doContinue = true;
    do{
      doContinue = moveRobo(robo, tracer);
      
      if(!doContinue){
        break;
      }

      loopCount++;
    
      if(loopCount % 1000 == 0){
        int brightness = tracer.getLastBrightness();
        syslog(LOG_NOTICE,"Brightness:%d",brightness);

        Position& position = robo.getPosition();
        syslog(LOG_NOTICE,position.toString());
      }


      clock.sleep(4000);

    }while(true);

    ext_tsk();
}

// 今、コースのどの区間にいるのかを表す変数
static int phase = 0;

bool moveRobo(RoboBody& robo, Tracer& tracer){

  //座標
  const Position& position = robo.calcNewPosition();
  //色識別
  colorid_t colorNumber = robo.getColorNumber();
  //colorid_t colorNumber = COLOR_BLUE;

  bool doContinue = true;
  // 以下 positionにより、出力と終了判定を行う。
  ONCE_MORE:
  switch(phase){
    case 0: // スタート直後
    syslog(LOG_NOTICE,"switch to case 0 ************************");
    //syslog(LOG_NOTICE,"position:" + position.toString());
      if(0.1 < position.x){ // 最初の直線を過ぎたら次のフェーズに
      syslog(LOG_NOTICE,"switch to case 1 ************************");
        phase = 1;
        goto ONCE_MORE;
      }
      tracer.moveRoboPID(robo,70); // 全速力で走る
      break;

    case 1: // 最初のカーブ
      if(colorNumber == COLOR_BLUE){ // 青と交わるところで次の処理に
      syslog(LOG_NOTICE,"switch to case 2 ************************");
        phase = 2;
        goto ONCE_MORE;
      }
      tracer.moveRoboPID(robo,50); // ちょっとスピードを抑える 
      break;
    
    case 2 ://最初の青判定(無視して一周させる)
        if(colorNumber != COLOR_BLUE){ //青が見えなくなったら次の処理に(前と同じ動きやけど)
      syslog(LOG_NOTICE,"switch to case 3 ************************");
        phase = 3;
        goto ONCE_MORE;
      }
      tracer.moveRoboPID(robo,50);
      break;
    case 3:
        if(colorNumber == COLOR_BLUE){ //一周した後の青判定(今回は次のコースに行かせる)
      syslog(LOG_NOTICE,"switch to case 4 ************************");
        phase = 4;
        goto ONCE_MORE;
        }
      tracer.moveRoboPID(robo,50);
      break;
    case 4:
        if(colorNumber != COLOR_BLUE){ //青が見えなくなったら次の処理に
        syslog(LOG_NOTICE,"switch to case 5 ************************");
        phase = 5;
        goto ONCE_MORE;
        }
        tracer.changemoveRoboPID(robo,50);
        break;
    case 5:
         if(1.9 > position.x && -2.0 > position.y){//1週目の青を踏んで勘違いしないように
          syslog(LOG_NOTICE,"switch to case 6 ************************");
          phase = 6;
          goto ONCE_MORE;
         }
         tracer.moveRoboPID(robo,50);
         break;
    case 6:
        if(colorNumber == COLOR_BLUE){//二週目の青が一回目に見えたら次の処理に
          syslog(LOG_NOTICE,"switch to case7  ************************");
          phase = 7;
          goto ONCE_MORE;
        }
        tracer.moveRoboPID(robo,50);
        break;

    case 7:
        if(colorNumber != COLOR_BLUE){//一度青が見えなくなったら次の処理に
          syslog(LOG_NOTICE,"switch to case 8 ************************");
          phase = 8;
          goto ONCE_MORE;
        }
        tracer.changemoveRoboPID(robo,50);
        break;
    case 8:
        if(colorNumber == COLOR_BLUE){//二週目の青２回目(今回は無視)
          syslog(LOG_NOTICE,"switch to case 9 ************************");
          phase = 9;
          goto ONCE_MORE;
        }
        tracer.moveRoboPID(robo,50);
        break;
    case 9 :
        if(-0.9 > position.y && -0.8 > position.x){//ゴール地点にきたら止める
          syslog(LOG_NOTICE,"switch to case 10************************");
          phase = 10;
          goto ONCE_MORE;
        }
      tracer.moveRoboPID(robo,50);
      break;
    case 10 :
      syslog(LOG_NOTICE,"switch to case end ************************");
      robo.setPower(0,0);
      doContinue = false;
      break;

    // case 2: // ゴール後の走り
    //   if(2.5 < position.y && 0.9 < position.x){ // 難所直前に着たら次のフェーズに
    //   syslog(LOG_NOTICE,"switch to case 3 ************************");
    //     phase = 3;
    //     goto ONCE_MORE;
    //   }
    //   tracer.moveRoboOnOf(robo,40); // オンオフ制御で確実に進む
    //   break;

    // case 3: // 難所直前
    //   // 今回はここで止まる…あとは任せた！
    //   syslog(LOG_NOTICE,"switch to case 4 ************************");
    //   robo.setPower(0,0);
    //   doContinue = false;
    //   break;

  }
  
  return doContinue;
}

// end::main_task[]
