#include "Balloon.h"




namespace StateNS {
namespace GameNS {
namespace GameMainNS{

bool Balloon::imgLoad = false;
int Balloon::images[8];

Balloon::Balloon(int _x, int _y) : EnemyChild(100, _x, _y, 32, 32)
{
	loadImage();

	initialize();
};


Balloon::~Balloon()
{
	//DeleteGraphはしない

}

void Balloon::initialize()
{
	this->mDirection = false;
}

void Balloon::update(const StageChild* _stage, const Vector2* _camera)
{
	actState = ENE_ACT_WALK;
	aTime++;
	mTime++;
	mTime %= 180;

	this->mDirection = player->raw_x > this->p->raw_x;

	standardAction(_stage);
	mImage = images[actState * 2 + (aTime / 10) % 2];
}

void Balloon::move(const StageChild* _stage, int& _dx, int& _dy)
{
	_dy = (int)(2 * vectorRate * sinf(pi(mTime / 90.0f)));
}



//==============================================
//内部プライベート関数
//==============================================
void Balloon::loadImage()
{
	if (!imgLoad)
	{
		int tmp = LoadDivGraph("Data/Image/Poppy.png", 8, 8, 1, 32, 32, images);
		assert(tmp != -1 && "Balloon画像読み込みエラー");
	}
	imgLoad = true;
}

void Balloon::hittedAction()
{

}


}
}
}