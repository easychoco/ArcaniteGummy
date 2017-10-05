#include "Dossunn.h"
#include "..\Character.h"

namespace StateNS {
namespace GameNS {
namespace GameMainNS {

bool Dossunn::imgLoad = false;
int Dossunn::image;

Dossunn::Dossunn(int _x, int _y, double _scale) :
DynamicGimmickChild(_x, _y, _scale)
{
	this->width = (int)(32 * _scale);
	this->height = (int)(32 * _scale);

	initialize();
}

Dossunn::~Dossunn()
{
	//DeleteGraphはしない
}

void Dossunn::initialize()
{
	loadImage();
	mImage = image;

	mTime = 0;
	isActive = true;
	isMove = false;
}

void Dossunn::update(const StageChild* _stage)
{
	move();
	standardMove(_stage);
}

void Dossunn::draw(const Vector2* _camera) const
{
	standardDraw(_camera, scale, mImage, mDirection);

}

void Dossunn::apply(Character* _character)
{
	this->isMove = true;

	//動作実装未確認
	if (abs(_character->getVector2()->raw_x - this->p->raw_x) < this->width)
	{
		if (this->p->raw_y < _character->getVector2()->raw_y && 
			(_character->getFloorCoordinate() - this->p->raw_y) < PLAYER_CHIP_HEIGHT_RATE() + this->height / 2)
		{
			//つぶされたらダメージ
			_character->hpController.damage(300);
		}
	}
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
	if (!imgLoad)
	{
		this->image = LoadGraph("Data/Image/dossunn.png");
		assert(image != -1 && "Dossunn画像読み込みエラー!");
	}
	imgLoad = true;
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