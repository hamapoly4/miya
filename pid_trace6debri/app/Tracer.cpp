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
  static int left = 45 ,right = 45;
  int left_cnt,right_cnt,sonar=0;
  static int mode=0;
  rgb_raw_t rgb;
  char color,angle,dir,dir_con=0;
  static int turn0_f = 0,turn1_f = 1,turn2_f = 1,turn3_f = 1;
  static int t=0;
  static int brt, get_brt[10] = {0}, brt_cnt = 0;
  int sum_brt = 0, i;
  
  left_cnt = leftWheel.getCount();
  right_cnt = rightWheel.getCount();
  colorSensor.getRawColor(rgb);
  angle = gyrosensor.getAngle();
  color = color_set(rgb);
  
  //bright_data->average(10count)
  if(t%10==0){
    get_brt[brt_cnt] = colorSensor.getBrightness();
  
    brt_cnt++;
    if(brt_cnt>9)
      brt_cnt=0;
    
    for(i=0;i<10;i++)
      sum_brt+=get_brt[i];
      
    //t<90 = data_array isn't fill
    if(t<90)
      brt = sum_brt / brt_cnt;
    else
      brt = sum_brt / 10;
  }
//  sonar = sonarsensor.getDistance();

  //mode:0
  if(mode==0){
    if(color=='B'){
      printf("\n***mode:1!!***\nleft:%d right:%d\n",left_cnt,right_cnt);
      printf("red:%d green:%d blue:%d color:%c angle:%d\n\n",rgb.r,rgb.g,rgb.b,color,angle);

      mode=1;
      left=60,right=60;
    }
    //omoshiro -> if,delete
    else{
      if(t%MOT_CON==0){
        if(color!='B'&&color!='K'){
          if( angle>0 ){
            if(left>right){
              left=45-dir_con,right=45+dir_con;
              dir_con = dir_con*2/3;
            }
            left-=2;
            right+=2;
            dir_con++;
          }
          else if( angle<0 ){
            if(left<right){
              left=45-dir_con,right=45+dir_con;
              dir_con = dir_con*2/3;
            }
            left+=2;
            right-=2;
            dir_con--;
          }
        }
        else{
          left=45-dir_con,right=45+dir_con;
          dir_con = dir_con*2/3;
        }
      }
    }
  }
  //mode:1
  if(mode==1){
    if(t%MOT_CON==0){
      if(left_cnt>1500 && (angle>-4 && angle<4) ){
        left=30-dir_con,right=30+dir_con;
        dir_con = dir_con*2/3;
      }
      else {
        if(color!='B'&&color!='K'){
          if( angle>0 ){
            if(left>right){
              left=60-dir_con,right=60+dir_con;
              dir_con = dir_con*2/3;
            }
            left-=2;
            right+=2;
            dir_con++;
          }
          else if( angle<0 ){
            if(left<right){
              left=60-dir_con,right=60+dir_con;
              dir_con = dir_con*2/3;
            }
            left+=2;
            right-=2;
            dir_con--;
          }
        }
        else{
          left=60-dir_con,right=60+dir_con;
          dir_con = dir_con*2/3;
        }
      }
    }
    if(color=='K'){
      turn0_f=1;
    }
    if(color=='B'&&turn0_f){
      printf("\n***mode:2!!***\nleft:%d right:%d\n",left_cnt,right_cnt);
      printf("red:%d green:%d blue:%d color:%c angle:%d\n\n",rgb.r,rgb.g,rgb.b,color,angle);

      mode=2;
      left=60,right=15;
    }
  }

  //mode:2
  if(mode==2 && angle>82 && turn1_f){
      printf("\n***mode:3!!***\nleft:%d right:%d\n",left_cnt,right_cnt);
      printf("red:%d green:%d blue:%d color:%c angle:%d\n\n",rgb.r,rgb.g,rgb.b,color,angle);
    turn1_f=0;
    mode=3;
    left=60,right=60;
  }
  //mode:3
  if(mode==3 && t%MOT_CON==0){
    if( angle>93 ){
      if(left>right){
        left=60-dir_con,right=60+dir_con;
        dir_con = dir_con*2/3;
      }
      left-=2;
      right+=2;
      dir_con++;
    }
    else if( angle<87 ){
      if(left<right){
        left=60-dir_con,right=60+dir_con;
        dir_con = dir_con*2/3;
      }
      left+=2;
      right-=2;
      dir_con--;
    }
    else {
      if(left_cnt>4000 && (angle>85 && angle<95) ){
        left=30-dir_con,right=30+dir_con;
        dir_con = dir_con*2/3;
      }
      else{
        left=60-dir_con,right=60+dir_con;
        dir_con = dir_con*2/3;
      }
    }
  }
  //mode:4
  if(turn2_f && left_cnt>4000 && color=='K'){
    mode=4;
    left =-15 ,right = 45;
  }
  if(mode==4 && angle<0){
    printf("\n***mode:5!!***\nleft:%d right:%d\n",left_cnt,right_cnt);
    printf("red:%d green:%d blue:%d color:%c angle:%d\n\n",rgb.r,rgb.g,rgb.b,color,angle);
    turn2_f=0;
    mode=5;
    left = 60,right = 60;
    dir_con=5;
  }
  //mode:5
  if(mode==5 && t%MOT_CON==0){
    if(color=='K'){
      left=60-dir_con,right=60+dir_con;
      dir_con = dir_con*2/3;
    }
    else {
      if( angle>0 ){
        if(left>right){
          left=60-dir_con,right=60+dir_con;
          dir_con = dir_con*2/3;
        }
        left-=2;
        right+=2;
        dir_con++;
      }
      else if( angle<0 ){
        if(left<right){
          left=60-dir_con,right=60+dir_con;
          dir_con = dir_con*2/3;
        }
        left+=2;
        right-=2;
        dir_con--;
      }
    }
  }
  //mode:6(stop)
  if(left_cnt>5800){
    left = 0;
    right = 0;
    mode=6;
  }
  
  leftWheel.setPWM(left);
  rightWheel.setPWM(right);
  
  if(t%25==0 && mode!=6){
    printf("mode:%d left:%d,right:%d l_speed:%d r_speed:%d dir:%d\n",mode,left_cnt,right_cnt,left,right,dir_con);
    printf("red:%d green:%d blue:%d color:%c angle:%d bright:%d\n",rgb.r,rgb.g,rgb.b,color,angle,brt);
    for(i=0;i<10;i++)
      printf("%d:%d ",i,get_brt[i]);
    puts("\n");
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
