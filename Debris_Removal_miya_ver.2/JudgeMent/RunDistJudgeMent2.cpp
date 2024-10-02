#include "RunDistJudgeMent2.h"
#include <stdio.h>

RunDistJudgeMent2::RunDistJudgeMent2(unsigned char tire, float target_dist)
	: mtire(tire), mtarget_dist1(target_dist), mtarget_dist2(-target_dist)	//target_dist1=(+), target_dist2=(-)
{
	mRunDistDetect1 = new RunDistDetect(RIGHT);
	mRunDistDetect2 = new RunDistDetect(LEFT);
}

RunDistJudgeMent2::~RunDistJudgeMent2()
{
	delete mRunDistDetect1;
	delete mRunDistDetect2;
}

bool RunDistJudgeMent2::judge()
{
	mcurrent_dist1 = mRunDistDetect1->getRunDist();	//current_dist1=RIGHT
	mcurrent_dist2 = mRunDistDetect2->getRunDist();	//current_dist2=LEFT
	
	if(mtire == LEFT)
	{
		if (mcurrent_dist1 >= mtarget_dist1 && mcurrent_dist2 <= mtarget_dist2)
		{
			printf("%fmm走った！！\n", mcurrent_dist2);
			return true;
		}
	}
	else if (mcurrent_dist1 <= mtarget_dist2 && mcurrent_dist2 >= mtarget_dist1)
	{
		printf("%fmm走った！！\n", mcurrent_dist1);
		return true;
	}
	return false;
}
