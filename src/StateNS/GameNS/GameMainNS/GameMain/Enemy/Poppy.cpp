#include "Poppy.h"




namespace StateNS {
namespace GameNS {
namespace GameMainNS{

Poppy::Poppy(int _x, int _y) : EnemyChild(100, _x, _y, 32, 32,1,1)
{
	if(!imgLoad)loadImage();
	assert(mImage != -1 && "Poppy画像読み込みエラー!");

	initialize();
};


Poppy::~Poppy()
{
	this->mDirection = player->raw_x > this->p->raw_x;
}

void Poppy::initialize()
{

}

void Poppy::update(const StageChild* _stage, const Vector2* _camera)
{
	//横に直進するだけ
	mTime++;

	standardAction(_stage);
}

void Poppy::move(const StageChild* _stage, int& _dx, int& _dy)
{
	int x = this->mDirection ? 1 : -1;
	_dx = getHorizontalDiffer(_stage, x * vectorRate, _dy < 0);
}


//==============================================
//内部プライベート関数
//==============================================
void Poppy::hittedAction()
{

}


}
}
}