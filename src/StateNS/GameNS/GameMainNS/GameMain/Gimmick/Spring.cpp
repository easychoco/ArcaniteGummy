#include "Spring.h"
#include "..\Character.h"

namespace StateNS {
namespace GameNS {
namespace GameMainNS{


Spring::Spring(Vector2 _pos) :
GimmickChild(_pos)
{
	initialize();
	
}

Spring::~Spring()
{

}

void Spring::initialize()
{
	loadImage();

	isActive = true;
	dy = 0.0f;
	mTime = 0;
	aTime = 0;
}

void Spring::update()
{
	mTime++;
}

void Spring::draw(const Vector2* _camera) const
{
	//画面内にいなければreturn
	if (abs(pos.pos_x() - _camera->pos_x()) > 350000 || abs(pos.pos_y() - _camera->pos_y()) > 270000)return;


	int draw_x = 320 + (pos.pos_x() - _camera->pos_x()) / MyData::vectorRate;
	int draw_y = 240 + (pos.pos_y() - _camera->pos_y()) / MyData::vectorRate;

	//描画
	DrawRotaGraph(draw_x, draw_y, 1.0, 0.0, mImage, true);
}

void Spring::apply(Character* _character)
{
	//要調整
	//このままだとどちらかというとトランポリンっぽい。
	_character->setJumpPower(30);
}

bool Spring::isOverlap(int _sub_x, int _sub_y) const
{
	return
		this->pos.x() / MyData::CHIP_WIDTH  == _sub_x &&
		this->pos.y() / MyData::CHIP_HEIGHT == _sub_y;
}

bool Spring::onActiveArea(const Vector2* _player) const
{
	/*
	return
		abs(this->pos.x() - _player->x()) <= MyData::CHIP_WIDTH / 2 &&
		(this->pos.y() - _player->y()) / MyData::CHIP_HEIGHT == 1;
		*/

	return
		abs(this->pos.x() - _player->x()) <= MyData::CHIP_WIDTH / 2  &&
		0<=(this->pos.y() - _player->y()) / MyData::CHIP_HEIGHT &&
		(this->pos.y() - _player->y()) / MyData::CHIP_HEIGHT <=1 ;

}

Stage::ChipType Spring::getChipType() const
{
	return Stage::ChipType::TYPE_RIGID;
}

//==============================================
//内部プライベート関数
//==============================================
void Spring::loadImage()
{
	mImage = LoadGraph("Data/Image/Spring.png");
	assert(mImage != -1 && "バネ画像読み込みエラー！");
}


}
}
}