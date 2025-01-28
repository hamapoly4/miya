#include "Tracer.h" // <1>
#define MOT_CON 20
Tracer::Tracer():
  leftWheel(PORT_C), rightWheel(PORT_B), colorSensor(PORT_2), gyrosensor(PORT_4) { // <2>
  }

void Tracer::init() {
  init_f("Tracer");
}

void Tracer::terminate() {
  msg_f("Stopped.", 1);
  leftWheel.stop();  // <1>
  rightWheel.stop();
}

void Tracer::run() {
  static int left = 60 ,right = 15;
  int left_cnt,right_cnt;
  rgb_raw_t rgb;
  int angle;
  static int turn1_f = 1,turn2_f = 1,turn3_f = 1;
  static int t=0;
  
  left_cnt = leftWheel.getCount();
  right_cnt = rightWheel.getCount();
  colorSensor.getRawColor(rgb);
  angle = gyrosensor.getAngle();
  
  if(angle>85){
    //turn -> message
    if(turn1_f){
      printf("\nturn right!! left:%d right:%d angle:%d\n\n",left_cnt,right_cnt,angle);
      turn1_f=0;
      left=60,right=60;
    }
  }
  //after right_turn
  if(1-turn1_f && turn2_f && t%MOT_CON==0){
    if( angle>93 ){
      left-=3;
      right+=3;
    }
    else if( angle<87 ){
      left+=3;
      right-=3;
    }
    else {
      left=60,right=60;
    }
  }
  if(turn3_f && left_cnt>2500){
    turn2_f=0;
    left = 15,right = 60;
    if(angle<5){
      printf("\nturn left!! left:%d right:%d angle:%d\n\n",left_cnt,right_cnt,angle);
      turn3_f=0;
      left = 60,right = 60;
    }
  }
  //after left_turn
  if(1-turn3_f && t%MOT_CON==0){
    if( angle>3 ){
      left-=3;
      right+=3;
    }
    else if( angle<-3 ){
      left+=3;
      right-=3;
    }
    else {
      left=60,right=60;
    }
  }
  if(left_cnt>3600){
    left = 0;
    right = 0;
  }
  
  leftWheel.setPWM(left);
  rightWheel.setPWM(right);
  
  if(t%50==0){
    printf("left:%d,right:%d l_speed:%d r_speed:%d\n",left_cnt,right_cnt,left,right);
    printf("red:%d green:%d blue:%d angle:%d\n\n",rgb.r,rgb.g,rgb.b,angle);
  }
  t++;
}
