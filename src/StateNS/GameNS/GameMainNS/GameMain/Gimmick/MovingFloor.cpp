#include "MovingFloor.h"

#include "..\Character.h"


//for Debug
#include "..\Collision.h"
#include "..\..\..\..\..\KeyInput.h"

namespace StateNS {
namespace GameNS {
namespace GameMainNS{


MovingFloor::MovingFloor(int _x, int _y, int _term_x, int _term_y, float _movingSpeed) : 
DynamicGimmickChild(_x, _y, 1.0)
{
	this->width  = 64;
	this->height = 32;

	float differ_x = (float)(_term_x - _x);
	float differ_y = (float)(_term_y - _y);


	//往復にかかる時間を計算
	this->interval = (int)(2 * hypotf(differ_x, differ_y) / _movingSpeed);

	//2頂点間の角度を計算
	float angle = atan2f(differ_y, differ_x);

	this->motion_dx = _movingSpeed * cosf(angle);
	this->motion_dy = _movingSpeed * sinf(angle);


	initialize();
}

MovingFloor::~MovingFloor()
{

}

void MovingFloor::initialize()
{
	mTime = 0;
	loadImage();
}

void MovingFloor::update(const Stage* _stage)
{
	mTime++;
	mTime %= interval;

	float tmp_dx = ((mTime - interval / 2 < 0) ? motion_dx : -motion_dx);
	float tmp_dy = ((mTime - interval / 2 < 0) ? motion_dy : -motion_dy);

	dx = (int)(tmp_dx * vectorRate);
	dy = (int)(tmp_dy * vectorRate);

	//for Debug
	if (Input_S())
	{
		int gpmi = 0;
	}

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
	_character->moveCharacter((float)dx / vectorRate, (float)dy / vectorRate);
}

void MovingFloor::hittedAction()
{
	/*do nothing*/
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
	return
		abs(this->p->x() - _player->x()) <= MyData::CHIP_WIDTH &&
		(this->p->y() - _player->y()) / MyData::CHIP_HEIGHT == 1;
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