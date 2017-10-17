#include "Karon.h"

#include "..\Collision.h"


namespace StateNS {
namespace GameNS {
namespace GameMainNS{
	
bool Karon::imgLoad = false;
int Karon::images[8];


Karon::Karon(int _x, int _y) : EnemyChild(100000, _x, _y, 32, 32)
{
	loadImage();
	
	initialize();
};


Karon::~Karon()
{
	//DeleteGraphはしない
}

void Karon::initialize()
{
	this->mDirection = true;
	this->moveSpeed = 1000;
	this->isAlive = true;

}

void Karon::update(const StageChild* _stage,const Vector2* _camera)
{
	aTime++;

	//ダメージを受けたら
	if (damaged && isAlive) 
	{
		hpController.recover(1);
		isAlive = false;
		hpController.isMuteki = true;
	}


	if (!isAlive) {
		this->collision->noCollide = true;
		aTime = 0;
		actState = ENE_ACT_DEAD;
		mTime++;
	}
	else mTime = 0;

	if (mTime == 300) 
	{
		actState = ENE_ACT_WALK;
		isAlive = true;
		hpController.isMuteki = false;
		this->collision->noCollide = false;
		hpController.recover(500);
	}
	standardAction(_stage);
	
	mImage = images[actState * 2 + (aTime / 10) % 2];
}

void Karon::move(const StageChild* _stage, int& _dx, int& _dy)
{
	_dy = getBottomDiffer(_stage, 4000, _dx < 0);
	if (!isAlive)return;

	//_dyが0でなかったら空中にいる
	if (_dy != 0)
	{
		_dx = 0;
		return;
	}
	_dx = getHorizontalDiffer(_stage, moveSpeed, _dy < 0);
	this->mDirection = _dx > 0;

	//_dxが0で壁にぶつかる
	if (_dx == 0)
	{
		_dy = 0;
		mDirection = !mDirection;
		moveSpeed = -moveSpeed;
	}

}


//==============================================
//内部プライベート関数
//==============================================
void Karon::loadImage()
{
	if (!imgLoad)
	{
		int tmp = LoadDivGraph("Data/Image/Karon.png", 8, 8, 1, 32, 32, images);
		assert(tmp != -1 && "Karon画像読み込みエラー");
	}
	imgLoad = true;
}

void Karon::hittedAction()
{
	aTime = 0;
	actState = ENE_ACT_DEAD;
}

}
}
}