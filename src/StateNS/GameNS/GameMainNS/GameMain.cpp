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
	SAFE_DELETE(mStage);
	SAFE_DELETE(mPlayer);
	SAFE_DELETE(mSystem);
	SAFE_DELETE(mEController);
}

void GameMain::initialize()
{
	mStage = new Stage(11);
	mPlayer = new Mokou(96, 96);
	mSystem = new System();
	mEController = new EnemyController();
}

Child* GameMain::update(GameParent* _parent)
{
	Child* next = this;

	mStage->update(mPlayer);
	
	PlayerChild* nextPlayer = mPlayer->update(mStage);

	mEController->update();

	if (nextPlayer != mPlayer)
	{
		SAFE_DELETE(mPlayer);
		mPlayer = nextPlayer;
	}


	mSystem->update();
	
	return next;
}

void GameMain::draw() const
{
	DrawFormatString(0, 20, MyData::WHITE, "GameMain");
	mStage->draw(mPlayer->getCamera());
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