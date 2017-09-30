#include "BeltConveyor.h"
#include "..\Character.h"

namespace StateNS {
namespace GameNS {
namespace GameMainNS{


BeltConveyor::BeltConveyor(float _dx, Vector2 _pos) : 
GimmickChild(_pos)
{
	initialize();
	
	setMovingSpeed(_dx);
}

BeltConveyor::~BeltConveyor()
{

}

void BeltConveyor::initialize()
{
	loadImage();

	isActive = true;
	dx = 0.0f;
	mTime = 0;
}

void BeltConveyor::update()
{
	mTime++;
}

void BeltConveyor::draw(const Vector2* _camera) const
{
	//画面内にいなければreturn
	if (abs(pos.raw_x - _camera->raw_x) > 350000 || abs(pos.raw_y - _camera->raw_y) > 270000)return;


	int draw_x = 320 + (pos.raw_x - _camera->raw_x) / MyData::vectorRate;
	int draw_y = 240 + (pos.raw_y - _camera->raw_y) / MyData::vectorRate;

	//描画
	DrawRotaGraph(draw_x, draw_y, 1.0, 0.0, mImage, true);
}

void BeltConveyor::apply(Character* _character)
{
	_character->moveCharacter(dx, 0);
}

bool BeltConveyor::isOverlap(int _sub_x, int _sub_y) const
{
	return
		this->pos.x() / MyData::CHIP_WIDTH  == _sub_x &&
		this->pos.y() / MyData::CHIP_HEIGHT == _sub_y;
}

bool BeltConveyor::onActiveArea(const Vector2* _player) const
{
	return
		abs(this->pos.x() - _player->x()) <= MyData::CHIP_WIDTH / 2 &&
		(this->pos.y() - _player->y()) / MyData::CHIP_HEIGHT == 1;
}

StageChild::ChipType BeltConveyor::getChipType() const
{
	return StageChild::ChipType::TYPE_RIGID;
}

//==============================================
//内部プライベート関数
//==============================================
void BeltConveyor::loadImage()
{
	mImage = LoadGraph("Data/Image/beltconveyor.png");
	assert(mImage != -1 && "ベルトコンベヤー画像読み込みエラー！");
}


}
}
}