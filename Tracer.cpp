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
  static int left = 40 ,right = 40;
  int left_cnt,right_cnt,sonar=0;
  static int mode=0;
  rgb_raw_t rgb;
  char color,angle,dir,dir_con=0;
  static int turn0_f = 0,turn1_f = 1,turn2_f = 1,turn3_f = 1;
  static int t=0;
  
  left_cnt = leftWheel.getCount();
  right_cnt = rightWheel.getCount();
  colorSensor.getRawColor(rgb);
  angle = gyrosensor.getAngle();
  color = color_set(rgb);
//  sonar = sonarsensor.getDistance();

  if(mode==0 && color=='B'){
      mode=1;
      left=60,right=60;
  }
  if(mode==1){
    if(color!='B'&&color!='K'){
      if( angle>3 ){
        left-=4;
        right+=2;
        dir_con++;
      }
      else if( angle<-3 ){
        left+=2;
        right-=4;
        dir_con--;
      }
    }
    else{
      if(color=='K'){
        turn0_f=1;
      }
      left=60-dir_con,right=60+dir_con;
      dir_con/=2;
    }
    if(color=='B'&&turn0_f){
      mode=2;
    }
  }

  //turn -> message
  if(mode==2 && angle>82 && turn1_f){
    printf("\nturn right!! left:%d right:%d angle:%d\n\n",left_cnt,right_cnt,angle);
    turn1_f=0;
    mode=3;
    left=60,right=60;
  }
  //after right_turn
  if(mode==3 && t%MOT_CON==0){
    if( angle>93 ){
      left-=4;
      right+=2;
      dir_con++;
    }
    else if( angle<87 ){
      left+=2;
      right-=4;
      dir_con--;
    }
    else {
      if(left_cnt>3000){
        left=30,right=30;
      }
      else{
        left=60-dir_con,right=60+dir_con;
        dir_con/=2;
      }
    }
  }
  if(turn2_f && left_cnt>3000 && color=='K'){
    mode=4;
    left = -30,right = 60;
    if(angle<15){
      printf("\nturn left!! left:%d right:%d\n",left_cnt,right_cnt);
      printf("red:%d green:%d blue:%d color:%c angle:%d\n\n",rgb.r,rgb.g,rgb.b,color,angle);
      turn2_f=0;
      mode=5;
      left = 60,right = 60;
      dir_con=0;
    }
  }
  //after left_turn
  if(mode==5 && t%MOT_CON==0){
    if(color=='K'){
      left=60-dir_con,right=60+dir_con;
      dir_con/=2;
    }
    else {
      if( angle>3 ){
        left-=4;
        right+=2;
        dir_con++;
      }
      else if( angle<-3 ){
        left+=2;
        right-=4;
        dir_con--;
      }
      else{
        left=60-dir_con,right=60+dir_con;
        dir_con/=2;
      }
    }
  }
  if(left_cnt>4200){
    left = 0;
    right = 0;
    mode=6;
  }
  
  leftWheel.setPWM(left);
  rightWheel.setPWM(right);
  
  if(t%25==0 && mode!=6){
    printf("mode:%d left:%d,right:%d l_speed:%d r_speed:%d dir:%d\n",mode,left_cnt,right_cnt,left,right,dir_con);
    printf("red:%d green:%d blue:%d color:%c angle:%d sonar:%d\n\n",rgb.r,rgb.g,rgb.b,color,angle,sonar);
  }
  t++;
}
char color_set(rgb_raw_t & rgb)
{
    char c;
    if(rgb.r<10&&rgb.g<10&&rgb.b<10)      //Black
      c='K';
    else if(rgb.r>50&&rgb.g>50&&rgb.b>50) //White
      c='W';
    else if(rgb.r<20&&rgb.g<20&&rgb.b>25) //Blue
      c='B';
    else
      c='A';                             //Another
    return c;
}
