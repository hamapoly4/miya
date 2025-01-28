#include "Scene.h"
#include <stdio.h>

Scene::Scene(unsigned char scene_no)
	: mcurrent_scene_no(scene_no)
{
	// 各シーンに応じた走行オブジェクトを確保
	switch (mcurrent_scene_no)
	{
		case 0:
		case 6:
		case 12:
		case 18:
		case 24:
		case 30:
		case 36:
		case 42:
		case 48:
		case 54:
			mRun[mcurrent_scene_no] = new StraRun(50);
			break;
			
		case 2:
		case 8:
		case 14:
		case 20:
		case 26:
		case 32:
		case 38:
		case 44:
		case 50:
			mRun[mcurrent_scene_no] = new StraRun(-50);
			break;
			
		case 4:
		case 22:
		case 28:
		case 34:
		case 52:
			mRun[mcurrent_scene_no] = new RotateRun(LEFT);
			break;
			
		case 10:
		case 16:
		case 40:
		case 46:
			mRun[mcurrent_scene_no] = new RotateRun(RIGHT);
			break;
			
		default:
			for(i=0;i<200000;i++){
				mRun[mcurrent_scene_no] = new StraRun(0);
			}
			break;
	}

	// 各シーンに応じた判定オブジェクトを確保
	switch (mcurrent_scene_no)
	{
		case 0:
			mJudgeMent[mcurrent_scene_no] = new RunDistJudgeMent(BOTH, 340);	//start
			break;
		case 12:
		case 30:
		case 36:
		case 42:
		case 48:
			mJudgeMent[mcurrent_scene_no] = new RunDistJudgeMent(BOTH, 385);	//1block	block*360+35
			break;
		case 24:
			mJudgeMent[mcurrent_scene_no] = new RunDistJudgeMent(BOTH, 755);	//2block
			break;
		case 6:
		case 18:
			mJudgeMent[mcurrent_scene_no] = new RunDistJudgeMent(BOTH, 1115);	//3block
			break;
		case 54:
			mJudgeMent[mcurrent_scene_no] = new RunDistJudgeMent(BOTH, 360);	//end
			break;
			
		case 2:
		case 8:
		case 14:
		case 20:
		case 26:
		case 32:
		case 38:
		case 44:
		case 50:
			mJudgeMent[mcurrent_scene_no] = new RunDistJudgeMent(BOTH, -50);	//back
			break;
			
		case 4:
			mJudgeMent[mcurrent_scene_no] = new RunDistJudgeMent2(LEFT, 72);
			break;
		case 22:
		case 28:
		case 34:
		case 52:
			mJudgeMent[mcurrent_scene_no] = new RunDistJudgeMent2(LEFT, 80);
			break;
		
		case 10:
		case 16:
		case 40:
		case 46:
			mJudgeMent[mcurrent_scene_no] = new RunDistJudgeMent2(RIGHT, 85);
			break;
		
		default:
			mJudgeMent[mcurrent_scene_no] = new RunDistJudgeMent(BOTH, 0);
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
