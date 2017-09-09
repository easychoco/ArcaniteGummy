#include "Dossunn.h"
#include "..\Character.h"

namespace StateNS {
namespace GameNS {
namespace GameMainNS {


Dossunn::Dossunn(int _x, int _y, double _scale) :
DynamicGimmickChild(_x, _y, _scale)
{
	this->width = (int)(32 * _scale);
	this->height = (int)(32 * _scale);

	initialize();
}

Dossunn::~Dossunn()
{

}

void Dossunn::initialize()
{
	loadImage();

	mTime = 0;
	isActive = true;
	isMove = false;
}

void Dossunn::update(const Stage* _stage)
{
	move();
	standardMove(_stage);
}

void Dossunn::draw(const Vector2* _camera) const
{
	standardDraw(_camera, p, mImage, mDirection);

	//for Debug
	DrawFormatString(0, 70, BLACK, "D: %d, %d", p->x(), p->y());
}

void Dossunn::apply(Character* _character)
{
	this->isMove = true;
}

void Dossunn::hittedAction()
{
	/* do nothing */
}

void Dossunn::burnedAction()
{
	/* do nothing */
}

bool Dossunn::isOverlap(const Vector2* _player) const
{
	return standardOverLap(_player);
}

bool Dossunn::onActiveArea(const Vector2* _player) const
{
	return
		abs(this->p->x() - _player->x()) <= CHIP_WIDTH * 5 &&
		abs(this->p->y() - _player->y()) <= CHIP_WIDTH * 5;
}

//==============================================
//内部プライベート関数
//==============================================
void Dossunn::loadImage()
{
	this->mImage = LoadGraph("Data/Image/dossunn.png");
	assert(mImage != -1 && "Dossunn画像読み込みエラー!");
}

void Dossunn::move()
{
	if (isMove && mTime <= 150)
	{
		++mTime;
		if (mTime < 30)dy = CHIP_HEIGHT * 100;
		else dy = - CHIP_HEIGHT * 25;
	}
	else
	{
		dy = 0;
		mTime = 0;
		isMove = false;
	}

}




}
}
}