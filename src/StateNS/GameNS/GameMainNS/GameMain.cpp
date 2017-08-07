#include "GameMain.h"
#include "GameMain\Stage.h"
#include "GameMain\System.h"
#include "GameMain\Player\Mokou.h"

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
	nowStageNum = 0;

	mPlayer = new Mokou(96, 96);
	mSystem = new System(nowStageNum);
	mEController = new EnemyController();
}

Child* GameMain::update(GameParent* _parent)
{
	Child* next = this;

	nowStageNum = mSystem->getNowStage();

	mStages[nowStageNum]->update(mPlayer);
	mEController->update();

	
	PlayerChild* nextPlayer = mPlayer->update(mStages[nowStageNum]);

	if (nextPlayer != mPlayer)
	{
		SAFE_DELETE(mPlayer);
		mPlayer = nextPlayer;
	}


	mSystem->update(mPlayer->getStageMove());
	
	return next;
}

void GameMain::draw() const
{
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