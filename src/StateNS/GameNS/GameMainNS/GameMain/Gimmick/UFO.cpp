#include "UFO.h"
#include "..\Character.h"
#include "..\..\..\..\..\KeyInput.h"


const int d_x[4] = { 0,1,0,-1 };
const int d_y[4] = { -1,0,1,0 };



namespace StateNS {
namespace GameNS {
namespace GameMainNS {


UFO::UFO(int _x, int _y, double _scale) :
DynamicGimmickChild(_x, _y, _scale)
{
	this->width = (int)(32 * 3);
	this->height = (int)(32 * _scale);

	initialize();
}

UFO::~UFO()
{

}

void UFO::initialize()
{
	loadImage();
	direction = -1;
	mTime = 0;
	isActive = true;
	isMove = false;



}

void UFO::update(const Stage* _stage)
{
	mTime++;
	move();
	standardMove(_stage);

	if (mTime > 12000 || (direction != -1 && mTime > 3000))this->isActive = false;

}

void UFO::draw(const Vector2* _camera) const
{
	standardDraw(_camera, p, mImage, mDirection);

	//for Debug
	DrawFormatString(0, 70, BLACK, "UFO: %d, %d", p->x(), p->y());
}

void UFO::apply(Character* _character)
{
	if (direction == -1) 
	{
		if (Input_UP())direction = 0;
		else if (Input_RIGHT())direction = 1;
		else if (Input_DOWN())direction = 2;
		else if (Input_LEFT())direction = 3;

	}


//	else _character->moveCharacter(3.2f, 0.0f);
	this->isMove = true;
}

void UFO::hittedAction()
{
	/* do nothing */
}

void UFO::burnedAction()
{
	/* do nothing */
}

bool UFO::isOverlap(const Vector2* _player) const
{
	return standardOverLap(_player);
}

bool UFO::onActiveArea(const Vector2* _player) const
{
	return rideOnGimmick(_player);

}

//==============================================
//内部プライベート関数
//==============================================
void UFO::loadImage()
{
	this->mImage = LoadGraph("Data/Image/UFO.png");
	assert(mImage != -1 && "UFO画像読み込みエラー!");
}

void UFO::move()
{


	if (direction != -1) {
		dx = d_x[direction]*3200;
		dy = d_y[direction]*3200;
	}
}




}
}
}