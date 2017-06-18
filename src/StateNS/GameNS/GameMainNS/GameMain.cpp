#include "GameMain.h"
#include "GameMain\Stage.h"
#include "GameMain\System.h"
#include "GameMain\Player\Mokou.h"

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
}

void GameMain::initialize()
{
	mStage = new Stage(0);
	mPlayer = new Mokou(40, 40);
	mSystem = new System();
}

Child* GameMain::update(GameParent* _parent)
{
	Child* next = this;

	mStage->update();

	
	PlayerChild* nextPlayer = mPlayer->update(mStage);

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
	mStage->draw(mPlayer->getVector2());
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