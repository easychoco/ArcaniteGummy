#include "Icicle.h"




namespace StateNS {
namespace GameNS {
namespace GameMainNS{

bool Icicle::imgLoad = false;
int Icicle::images[8];

Icicle::Icicle(int _x, int _y) : EnemyChild(100, _x, _y, 32, 32)
{
	loadImage();

	initialize();
};


Icicle::~Icicle()
{
	//DeleteGraphはしない

}

void Icicle::initialize()
{
	this->mDirection = false;
	mTime = 0;
	nowfall = false;
}

void Icicle::update(const StageChild* _stage, const Vector2* _camera)
{
	if (actState == ENE_ACT_DEAD && aTime >= 60)actState = ENE_ACT_NONE;
	aTime++;
	if (!nowfall)
	{
		if ((abs(player->raw_x - this->p->raw_x) <= 32 * 3 * vectorRate))actState = ENE_ACT_WALK;
		else actState = ENE_ACT_NONE;
	}
	else mTime++;

	if ((abs(player->raw_x - this->p->raw_x) <= 32 * vectorRate) && player->raw_y > this->p->raw_y)
	{
		nowfall = true;
		actState = ENE_ACT_ATTACK;
	}
	standardAction(_stage);

	mImage = images[actState * 2 + (aTime / 30) % 2];
}

void Icicle::move(const StageChild* _stage, int& _dx, int& _dy)
{
	if(mTime>0)_dy = vectorRate*2;
}




//==============================================
//内部プライベート関数
//==============================================
void Icicle::loadImage()
{
	if (!imgLoad)
	{
		int tmp = LoadDivGraph("Data/Image/Icicle.png", 8, 8, 1, 32, 32, images);
		assert(tmp != -1 && "Icicle画像読み込みエラー");
	}
	imgLoad = true;
}

void Icicle::hittedAction()
{
	aTime = 0;
	actState = ENE_ACT_DEAD;
}


}
}
}