#include "Block.h"

#include "..\Character.h"


//for Debug
#include "..\Collision.h"

namespace StateNS {
namespace GameNS {
namespace GameMainNS{

Block::Block(int _x, int _y, double _scale) :
	Block(_x, _y, _scale, true){ }

Block::Block(int _x, int _y, double _scale, bool _isBreakable) :
DynamicGimmickChild(_x, _y, _scale),
isBreakable(_isBreakable)
{
	this->width  = (int)(32 * _scale);
	this->height = (int)(32 * _scale);
	
	initialize();
}

Block::~Block()
{

}

void Block::initialize()
{
	loadImage();
	dy = 0;
}

void Block::update(const StageChild* _stage)
{
	standardMove(_stage);
	//this->dy = getBottomDiffer(_stage, 4000);
	//this->p->raw_y += this->dy;
}

void Block::draw(const Vector2* _camera) const
{
	standardDraw(_camera, p, scale, mImage, mDirection);

	//for Debug
	//DrawFormatString(0, 50, BLACK, "%d %d", width, height);
	//DrawFormatString(300, 100, BLACK, "%lf", scale);
	DrawFormatString(300, 120, BLACK, "b: %d %d", collision->p->raw_x, collision->p->raw_y);


	int draw_x = 320 + p->x() - _camera->x();
	int draw_y = 240 + p->y() - _camera->y();

	DrawCircle(draw_x, draw_y, 5, GREEN);
	//DrawBox(draw_x, draw_y, draw_x + width, draw_y + height, BLACK, false);
}

void Block::apply(Character* _character)
{
	_character->moveCharacter(0.0f, (float)dy);
}

void Block::hittedAction()
{
	if(isBreakable)this->isActive = false;
}

void Block::burnedAction()
{
	//TODO -> アニメーションをつける

	//燃やされると消える
	this->isActive = false;
}

bool Block::isOverlap(const Vector2* _player) const
{
	return standardOverLap(_player);

	/*
	int tmp_w = this->width  * vectorRate / 2;
	int tmp_h = this->height * vectorRate / 2;

	return
		this->p->raw_x - tmp_w < _player->raw_x &&
		this->p->raw_x + tmp_w > _player->raw_x &&
		this->p->raw_y - tmp_h < _player->raw_y &&
		this->p->raw_y + tmp_h > _player->raw_y;
	*/

	/* Collisionの当たり判定
	return
		this->p->raw_x			      < other->p->raw_x + other->width  &&
		this->p->raw_x + this->width  > other->p->raw_x					&&
		this->p->raw_y			      < other->p->raw_y + other->height &&
		this->p->raw_y + this->height > other->p->raw_y;
	*/
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