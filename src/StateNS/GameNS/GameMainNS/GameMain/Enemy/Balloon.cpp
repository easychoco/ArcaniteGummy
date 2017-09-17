#include "Balloon.h"




namespace StateNS {
namespace GameNS {
namespace GameMainNS{

Balloon::Balloon(int _x, int _y) : EnemyChild(100, _x, _y, 32, 32,1,1)
{
	if(!imgLoad)loadImage();
	assert(mImage != -1 && "Balloon画像読み込みエラー!");

	initialize();
};


Balloon::~Balloon()
{

}

void Balloon::initialize()
{
	this->mDirection = false;
}

void Balloon::update(const Stage* _stage)
{
	mTime++;
	mTime %= 180;

	this->mDirection = player->raw_x > this->p->raw_x;

	standardAction(_stage);
}

void Balloon::move(const Stage* _stage, int& _dx, int& _dy)
{
	_dy = (int)(2 * vectorRate * sinf(pi(mTime / 90.0f)));
}


//==============================================
//内部プライベート関数
//==============================================
void Balloon::hittedAction()
{

}


}
}
}