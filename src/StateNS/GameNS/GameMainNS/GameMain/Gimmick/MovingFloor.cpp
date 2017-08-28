#include "MovingFloor.h"
#include "..\Player\PlayerChild.h"

namespace StateNS {
namespace GameNS {
namespace GameMainNS{


MovingFloor::MovingFloor(){
	initialize();
}

MovingFloor::~MovingFloor()
{

}

void MovingFloor::initialize()
{
	isActive = false;
}

void MovingFloor::update(PlayerChild* _player)
{
	
}

void MovingFloor::draw(const Vector2* _camera) const
{
	
	/*
	//画面内にいなければreturn
	if (abs(pos.pos_x() - _camera->pos_x()) > 350000 || abs(pos.pos_y() - _camera->pos_y()) > 270000)return;


	int draw_x = 320 + (pos.pos_x() - _camera->pos_x()) / MyData::vectorRate;
	int draw_y = 240 + (pos.pos_y() - _camera->pos_y()) / MyData::vectorRate;

	//描画
	DrawRotaGraph(draw_x, draw_y, 1.0, 0.0, img, true);
	//*/
}

bool MovingFloor::isHit(const Vector2*) const
{
	return false;
}

Stage::ChipType MovingFloor::getChipType() const
{
	return Stage::ChipType::TYPE_BACK;
}



//==============================================
//内部プライベート関数
//==============================================

//そんなものはない



}
}
}