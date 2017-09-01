#include "Block.h"

namespace StateNS {
namespace GameNS {
namespace GameMainNS{


Block::Block(int _x, int _y, int _w, int _h) : 
DynamicGimmickChild(_x, _y, _w, _h)
{
	initialize();
}

Block::~Block()
{

}

void Block::initialize()
{
	loadImage();
}

void Block::update(PlayerChild* _player)
{

}

void Block::draw(const Vector2* _camera) const
{
	standardDraw(_camera, p, mImage, mDirection);
}

void Block::apply(Character* _character)
{

}

void Block::hittedAction()
{

}

bool Block::isOverlap(int _sub_x, int _sub_y) const
{
	//for Debug
	return
		this->p->x() / MyData::CHIP_WIDTH == _sub_x &&
		this->p->y() / MyData::CHIP_HEIGHT == _sub_y;
}

bool Block::onActiveArea(const Vector2* _player) const
{
	//for Debug
	return
		abs(this->p->x() - _player->x()) <= MyData::CHIP_WIDTH / 2 &&
		   (this->p->y() - _player->y()) / MyData::CHIP_HEIGHT == 1;
}

//==============================================
//内部プライベート関数
//==============================================
void Block::loadImage()
{
	this->mImage = LoadGraph("Data/Image/block.png");
	assert(mImage != -1 && "Block画像読み込みエラー!");
}


}
}
}