#include "Block.h"
#include "..\Player\PlayerChild.h"

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


//==============================================
//内部プライベート関数
//==============================================
void Block::loadImage()
{
	this->mImage = LoadGraph("Data/Image/Block.png");
	assert(mImage == -1 && "Block画像読み込みエラー!");
}


}
}
}