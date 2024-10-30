#include "Scene.h"
#include <stdio.h>

Scene::Scene(unsigned char scene_no)
	: mcurrent_scene_no(scene_no)
{
	// 各シーンに応じた走行オブジェクトを確保
	switch (mcurrent_scene_no)
	{				
		case 8:
			mRun[mcurrent_scene_no] = new LineTraceRun(LEFT,40,0.5,0,2,35);	//LineTraceL
			break;	
		case 9:
			mRun[mcurrent_scene_no] = new LineTraceRun(LEFT,40,0.5,0,2,40);	//LineTraceL
			break;
		case 29:
			mRun[mcurrent_scene_no] = new LineTraceRun(RIGHT,15,0.5,0,2,40);//LineTraceR
			break;

			mRun[mcurrent_scene_no] = new LineSearchRun(40);
			break;
			
		case 0:
		case 4:
		case 15:
		case 19:
		case 25:
			mRun[mcurrent_scene_no] = new StraRun(50);
			break;
		case 11:
			mRun[mcurrent_scene_no] = new StraRun(-50);				//back
			break;
		case 21:
			mRun[mcurrent_scene_no] = new StraRun(-70);				//back
			break;
			
		case 1:
		case 3:
		case 5:
		case 7:
		case 10:
		case 12:
		case 14:
		case 16:
		case 18:
		case 20:
		case 22:
		case 24:
		case 26:
		case 28:
			for(i=0; i<200000; i++){
				mRun[mcurrent_scene_no] = new StraRun(0);			//stop
			}
			break;
			
			mRun[mcurrent_scene_no] = new StraRun(60,1);
			break;
			
			mRun[mcurrent_scene_no] = new StraRun(60,2);
			break;
			
		case 6:
		case 17:
			mRun[mcurrent_scene_no] = new RotateRun(LEFT);	//RotateL
			break;
			
		case 2:
		case 13:
		case 23:
		case 27:
			mRun[mcurrent_scene_no] = new RotateRun(RIGHT);	//RotateR
			break;
		
		default:
			break;
	}

	// 各シーンに応じた判定オブジェクトを確保
	switch (mcurrent_scene_no)
	{
		case 0:
			mJudgeMent[mcurrent_scene_no] = new RunDistJudgeMent(BOTH, 240);
			break;
		case 4:
			mJudgeMent[mcurrent_scene_no] = new RunDistJudgeMent(BOTH, 865);
			break;
		case 15:
			mJudgeMent[mcurrent_scene_no] = new RunDistJudgeMent(BOTH, 200);
			break;
		case 19:
			mJudgeMent[mcurrent_scene_no] = new RunDistJudgeMent(BOTH, 1111);
			break;
		case 25:
			mJudgeMent[mcurrent_scene_no] = new RunDistJudgeMent(BOTH, 430);
			break;

			mJudgeMent[mcurrent_scene_no] = new ColorJudgeMent(BLUE);
			break;
			
			
		case 11:
			mJudgeMent[mcurrent_scene_no] = new RunDistJudgeMent(BOTH, -35);	//back
			break;
		case 21:
			mJudgeMent[mcurrent_scene_no] = new RunDistJudgeMent(BOTH, -55);	//back
			break;
			
		case 1:
		case 3:
		case 5:
		case 7:
		case 10:
		case 12:
		case 14:
		case 16:
		case 18:
		case 20:
		case 22:
		case 24:
		case 26:
		case 28:
			mJudgeMent[mcurrent_scene_no] = new RunDistJudgeMent(BOTH, 0);		//stop
			break;
			
		case 8:
			mJudgeMent[mcurrent_scene_no] = new RunDistJudgeMent(LEFT, 250);	//LineTraceL
			break;
		case 9:
			mJudgeMent[mcurrent_scene_no] = new RunDistJudgeMent(LEFT, 250);	//LineTraceL
			break;
		case 29:
			mJudgeMent[mcurrent_scene_no] = new RunDistJudgeMent(RIGHT, 1111);	//LineTraceR
			break;
			
			mJudgeMent[mcurrent_scene_no] = new RunDistJudgeMent(RIGHT, 80);
			break;
			
			mJudgeMent[mcurrent_scene_no] = new RunDistJudgeMent(RIGHT, 145);
			break;
			
			mJudgeMent[mcurrent_scene_no] = new RunDistJudgeMent(LEFT, 80);
			break;

			mJudgeMent[mcurrent_scene_no] = new RunDistJudgeMent(LEFT, 145);
			break;
			
		case 6:
			mJudgeMent[mcurrent_scene_no] = new RotateAngleJudgeMent(LEFT, -78);	//RotateL
			break;
		case 17:
			mJudgeMent[mcurrent_scene_no] = new RotateAngleJudgeMent(LEFT, -111);	//RotateL
			break;
			
		case 2:
		case 23:
		case 27:
			mJudgeMent[mcurrent_scene_no] = new RotateAngleJudgeMent(RIGHT, 78);	//RotateR
			break;
		case 13:
			mJudgeMent[mcurrent_scene_no] = new RotateAngleJudgeMent(RIGHT, 25);	//RotateR
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
