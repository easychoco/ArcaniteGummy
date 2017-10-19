#include "BeltConveyor.h"
#include "..\Character.h"

namespace StateNS {
namespace GameNS {
namespace GameMainNS{

bool BeltConveyor::imgLoad = false;
int BeltConveyor::images[3];



BeltConveyor::BeltConveyor(float _dx, Vector2 _pos) : 
GimmickChild(_pos)
{
	loadImage();
	setMovingSpeed(_dx);

	initialize();

}

BeltConveyor::~BeltConveyor()
{
	//DeleteGraphはしない
}

void BeltConveyor::initialize()
{

	isActive = true;
	mTime = 0;

	this->direction = this->dx > 0;
}

void BeltConveyor::update()
{
	mTime++;
	mImage = images[mTime / 10 % 3];
}

void BeltConveyor::draw(const Vector2* _camera) const
{
	//画面内にいなければreturn
	if (abs(pos.raw_x - _camera->raw_x) > 350000 || abs(pos.raw_y - _camera->raw_y) > 270000)return;


	int draw_x = 320 + (pos.raw_x - _camera->raw_x) / MyData::vectorRate;
	int draw_y = 240 + (pos.raw_y - _camera->raw_y) / MyData::vectorRate;

	//描画
	if (direction)
	{
		//右向きなら
		SetDrawBlendMode(DX_BLENDMODE_ADD, 255);
		DrawRotaGraph(draw_x, draw_y, 1.0, 0.0, mImage, true, false);
	}
	else
	{
		//左向きなら
		SetDrawBlendMode(DX_BLENDMODE_SUB, 255);
		DrawRotaGraph(draw_x, draw_y, 1.0, 0.0, mImage, true, true);
	}
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
}

void BeltConveyor::apply(Character* _character)
{
	_character->moveCharacter(dx, 0);
}

/*
bool BeltConveyor::isOverlap(int _sub_x, int _sub_y) const
{
	return
		this->pos.x() / MyData::CHIP_WIDTH  == _sub_x &&
		this->pos.y() / MyData::CHIP_HEIGHT == _sub_y;
}
*/

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
	if (!imgLoad)
	{
		int tmp = LoadDivGraph("Data/Image/beltconveyor.png", 3, 3, 1, 32, 32, images);
		assert(tmp != -1 && "ベルトコンベヤー画像読み込みエラー！");
	}
	imgLoad = true;
}


}
}
}