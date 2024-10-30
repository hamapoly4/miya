#include "StraRun.h"
#include <stdio.h>

StraRun::StraRun(int pwm,char mode)
	: Run(pwm), Mode(mode)	//mode0:stra 1:left 2:right
{
	mPDcon = new PDcon(mSTRAIGHT, 0, 1.5, 0, 3);
}

StraRun::~StraRun()
{
	delete mPDcon;
}

void StraRun::run()
{
	mturn = mPDcon->getTurn();
	switch(Mode){
		case 0:
			LeftMotor.setPWM(mfix_pwm - mturn);
			RightMotor.setPWM(mfix_pwm + mturn);
			break;
		case 1:
			LeftMotor.setPWM(mfix_pwm - mturn);
			RightMotor.setPWM(mfix_pwm + mturn +8);
			break;
		case 2:
			LeftMotor.setPWM(mfix_pwm - mturn +8);
			RightMotor.setPWM(mfix_pwm + mturn);
			break;
	}
	
	//printf("Straight Run!!\n");
	//printf("pwm is %d\n", mfix_pwm);
}
