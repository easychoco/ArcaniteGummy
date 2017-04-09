#include "GameMain.h"

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

}

void GameMain::initialize()
{

}

Child* GameMain::update(GameParent* _parent)
{
	Child* next = this;
	
	return next;
}

void GameMain::draw() const
{
	DrawFormatString(0, 20, MyData::WHITE, "GameMain");
}


//==============================================
//内部プライベート関数
//==============================================

//そんなものはない



}
}
}