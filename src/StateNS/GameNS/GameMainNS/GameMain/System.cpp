#include "System.h"

#include "..\..\..\..\Data.h"
#include "..\..\..\..\KeyInput.h"

namespace StateNS {
namespace GameNS {
namespace GameMainNS{


System::System(int _stage){
	nowStage = _stage;
	initialize();
}

System::~System()
{

}

void System::initialize()
{
	stage_x = stage_y = 2;
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
	//for Debug
	DrawFormatString(0, 70, MyData::BLACK, "%d", nowStage);
}



//==============================================
//内部プライベート関数
//==============================================

//そんなものはない



}
}
}