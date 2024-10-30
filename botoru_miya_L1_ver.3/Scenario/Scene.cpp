#include "Scene.h"
#include <stdio.h>

Scene::Scene(unsigned char scene_no)
	: mcurrent_scene_no(scene_no)
{
	// 各シーンに応じた走行オブジェクトを確保
	switch (mcurrent_scene_no)
	{	
		case 60:	
			mRun[mcurrent_scene_no] = new LineTraceRun(RIGHT,40,0.5,0,2,35);	//LineTraceR
			break;
		case 61:	
			mRun[mcurrent_scene_no] = new LineTraceRun(RIGHT,40,0.5,0,2,40);	//LineTraceR
			break;
		case 81:
			mRun[mcurrent_scene_no] = new LineTraceRun(RIGHT,25,0.5,0,2,40);	//LineTraceR
			break;

			mRun[mcurrent_scene_no] = new LineSearchRun(40);
			break;
			
		case 0:
		case 4:
		case 8:
		case 19:
		case 30:
		case 41:
		
		case 52:
		case 56:
		case 67:
		case 71:
		case 77:
			mRun[mcurrent_scene_no] = new StraRun(50);
			break;
		case 63:
			mRun[mcurrent_scene_no] = new StraRun(-50);				//back
			break;
		case 73:
			mRun[mcurrent_scene_no] = new StraRun(-70);				//back
			break;
			
		case 1:
		case 3:
		case 5:
		case 7:
		case 9:
		/*-------botoru1-------*/
		case 11:	//stop
		case 12:	//handan
		case 13:	//go
		case 14:	//stop
		case 15:	//back
		case 16:	//stop
		/*---------------------*/
		
		case 18:
		case 20:
		
		/*-------botoru2-------*/
		case 22:	//stop
		case 23:	//handan
		case 24:	//go
		case 25:	//stop
		case 26:	//back
		case 27:	//stop
		/*---------------------*/
		
		case 29:
		case 31:
		
		/*-------botoru3-------*/
		case 33:	//stop
		case 34:	//handan
		case 35:	//go
		case 36:	//stop
		case 37:	//back
		case 38:	//stop
		/*---------------------*/
		
		case 40:
		case 42:
		
		/*-------botoru4-------*/
		case 44:	//stop
		case 45:	//handan
		case 46:	//go
		case 47:	//stop
		case 48:	//back
		case 49:	//stop
		/*---------------------*/
		case 51:
		
		case 53:
		case 55:
		case 57:
		case 59:
		case 62:
		case 64:
		case 66:
		case 68:
		case 70:
		case 72:
		case 74:
		case 76:
		case 78:
		case 80:

			for(i=0; i<200000; i++){
				mRun[mcurrent_scene_no] = new StraRun(0);			//stop
			}
			break;
			
			mRun[mcurrent_scene_no] = new StraRun(60,1);
			break;
			
			mRun[mcurrent_scene_no] = new StraRun(60,2);
			break;
			
		case 2:
		case 10:
		case 28:
		case 32:
		case 43:

		case 58:
		case 69:
			mRun[mcurrent_scene_no] = new RotateRun(RIGHT);	//RotateR
			break;
		
		case 6:
		case 17:
		case 21:
		case 39:
		case 50:
		
		case 54:
		case 65:
		case 75:
		case 79:
			mRun[mcurrent_scene_no] = new RotateRun(LEFT);	//RotateL
			break;
		
		default:
			break;
	}
	
	

	// 各シーンに応じた判定オブジェクトを確保
	switch (mcurrent_scene_no)
	{
		case 0:
			mJudgeMent[mcurrent_scene_no] = new RunDistJudgeMent(BOTH, 80);
			break;
		case 4:
			mJudgeMent[mcurrent_scene_no] = new RunDistJudgeMent(BOTH, 160);
			break;
		case 8:
			mJudgeMent[mcurrent_scene_no] = new RunDistJudgeMent(BOTH, 250);
			break;
		case 19:
			mJudgeMent[mcurrent_scene_no] = new RunDistJudgeMent(BOTH, 690);
			break;
		case 30:
			mJudgeMent[mcurrent_scene_no] = new RunDistJudgeMent(BOTH, 690);
			break;
		case 41:
			mJudgeMent[mcurrent_scene_no] = new RunDistJudgeMent(BOTH, 600);
			break;

		case 52:
			mJudgeMent[mcurrent_scene_no] = new RunDistJudgeMent(BOTH, 245);
			break;
		case 56:
			mJudgeMent[mcurrent_scene_no] = new RunDistJudgeMent(BOTH, 865);
			break;
		case 67:
			mJudgeMent[mcurrent_scene_no] = new RunDistJudgeMent(BOTH, 200);
			break;
		case 71:
			mJudgeMent[mcurrent_scene_no] = new RunDistJudgeMent(BOTH, 1111);
			break;
		case 77:
			mJudgeMent[mcurrent_scene_no] = new RunDistJudgeMent(BOTH, 430);
			break;
			
			mJudgeMent[mcurrent_scene_no] = new ColorJudgeMent(BLUE);
			break;
			
			
		case 63:
			mJudgeMent[mcurrent_scene_no] = new RunDistJudgeMent(BOTH, -35);	//back
			break;
		case 73:
			mJudgeMent[mcurrent_scene_no] = new RunDistJudgeMent(BOTH, -55);	//back
			break;
			
		case 1:
		case 3:
		case 5:
		case 7:
		case 9:
		/*-------botoru1-------*/
		case 11:	//stop
		case 12:	//handan
		case 13:	//go
		case 14:	//stop
		case 15:	//back
		case 16:	//stop
		/*---------------------*/
		
		case 18:
		case 20:
		
		/*-------botoru2-------*/
		case 22:	//stop
		case 23:	//handan
		case 24:	//go
		case 25:	//stop
		case 26:	//back
		case 27:	//stop
		/*---------------------*/
		
		case 29:
		case 31:
		
		/*-------botoru3-------*/
		case 33:	//stop
		case 34:	//handan
		case 35:	//go
		case 36:	//stop
		case 37:	//back
		case 38:	//stop
		/*---------------------*/
		
		case 40:
		case 42:
		
		/*-------botoru4-------*/
		case 44:	//stop
		case 45:	//handan
		case 46:	//go
		case 47:	//stop
		case 48:	//back
		case 49:	//stop
		/*---------------------*/
		case 51:
		
		case 53:
		case 55:
		case 57:
		case 59:
		case 62:
		case 64:
		case 66:
		case 68:
		case 70:
		case 72:
		case 74:
		case 76:
		case 78:
		case 80:
			mJudgeMent[mcurrent_scene_no] = new RunDistJudgeMent(BOTH, 0);		//stop
			break;
			
		case 60:
			mJudgeMent[mcurrent_scene_no] = new RunDistJudgeMent(RIGHT, 250);	//LineTraceR
			break;
		case 61:
			mJudgeMent[mcurrent_scene_no] = new RunDistJudgeMent(RIGHT, 250);	//LineTraceR
			break;
		case 81:
			mJudgeMent[mcurrent_scene_no] = new RunDistJudgeMent(LEFT, 1111);	//LineTraceL
			break;
			
		case 2:
			mJudgeMent[mcurrent_scene_no] = new RotateAngleJudgeMent(RIGHT, 52);	//RotateR
			break;
		case 10:
		case 43:
			mJudgeMent[mcurrent_scene_no] = new RotateAngleJudgeMent(RIGHT, 40);	//RotateR
			break;
		case 28:
		case 32:
			mJudgeMent[mcurrent_scene_no] = new RotateAngleJudgeMent(RIGHT, 124);	//RotateR
			break;
			
		case 6:
			mJudgeMent[mcurrent_scene_no] = new RotateAngleJudgeMent(LEFT, -50);	//RotateL
			break;
		case 17:
		case 21:
			mJudgeMent[mcurrent_scene_no] = new RotateAngleJudgeMent(LEFT, -40);	//RotateL
			break;
		case 39:
			mJudgeMent[mcurrent_scene_no] = new RotateAngleJudgeMent(LEFT, -37);	//RotateL
			break;
		case 50:
			mJudgeMent[mcurrent_scene_no] = new RotateAngleJudgeMent(LEFT, -120);	//RotateL
			break;
			
		case 58:
			mJudgeMent[mcurrent_scene_no] = new RotateAngleJudgeMent(RIGHT, 78);	//RotateR
			break;
		case 69:
			mJudgeMent[mcurrent_scene_no] = new RotateAngleJudgeMent(RIGHT, 111);	//RotateR
			break;
			
		case 54:
		case 75:
		case 79:
			mJudgeMent[mcurrent_scene_no] = new RotateAngleJudgeMent(LEFT, -78);	//RotateL
			break;
		case 65:
			mJudgeMent[mcurrent_scene_no] = new RotateAngleJudgeMent(LEFT, -25);	//RotateL
			break;
			
		default:
			break;
	}
}

Scene::~Scene()
{
	delete mRun[mcurrent_scene_no];
	delete mJudgeMent[mcurrent_scene_no];

	printf("シーン番号：%d シーンオブジェクトの解放！！\n\n", mcurrent_scene_no + 1);
}

void Scene::run()
{
	mRun[mcurrent_scene_no]->run();
}

bool Scene::fin_judge()
{
	return mJudgeMent[mcurrent_scene_no]->judge();
}
