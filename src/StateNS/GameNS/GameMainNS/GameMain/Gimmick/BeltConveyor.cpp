#include "BeltConveyor.h"
#include "..\Character.h"

namespace StateNS {
namespace GameNS {
namespace GameMainNS{


BeltConveyor::BeltConveyor(int _dx, Vector2 _pos)
{
	initialize();
	
	pos = _pos;
	setMovingParam(_dx);
	mImage = LoadGraph("Data/Image/beltconveyor.png");
	assert(mImage != -1 && "ベルトコンベヤー画像読み込みエラー！");
}

BeltConveyor::~BeltConveyor()
{

}

void BeltConveyor::initialize()
{
	isActive = true;
	dx = 0;
	mTime = 0;
}

void BeltConveyor::update()
{
	mTime++;
}

void BeltConveyor::draw(const Vector2* _camera) const
{
	//画面内にいなければreturn
	if (abs(pos.pos_x - _camera->pos_x) > 350000 || abs(pos.pos_y - _camera->pos_y) > 270000)return;


	int draw_x = 320 + (pos.pos_x - _camera->pos_x) / MyData::vectorRate;
	int draw_y = 240 + (pos.pos_y - _camera->pos_y) / MyData::vectorRate;

	//描画
	DrawRotaGraph(draw_x, draw_y, 1.0, 0.0, mImage, true);
}

void BeltConveyor::apply(Character* _character)
{
	_character->moveCharacter(dx, 0);
}

bool BeltConveyor::isOverlap(const Vector2*) const
{
	return false;
}

bool BeltConveyor::onActiveArea(const Vector2*) const
{
	return false;
}

Stage::ChipType BeltConveyor::getChipType() const
{
	return Stage::ChipType::TYPE_RIGID;
}

//==============================================
//内部プライベート関数
//==============================================

//そんなものはない



}
}
}