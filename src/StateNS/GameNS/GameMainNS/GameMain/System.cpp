#include "System.h"

#include "..\..\..\..\Data.h"
#include "..\..\..\..\KeyInput.h"

namespace StateNS {
namespace GameNS {
namespace GameMainNS{


System::System(int _stage, int _stage_x, int _stage_y){
	nowStage = _stage;
	stage_x = 2;
	stage_y = 1;

	initialize();
}

System::~System()
{

}

void System::initialize()
{

}

void System::update(GameMain::HowStageMove _nextStage)
{
	switch (_nextStage)
	{
	case GameMain::HowStageMove::MOVE_RIGHT:
		if (nowStage % stage_x < stage_x - 1)nowStage++;
		break;
	case GameMain::HowStageMove::MOVE_LEFT:
		if (nowStage % stage_x > 0)nowStage--;
		break;
	case GameMain::HowStageMove::MOVE_UP:
		if (nowStage / stage_y > 0)nowStage -= stage_y;
		break;
	case GameMain::HowStageMove::MOVE_DOWN:
		if (nowStage / stage_y < stage_y - 1)nowStage += stage_y;
		break;
	}
}

void System::draw() const
{

}



//==============================================
//内部プライベート関数
//==============================================

//そんなものはない



}
}
}