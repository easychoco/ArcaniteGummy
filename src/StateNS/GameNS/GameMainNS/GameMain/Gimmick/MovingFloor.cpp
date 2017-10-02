#include "MovingFloor.h"

#include "..\Character.h"


//for Debug
#include "..\Collision.h"
#include "..\..\..\..\..\KeyInput.h"

namespace StateNS {
namespace GameNS {
namespace GameMainNS{


MovingFloor::MovingFloor(int _x, int _y, int _term_x, int _term_y, float _movingSpeed, int _moveType) :
DynamicGimmickChild(_x, _y, 1.0)
{
	this->width  = 64;
	this->height = 32;

	float differ_x = (float)(_term_x - _x);
	float differ_y = (float)(_term_y - _y);


	//往復にかかる時間を計算
	this->r = (int)hypotf(differ_x, differ_y)/2;
	this->interval = (int)(2 * hypotf(differ_x, differ_y) / _movingSpeed);

	//2頂点間の角度を計算
	float angle = atan2f(differ_y, differ_x);

	this->motion_dx = _movingSpeed * cosf(angle);
	this->motion_dy = _movingSpeed * sinf(angle);
	this->moveType = _moveType;
	initialize();
}

MovingFloor::~MovingFloor()
{
	DeleteGraph(mImage);
}

void MovingFloor::initialize()
{
	mTime = 0;
	loadImage();
}

void MovingFloor::update(const StageChild* _stage)
{
	mTime++;
	mTime %= interval;




	move();
	standardMove(_stage);

}

void MovingFloor::draw(const Vector2* _camera) const
{
	
	standardDraw(_camera, scale, mImage, mDirection);
//	DrawFormatString(0, 100, BLACK, "interval:%d", interval);
//	DrawFormatString(0, 128, BLACK, "mTime:%d", mTime);
}

void MovingFloor::apply(Character* _character)
{
	//_character->moveCharacter((float)dx / vectorRate, (float)dy / vectorRate);
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

void MovingFloor::move()
{
	float tmp_dy = 0.0f;
	float tmp_dx = 0.0f;

	//TODO 列挙型に書き換え
	switch (moveType) 
	{
	case 0://線形移動
		tmp_dx = ((mTime - interval / 2 < 0) ? motion_dx : -motion_dx);
		tmp_dy = ((mTime - interval / 2 < 0) ? motion_dy : -motion_dy);break;
	case 1://上に凸な放物線移動
		tmp_dx = ((mTime - interval / 2 < 0) ? motion_dx : -motion_dx);
		tmp_dy = (mTime - interval / 2 < 0) ? (mTime - interval / 4) / 10.0f : (-interval + mTime + interval / 4) / 10.0f; 
		break;
	case 2://下に凸な放物線移動
		tmp_dx = ((mTime - interval / 2 < 0) ? motion_dx : -motion_dx);
		tmp_dy = (mTime - interval / 2 < 0) ? (-mTime + interval / 4) / 10.0f : (interval - mTime - interval / 4) / 10.0f;
		break;
	case 3://時計回り円
		tmp_dx = r*sinf(2 * Pi*mTime / interval) / 10.0f;
		tmp_dy = r*cosf(2 * Pi*mTime / interval) / 10.0f;
		break;
	case 4://反時計回り円
		tmp_dx = r*sinf(-2 * Pi*mTime / interval) / 10.0f;
		tmp_dy = r*cosf(-2 * Pi*mTime / interval) / 10.0f;
		break;
	}
	dx = (int)(tmp_dx * vectorRate);
	dy = (int)(tmp_dy * vectorRate);

}


}
}
}