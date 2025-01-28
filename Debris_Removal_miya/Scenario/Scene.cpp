#include "Scene.h"
#include <stdio.h>

Scene::Scene(unsigned char scene_no)
	: mcurrent_scene_no(scene_no)
{
	// 各シーンに応じた走行オブジェクトを確保
	switch (mcurrent_scene_no)
	{			
		case 0:
			mRun[mcurrent_scene_no] = new LineTraceRun(RIGHT,40);
			break;
			
		case 1:
			mRun[mcurrent_scene_no] = new LineSearchRun(35);
			break;
			
		case 2:
		case 14:
		case 20:
		case 32:
		case 41:
		case 47:
		case 53:
		case 59:
		case 65:
		case 71:
			mRun[mcurrent_scene_no] = new StraRun(60);
			break;
			
		case 6:
		case 18:
		case 24:
		case 36:
		case 45:
		case 51:
		case 57:
		case 63:
		case 69:
		
		case 9:
		case 12:
		case 27:
		case 30:
		case 39:
			mRun[mcurrent_scene_no] = new StraRun(50);
			break;
			
		case 8:
		case 11:
		case 26:
		case 29:
		case 38:
			mRun[mcurrent_scene_no] = new RotateRun(LEFT);
			break;
		
		case 4:
		case 16:
		case 22:
		case 34:
		case 43:
		case 49:
		case 55:
		case 61:
		case 67:
			mRun[mcurrent_scene_no] = new StraRun(-50);
			break;
			
		case 3:
		case 15:
		case 21:
		case 33:
		case 42:
		case 48:
		case 54:
		case 60:
		case 66:
			for(i=0; i<200000; i++){
				mRun[mcurrent_scene_no] = new StraRun(0);
			}
			break;
			
		case 7:
		case 10:
		case 13:
		case 19:
		case 25:
		case 28:
		case 31:
		case 37:
		case 40:
		case 46:
		case 52:
		case 58:
		case 64:
		case 70:
			mRun[mcurrent_scene_no] = new LineTraceRun(LEFT,50);
			break;
	
		case 5:
		case 35:
		case 44:
		case 50:
		case 68:
			mRun[mcurrent_scene_no] = new RotateRun(LEFT);
			break;
			
		case 17:
		case 23:
		case 56:
		case 62:
			mRun[mcurrent_scene_no] = new RotateRun(RIGHT);
			break;
		
		default:
			break;
	}

	// 各シーンに応じた判定オブジェクトを確保
	switch (mcurrent_scene_no)
	{
		case 0:
			mJudgeMent[mcurrent_scene_no] = new RunDistJudgeMent(BOTH, 150);
			break;
			
		case 1:
			mJudgeMent[mcurrent_scene_no] = new ColorJudgeMent(BLUE);
			break;
			
		case 2:
			mJudgeMent[mcurrent_scene_no] = new RunDistJudgeMent(BOTH, 160);	//straPush
			break;
		case 14:
		case 20:
		case 32:
		case 41:
		case 47:
		case 53:
		case 59:
		case 65:
		case 71:
			mJudgeMent[mcurrent_scene_no] = new RunDistJudgeMent(BOTH, 180);	//straPush
			break;
			
		case 6:
		case 18:
		case 24:
		case 36:
		case 45:
		case 51:
		case 57:
		case 63:
		case 69:
			mJudgeMent[mcurrent_scene_no] = new RunDistJudgeMent(BOTH, 70);	//stra50(Harf)
			break;
		
		case 9:
		case 12:
		case 27:
		case 30:
		case 39:
			mJudgeMent[mcurrent_scene_no] = new RunDistJudgeMent(BOTH, 145);	//stra50
			break;
			
		case 8:
		case 11:
		case 26:
		case 29:
		case 38:
			mJudgeMent[mcurrent_scene_no] = new RotateAngleJudgeMent(LEFT, -2);	//agjust
			break;
			
		case 4:
		case 16:
		case 22:
		case 34:
		case 43:
		case 49:
		case 55:
		case 61:
		case 67:
			mJudgeMent[mcurrent_scene_no] = new RunDistJudgeMent(BOTH, -65);	//back
			break;
			
		case 3:
		case 15:
		case 21:
		case 33:
		case 42:
		case 48:
		case 54:
		case 60:
		case 66:
			mJudgeMent[mcurrent_scene_no] = new RunDistJudgeMent(BOTH, 0);	//stop
			break;
		
		case 7:
		case 10:
		case 13:
		case 19:
		case 25:
		case 28:
		case 31:
		case 37:
		case 40:
		case 46:
		case 52:
		case 58:
		case 64:
		case 70:
			mJudgeMent[mcurrent_scene_no] = new RunDistJudgeMent(LEFT, 210);	//LineTrace
			break;
			
		case 5:
		case 35:
		case 44:
		case 50:
		case 68:
			mJudgeMent[mcurrent_scene_no] = new RotateAngleJudgeMent(LEFT, -90);	//RotateL
			break;
		
		case 17:
		case 23:
		case 56:
		case 62:
			mJudgeMent[mcurrent_scene_no] = new RotateAngleJudgeMent(RIGHT, 90);	//RotateR
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
