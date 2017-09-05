#include "Block.h"


//for Debug
#include "..\Collision.h"

namespace StateNS {
namespace GameNS {
namespace GameMainNS{


Block::Block(int _x, int _y, int _w, int _h) : 
DynamicGimmickChild(_x, _y, _w, _h)
{
	this->width = _w;
	this->height = _h;
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
	standardDraw(_camera, p, scale_x, scale_y, mImage, mDirection);

	//for Debug
	DrawFormatString(300, 100, BLACK, "%lf %lf", scale_x, scale_y);
	DrawFormatString(300, 120, BLACK, "%d %d", collision->width, collision->height);
}

void Block::apply(Character* _character)
{

}

void Block::hittedAction()
{

}

void Block::burnedAction()
{
	//TODO -> アニメーションをつける

	//燃やされると消える
	this->isActive = false;
}

bool Block::isOverlap(int _sub_x, int _sub_y) const
{
	//for Debug
	//このままだと、32[pixcel]区切りでしか箱を置けない
	//32区切りでないところに置いても、当たり判定が対応しない
	int  left_x = (this->p->x() - this->width + 32) / MyData::CHIP_WIDTH;
	int right_x = (this->p->x()/* + this->width - 16*/) / MyData::CHIP_WIDTH;

	int   up_y =  this->p->y() / MyData::CHIP_HEIGHT;
	int down_y = (this->p->y() + this->height - 16) / MyData::CHIP_HEIGHT;

	return
		left_x <= _sub_x && _sub_x <= right_x &&
		  up_y <= _sub_y && _sub_y <=  down_y;
}

bool Block::onActiveArea(const Vector2* _player) const
{
	//for Debug
	return false;
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