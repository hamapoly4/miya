#include "LineTraceRun.h"
#include <stdio.h>

LineTraceRun::LineTraceRun(unsigned char edge, int threshold, float pgein, float igein, float dgein, int pwm)
	: medge(edge), Run(pwm)
{
	mPDcon = new PDcon(mLINETRACE, threshold, pgein, igein, dgein);
}
/*-------BLUE-------*/
//	threshold = 40;
//	pgein = 0.5;
//	igein = 0;
//	dgein = 2;

/*-------BLACK?-------*/
//	threshold = 40;
//	pgein = 0.5;
//	igein = 0.025;
//	dgein = 2;

LineTraceRun::~LineTraceRun()
{
	delete mPDcon;
}

void LineTraceRun::run()
{
	mturn = mPDcon->getTurn();
	if (medge == RIGHT)
	{
		LeftMotor.setPWM(mfix_pwm - mturn);
		RightMotor.setPWM(mfix_pwm + mturn);
	}
	else if (medge == LEFT)
	{
		LeftMotor.setPWM(mfix_pwm + mturn);
		RightMotor.setPWM(mfix_pwm - mturn);
	}
	//printf("LineTrace Run!!\n");
	//printf("pwm is %d\n", mfix_pwm);

}
