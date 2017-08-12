#include "GameMain.h"
#include "GameMain\Stage.h"
#include "GameMain\System.h"
#include "GameMain\Player\Mokou.h"
#include "GameMain\Player\Sakuya.h"

#include "GameMain\Enemy\EnemyController.h"

#include "..\..\..\Data.h"
#include "..\..\..\KeyInput.h"

namespace StateNS {
namespace GameNS {
namespace GameMainNS{


GameMain::GameMain(){
	initialize();
}

GameMain::~GameMain()
{
	for (auto& stage : mStages)
	{
		SAFE_DELETE(stage);
	}
	mStages.clear();
	mStages.shrink_to_fit();

	SAFE_DELETE(mPlayer);
	SAFE_DELETE(mSystem);
	SAFE_DELETE(mEController);
}

void GameMain::initialize()
{
	for (int i = 0; i < 4; i++)
	{
		mStages.push_back(new Stage(0, i));
	}

	//ステージの全体的な縦と横の数を設定
	for (auto& stage : mStages)
	{
		stage->setStageSize(2, 2);
	}
	nowStageNum = 0;

	mPlayer = new Sakuya(96, 96);
	mSystem = new System(nowStageNum);
	mEController = new EnemyController();

	changed = false;
}

Child* GameMain::update(GameParent* _parent)
{
	Child* next = this;

	//今のstageをget
	nowStageNum = mSystem->getNowStage();
	Stage* stage = mStages[nowStageNum];

	stage->update(mPlayer);
	mEController->update(stage);
	PlayerChild* nextPlayer = mPlayer->update(stage);

	changed = false;
	if (nextPlayer != mPlayer)
	{
		SAFE_DELETE(mPlayer);
		mPlayer = nextPlayer;
		changed = true;
	}

	if(changed)mSystem->update(HowStageMove::MOVE_NONE);
	else mSystem->update(mPlayer->getStageMove());
	
	return next;
}

void GameMain::draw() const
{
	if (changed)return;

	//DrawFormatString(0, 20, MyData::WHITE, "GameMain");
	mStages[nowStageNum]->draw(mPlayer->getCamera());
	mEController->draw(mPlayer->getCamera());
	mPlayer->draw();
	mSystem->draw();
}


//==============================================
//内部プライベート関数
//==============================================

//そんなものはない



}
}
}