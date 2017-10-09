#include "Mariri.h"




namespace StateNS {
namespace GameNS {
namespace GameMainNS{

bool Mariri::imgLoad = false;
int Mariri::images[8];


Mariri::Mariri(int _x, int _y) : EnemyChild(100, _x, _y, 32, 32)
{
	loadImage();

	initialize();
};


Mariri::~Mariri()
{
	//DeleteGraphはしない
}

void Mariri::initialize()
{
	this->mDirection = false;
	this->moveSpeed = 0;
	this->mTime = 0;
	this->attackDirection = false;
}

void Mariri::update(const StageChild* _stage,const Vector2* _camera)
{

	if (actState == ENE_ACT_DEAD && aTime >= 60)actState = ENE_ACT_WALK;
	aTime++;
	mTime++;
	standardAction(_stage);
	this->mDirection = player->raw_x > this->p->raw_x;

	mImage = images[actState * 2 + (aTime / 10) % 2];

}

void Mariri::move(const StageChild* _stage, int& _dx, int& _dy)
{		
	if (mTime == 30) 
	{
		aTime = 0;
		actState = ENE_ACT_WALK;
		attackDirection = mDirection;
	}
	if (30 <= mTime &&mTime<=60) 
	{
		int tmp_dy = getTopDiffer(_stage, -2 * vectorRate, _dx < 0);
		_dy = tmp_dy;
		int tmp_dx = attackDirection ? getHorizontalDiffer(_stage, vectorRate, _dy < 0) : getHorizontalDiffer(_stage, -vectorRate, _dy < 0);
		_dx = tmp_dx;
	}
	
	if (mTime == 60)
	{
		aTime = 0;
		actState = ENE_ACT_ATTACK;
	}

	if (60 < mTime) {
		_dy = getBottomDiffer(_stage, 2 * vectorRate, _dx < 0);
		
		if (abs(_dy) >0)
		{
			int tmp_dx = attackDirection ? getHorizontalDiffer(_stage, vectorRate, _dy < 0) : getHorizontalDiffer(_stage, -vectorRate, _dy < 0);
			_dx = tmp_dx;
		}
		else {
		
			actState = ENE_ACT_NONE;
			if (mTime > 150)mTime = 0;
		}




	}



}


//==============================================
//内部プライベート関数
//==============================================
void Mariri::loadImage()
{
	if (!imgLoad)
	{
		int tmp = LoadDivGraph("Data/Image/Mariri.png", 8, 8, 1, 32, 32, images);
		assert(tmp != -1 && "Mariri画像読み込みエラー");
	}
	imgLoad = true;
}

void Mariri::hittedAction()
{
	aTime = 0;
	actState = ENE_ACT_DEAD;
}




}
}
}