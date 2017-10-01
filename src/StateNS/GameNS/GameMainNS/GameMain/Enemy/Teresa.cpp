#include "Teresa.h"




namespace StateNS {
namespace GameNS {
namespace GameMainNS{

Teresa::Teresa(int _x, int _y) : EnemyChild(100, _x, _y, 32, 32)
{
	if(!imgLoad)loadImage();
	assert(*mImage != -1 && "Teresa画像読み込みエラー!");

	initialize();
};


Teresa::~Teresa()
{

}

void Teresa::initialize()
{
	this->mDirection = false;
	this->mTime = 0;
}

void Teresa::update(const StageChild* _stage, const Vector2* _camera)
{
	actState = ENE_ACT_WALK;
	aTime++;
	mTime++;
	this->mDirection = player->raw_x > this->p->raw_x;

	standardAction(_stage);
}

void Teresa::move(const StageChild* _stage, int& _dx, int& _dy)
{
	int dx_tmp = mDirection ? vectorRate / 2 : -vectorRate / 2;

	int dy_tmp = (player->raw_y > this->p->raw_y) ? vectorRate / 2 : -vectorRate / 2;
	dy_tmp += (int)(vectorRate * sin((Pi / 90) * mTime));

	_dy = dy_tmp;
	_dx = dx_tmp;
}



//==============================================
//内部プライベート関数
//==============================================
void Teresa::hittedAction()
{

}


}
}
}