// tag::walker_def[]
#include "app.h"
#include "util.h"

#include "Motor.h"
#include "Clock.h"

using namespace ev3api;


// tag::main_task[]
void main_task(intptr_t unused) {

  system("cd /home/user/camera/ && ./capture");
  ext_tsk();
}
// end::main_task[]
