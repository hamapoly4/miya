﻿#include "Scene.h"
#include <stdio.h>

Scene::Scene(unsigned char scene_no)
	: mcurrent_scene_no(scene_no)
{
	// 各シーンに応じた走行オブジェクトを確保
	switch (mcurrent_scene_no)
	{
		case  0:
		case  3:
		case 17:
		case 20:
			mRun[mcurrent_scene_no] = new RotateRun(RIGHT);
			break;
		case  1:
		case  6:
			mRun[mcurrent_scene_no] = new StraRun;
			break;
		case 12:
			mRun[mcurrent_scene_no] = new StraRun(45);
			break;
		case 16:
			mRun[mcurrent_scene_no] = new StraRun(35);
			break;
		case 21:
		case 23:
		case 25:
		case 27:
		case 30:
			mRun[mcurrent_scene_no] = new StraRun(50);
			break;
		case 19:
		case 28:
			mRun[mcurrent_scene_no] = new StraRun(-50);
			break;
		case  2:
		case  5:
		case  7:
		case 10:
		case 13:
		case 15:
			mRun[mcurrent_scene_no] = new LineSearchRun();
			break;
		case  4:
		case 14:
			mRun[mcurrent_scene_no] = new LineTraceRun(RIGHT);
			break;
		case  8:
		case 11:
		case 29:
			mRun[mcurrent_scene_no] = new RotateRun(LEFT);
			break;
		case  9:
		case 18:
		case 22:
		case 24:
		case 26:
			mRun[mcurrent_scene_no] = new LineTraceRun(LEFT);
			break;
		default:
			break;
	}

	// 各シーンに応じた判定オブジェクトを確保
	switch (mcurrent_scene_no)
	{
		case  0:
			mJudgeMent[mcurrent_scene_no] = new RotateAngleJudgeMent(RIGHT, 9);
			break;
		case  1:
			mJudgeMent[mcurrent_scene_no] = new RunDistJudgeMent(BOTH, 515);
			break;
		case  2:
		case  7:
		case 13:
			mJudgeMent[mcurrent_scene_no] = new ColorJudgeMent(BLACK);
			break;
		case  3:
			mJudgeMent[mcurrent_scene_no] = new RotateAngleJudgeMent(RIGHT, 28);
			break;
		case  4:
			mJudgeMent[mcurrent_scene_no] = new RunDistJudgeMent(RIGHT, 780);	//810
			break;
		case  6:
			mJudgeMent[mcurrent_scene_no] = new RunDistJudgeMent(BOTH, 460);	//440
			break;
		case  8:
			mJudgeMent[mcurrent_scene_no] = new RotateAngleJudgeMent(LEFT, -28);
			break;
		case  9:
			mJudgeMent[mcurrent_scene_no] = new RunDistJudgeMent(LEFT, 1540);
			break;
		case  5:
		case 10:
		case 15:
			mJudgeMent[mcurrent_scene_no] = new ColorJudgeMent(BLUE);
			break;
		case 11:
			mJudgeMent[mcurrent_scene_no] = new RotateAngleJudgeMent(LEFT, -19);
			break;
		case 12:
			mJudgeMent[mcurrent_scene_no] = new RunDistJudgeMent(BOTH, 120);
			break;
		case 14:
			mJudgeMent[mcurrent_scene_no] = new RunDistJudgeMent(RIGHT, 650);
			break;
		case 16:
			mJudgeMent[mcurrent_scene_no] = new RunDistJudgeMent(BOTH, 120);
			break;
		case 17:
			mJudgeMent[mcurrent_scene_no] = new RotateAngleJudgeMent(RIGHT, 9);
			break;
		case 18:
			mJudgeMent[mcurrent_scene_no] = new RunDistJudgeMent(LEFT, 970);
			break;
		case 19:
		case 28:
			mJudgeMent[mcurrent_scene_no] = new RunDistJudgeMent(BOTH, -20);
			break;
		case 20:
			mJudgeMent[mcurrent_scene_no] = new RotateAngleJudgeMent(RIGHT, 70);
			break;
		case 29:
			mJudgeMent[mcurrent_scene_no] = new RotateAngleJudgeMent(LEFT, -70);
			break;
		case 21:
		case 30:
			mJudgeMent[mcurrent_scene_no] = new RunDistJudgeMent(BOTH, 40);
			break;
		case 22:
		case 24:
		case 26:
			mJudgeMent[mcurrent_scene_no] = new RunDistJudgeMent(LEFT, 300);
			break;
		case 23:
		case 25:
		case 27:
			mJudgeMent[mcurrent_scene_no] = new RunDistJudgeMent(BOTH, 120);
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
