#include "Tracer.h" // <1>
#define MOT_CON 10

static int left = 0 ,right = 0 ,cent = 0;
int left_cnt,right_cnt,cent_cnt;
int angle,sonar=0;
char color,dir,dir_con=0;
static int mode=0;
rgb_raw_t rgb;
static int start_f = 1;
static int turn0_f = 0,turn1_f = 1,turn2_f = 1,turn3_f = 1;
static int brt, get_brt[10] = {0}, brt_cnt = 0;
int sum_brt, i;

Tracer::Tracer():
  leftWheel(PORT_C), rightWheel(PORT_B), centralWheel(PORT_A), colorSensor(PORT_2), gyrosensor(PORT_4) { // <2>
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
  
  //initialize
  if(start_f){
    gyrosensor.reset();
    leftWheel.reset();
    rightWheel.reset();
    if(t<5){
      cent = -20;
      centralWheel.reset();
    }
    else
      set_colorsensor();
  }
  //motor
  left_cnt = leftWheel.getCount();
  right_cnt = rightWheel.getCount();
  cent_cnt = centralWheel.getCount();
  
  centralWheel.setBrake(true);
  
  colorSensor.getRawColor(rgb);
  angle = gyrosensor.getAngle();
  color = color_set(rgb);
  
  //bright_data->average(10count)
  if(t%10==0){
    sum_brt = 0;
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
    if(t%MOT_CON==0){
      run_straight(0);
    }
    if(left_cnt>1000)
      run_straight(0);
  }
  //mode:1(直進Straight)
  if(mode==1){
    if(t%MOT_CON==0){
      if(left_cnt>1500){
        if(angle>-4 && angle<4)
          run_straight(30);
      }
      else {
        if(color!='B'&&color!='K'){
          angle_fix(60,0,1);
        }
        else{
          run_straight(60);
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

  //mode:2(右に曲がるTurn right)
  if(mode==2 && angle>80 && turn1_f){
      printf("\n***mode:3!!***\nleft:%d right:%d\n",left_cnt,right_cnt);
      printf("red:%d green:%d blue:%d color:%c angle:%d\n\n",rgb.r,rgb.g,rgb.b,color,angle);
    turn1_f=0;
    mode=3;
    left=60,right=60;
  }
  //mode:3(横断走行Crossing)
  if(mode==3 && t%MOT_CON==0){
    if(angle<87 || angle>93 )
      angle_fix(60,90,0);
    else {
      if(left_cnt>4000 && (angle>85 && angle<95) ){
        run_straight(30);
      }
      else{
        run_straight(60);
      }
    }
  }
  //mode:4(左に曲がるTurn left)
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
  //mode:5(ライントレースで進むProceed with line tracing)
  if(mode==5 && t%MOT_CON==0){
    if(color=='K'){
      run_straight(60);
    }
    else {
      angle_fix(60,0,1);
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
  centralWheel.setPWM(cent);
  
  if(t%5==0 && mode!=6){
    printf("mode:%d left:%d,right:%d cent:%d l_speed:%d r_speed:%d c_speed:%d\n",mode,left_cnt,right_cnt,cent_cnt,left,right,cent);
    printf("red:%d green:%d blue:%d color:%c angle:%d bright:%d\n",rgb.r,rgb.g,rgb.b,color,angle,brt);
    puts("\n");
  }
  t++;
}

//function
char color_set(rgb_raw_t & rgb)
{
    char c;
    if(rgb.r<10&&rgb.g<10&&rgb.b<10)      //Black
      c='K';
    else if(rgb.r>50&&rgb.g>50&&rgb.b>50) //White
      c='W';
    else if(rgb.r<20&&rgb.g<25&&rgb.b>28) //Blue
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
//まっすぐタイヤ調整
void run_straight(int spd)
{
  left=spd+(dir_con*2/3),right=spd-(dir_con*2/3);
  dir_con = dir_con/2;
}
//爪
char set_colorsensor(void)
{
  char flag = 1;
  if(cent_cnt>80)
    cent = 0,flag = 0;
  else
    cent = 20,flag = 1;
  return flag;
}
