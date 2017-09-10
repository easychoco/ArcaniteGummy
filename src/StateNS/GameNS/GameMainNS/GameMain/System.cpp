#include "System.h"

#include "..\..\..\..\Data.h"
#include "..\..\..\..\KeyInput.h"

namespace StateNS {
namespace GameNS {
namespace GameMainNS{

System::System(int _stage,int _stage_x,int _stage_y){
	nowStage = _stage;
	stage_x = _stage_x;
	stage_y = _stage_y;
	stage_num = _stage_x * _stage_y;

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
		//if (nowStage % stage_x < stage_x - 1)
		nowStage++;
		break;
	case GameMain::HowStageMove::MOVE_LEFT:
		//if (nowStage % stage_x > 0)
		nowStage--;
		break;
	case GameMain::HowStageMove::MOVE_UP:
		//if (nowStage / stage_y > 0)
		nowStage -= stage_y;
		break;
	case GameMain::HowStageMove::MOVE_DOWN:
		//if (nowStage + stage_y < stage_num)
		nowStage += stage_y;
		break;
	}
}

void System::draw() const
{
	//for Debug
	DrawFormatString(300, 30, BLACK, "stagenum: %d", nowStage);
	DrawFormatString(300, 50, BLACK, "stage_x:  %d", stage_x);
	DrawFormatString(300, 70, BLACK, "stage_y:  %d", stage_y);
}



//==============================================
//内部プライベート関数
//==============================================

//そんなものはない



}
}
}