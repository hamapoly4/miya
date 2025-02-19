﻿#include "RunDistJudgeMent.h"
#include <stdio.h>

RunDistJudgeMent::RunDistJudgeMent(float target_dist, RunDistDetect* rundistdetect)
	: mtarget_dist(target_dist), mRunDistDetect(rundistdetect)
{
	;
}

bool RunDistJudgeMent::judge()
{
	mcurrent_dist = mRunDistDetect->getRunDist();

	if(0 > mtarget_dist)
	{
		if (mcurrent_dist <= mtarget_dist)
		{
			printf("%fmm走った！！\n", mcurrent_dist);
			return true;
		}
	}
	else if (mcurrent_dist >= mtarget_dist)
	{
		printf("%fmm走った！！\n", mcurrent_dist);
		return true;
	}
	return false;
}
