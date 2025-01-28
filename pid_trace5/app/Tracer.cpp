#include "Tracer.h" // <1>
#define MOT_CON 10

static int left = 45 ,right = 45;
static int l_def_cnt,r_def_cnt;
int left_cnt,right_cnt,angle,sonar=0;
char color,dir,dir_con=0;
static int mode=0;
rgb_raw_t rgb;
static int start_f = 1,turn0_f = 0,turn1_f = 1,turn2_f = 1,turn3_f = 1;
static int brt, get_brt[10] = {0}, brt_cnt = 0;
int sum_brt, i;

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
  static int t=0;
  
  if(start_f){
    gyrosensor.reset();
    l_def_cnt = leftWheel.getCount();
    r_def_cnt = rightWheel.getCount();
    start_f = 0;
  }
  
  left_cnt = leftWheel.getCount() -l_def_cnt;
  right_cnt = rightWheel.getCount() -r_def_cnt;
  colorSensor.getRawColor(rgb);
  angle = gyrosensor.getAngle();
  color = color_set(rgb);
  
  if(t%10==0){
    printf("angle:%d\n",angle);
  }
  t++;
}
//  sonar = sonarsensor.getDistance();


char color_set(rgb_raw_t & rgb)
{
    char c;
    if(rgb.r<10&&rgb.g<10&&rgb.b<10)      //黒
      c='K';
    else if(rgb.r>50&&rgb.g>50&&rgb.b>50) //白
      c='W';
    else if(rgb.r<20&&rgb.g<25&&rgb.b>28) //青
      c='B';
    else
      c='A';                              //Another
    return c;
}
void angle_fix(int spd,int ag,int type)
{
  char cond1, cond2;
  
  //type0:gyro only type1:linetrace
  if(type){
    cond1 = (angle>ag);
    cond2 = (angle<ag);
  }
  else {
    cond1 = (angle>ag+3);
    cond2 = (angle<ag-3);
  }
  //right->left
  if( cond1 ){
    if(left>right){
      run_straight(spd);
    }
    left-=1;
    right+=1;
    dir_con++;
  }
  //left->right
  else if( cond2 ){
    if(left<right){
      run_straight(spd);
    }
    left+=1;
    right-=1;
    dir_con--;
  }
}
void run_straight(int spd)
{
  left=spd+(dir_con*2/3),right=spd-(dir_con*2/3);
  dir_con = dir_con/2;
}
