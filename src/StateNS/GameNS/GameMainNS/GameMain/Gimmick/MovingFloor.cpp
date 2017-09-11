#include "MovingFloor.h"

#include "..\Character.h"


//for Debug
#include "..\Collision.h"

namespace StateNS {
namespace GameNS {
namespace GameMainNS{


MovingFloor::MovingFloor(int _x, int _y, int _term_x, int _term_y, float _movingSpeed) : 
DynamicGimmickChild(_x, _y, 1.0)
{
	this->width  = 64;
	this->height = 32;

	this->start_x = _x;
	this->start_y = _y;

	this->term_x = _term_x;
	this->term_x = _term_y;

	this->movingSpeed = _movingSpeed;

	initialize();
}

MovingFloor::~MovingFloor()
{

}

void MovingFloor::initialize()
{
	loadImage();
	motion_dx = (int)((term_x - start_x) / movingSpeed);
	motion_dy = (int)((term_y - start_y) / movingSpeed);
}

void MovingFloor::update(const Stage* _stage)
{

	dx = motion_dx;
	dy = motion_dy;

	standardMove(_stage);
}

void MovingFloor::draw(const Vector2* _camera) const
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

void MovingFloor::apply(Character* _character)
{
	_character->moveCharacter((float)dx, (float)dy);
}

void MovingFloor::hittedAction()
{

}

void MovingFloor::burnedAction()
{
	/*do nothing*/
}

bool MovingFloor::isOverlap(const Vector2* _player) const
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

bool MovingFloor::onActiveArea(const Vector2* _player) const
{
	//for Debug
	return false;
}

//==============================================
//内部プライベート関数
//==============================================
void MovingFloor::loadImage()
{
	this->mImage = LoadGraph("Data/Image/movingfloor.png");
	assert(mImage != -1 && "MovingFloor画像読み込みエラー!");
}


}
}
}