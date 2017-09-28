#include "Teresa.h"




namespace StateNS {
namespace GameNS {
namespace GameMainNS{

Teresa::Teresa(int _x, int _y) : EnemyChild(100, _x, _y, 32, 32,1,1)
{
	if(!imgLoad)loadImage();
	assert(mImage != -1 && "Teresa画像読み込みエラー!");

	initialize();
};


Teresa::~Teresa()
{

}

void Teresa::initialize()
{
	this->mDirection = false;
}

void Teresa::update(const StageChild* _stage, const Vector2* _camera)
{


	this->mDirection = player->raw_x > this->p->raw_x;

	standardAction(_stage);
}

void Teresa::move(const StageChild* _stage, int& _dx, int& _dy)
{
	int dx_tmp = player->raw_x > this->p->raw_x ? 0.5*vectorRate : -0.5*vectorRate;
	int dy_tmp = player->raw_y > this->p->raw_y ? 0.5*vectorRate : -0.5*vectorRate;
	_dx = getHorizontalDiffer(_stage, dx_tmp, _dy < 0);
	_dy = dy_tmp > 0 ? getBottomDiffer(_stage, dy_tmp, _dx < 0) : getTopDiffer(_stage, dy_tmp, _dx < 0);
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