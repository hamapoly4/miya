#ifdef __cplusplus
extern "C" {
#endif

#include "ev3api.h"
  
/* タスク優先度 */
#define MAIN_PRIORITY   (TMIN_APP_TPRI + 1) // メインタスク

#ifndef STACK_SIZE
#define STACK_SIZE      (4096)
#endif /* STACK_SIZE */

#ifndef TOPPERS_MACRO_ONLY

extern void main_task(intptr_t exinf);

#endif /* TOPPERS_MACRO_ONLY */

/* ここにSPIKE用APIのヘッダファイルをインクルード */
#include "spike/hub/button.h"

#ifdef __cplusplus
}
#endif
