#include "Usagi.h"




namespace StateNS {
namespace GameNS {
namespace GameMainNS{

Usagi::Usagi(int _x, int _y) : EnemyChild(100, _x, _y, 32, 32)
{
	if(!imgLoad)loadImage();
	assert(mImage != -1 && "Usagi画像読み込みエラー!");

	initialize();
};


Usagi::~Usagi()
{

}

void Usagi::initialize()
{

}

void Usagi::update(const Stage* _stage)
{
	mTime++;
	standardMove(_stage);
}

void Usagi::move(const Stage* _stage, int& _dx, int& _dy)
{
	_dx = getHorizontalDiffer(_stage, _dx);
	_dy = getBottomDiffer(_stage, _dy);
}


//==============================================
//内部プライベート関数
//==============================================

void Usagi::hittedAction()
{

}

}
}
}