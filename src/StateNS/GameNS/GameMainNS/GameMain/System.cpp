#include "System.h"

//#include "..\..\..\..\Data.h"
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
	DeleteGraph(img_DarkRing);
}

void System::initialize()
{
	this->f_type = FilterType::TYPE_NONE;

	img_DarkRing = LoadGraph("Data/Image/darkring.png");
	assert(img_DarkRing != -1 && "DarkRing読み込みエラー");
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

	//for Debug
	if (Input_S())filter = TYPE_NONE;
	if (Input_D())filter = TYPE_DARK;
}

void System::draw(const Vector2* _player) const
{
	if(filter == TYPE_DARK)drawDarkFilter(_player, 100);
}



//==============================================
//内部プライベートメンバ
//==============================================
void System::drawDarkFilter(const Vector2* _p, int _radius) const
{
	/*
	PlayerChild::updateCamera
	//カメラ位置を更新
	int tmp_x = p->raw_x / MyData::vectorRate;
	int tmp_y = p->raw_y / MyData::vectorRate;
	if (actionState == ACT_SIT)tmp_y -= PLAYER_CHIP_HEIGHT / 4;

	if (tmp_x % MyData::MAP_WIDTH  <                     MyData::CX)tmp_x = MyData::MAP_WIDTH * (tmp_x / MyData::MAP_WIDTH) + MyData::CX;
	if (tmp_x % MyData::MAP_WIDTH  > MyData::MAP_WIDTH - MyData::CX)tmp_x = MyData::MAP_WIDTH * (tmp_x / MyData::MAP_WIDTH) + MyData::MAP_WIDTH - MyData::CX;

	if (tmp_y % MyData::MAP_HEIGHT <                      MyData::CY)tmp_y = MyData::MAP_HEIGHT * (tmp_y / MyData::MAP_HEIGHT) + MyData::CY;
	if (tmp_y % MyData::MAP_HEIGHT > MyData::MAP_HEIGHT - MyData::CY)tmp_y = MyData::MAP_HEIGHT * (tmp_y / MyData::MAP_HEIGHT) + MyData::MAP_HEIGHT - MyData::CY;
	*/

	int draw_x = MyData::CX;
	int draw_y = MyData::CY;

	if (_p->x() < MyData::CX)draw_x = _p->x();
	if (_p->y() < MyData::CY)draw_y = _p->y();

	if (_p->x() > MAP_WIDTH  - MyData::CX)draw_x = _p->x() % (MAP_WIDTH  - MyData::CX) + MyData::CX;
	if (_p->y() > MAP_HEIGHT - MyData::CY)draw_y = _p->y() % (MAP_HEIGHT - MyData::CY) + MyData::CY;

	//draw_x, draw_y が画面上のプレイヤーの座標

	DrawBox(0, 0, draw_x - _radius, 480, BLACK, true);
	DrawBox(0, 0, 640, draw_y - _radius, BLACK, true);
	DrawBox(0, draw_y + _radius, 640, 480, BLACK, true);
	DrawBox(draw_x + _radius, 0, 640, 480, BLACK, true);

	DrawRotaGraph(draw_x, draw_y, 1.0, 0.0, img_DarkRing, true);
}

}
}
}