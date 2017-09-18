#include "Pikachi.h"




namespace StateNS {
namespace GameNS {
namespace GameMainNS{

Pikachi::Pikachi(int _x, int _y) : EnemyChild(100, _x, _y, 32, 32,1,1)
{
	if(!imgLoad)loadImage();
	assert(mImage != -1 && "Pikachi画像読み込みエラー!");

	initialize();
};


Pikachi::~Pikachi()
{

}

void Pikachi::initialize()
{
	this->mDirection = false;
	this->moveSpeed = 0;
}

void Pikachi::update(const Stage* _stage,const Vector2* _camera)
{
	mTime++;
	mTime %= 211;
	standardAction(_stage);
	this->mDirection = player->raw_x > this->p->raw_x;

	if (mTime == 180)
	{
		attack(_stage);
	}



	//攻撃
	for (auto& a : attacks)
	{
		if (a->isActive)
		{
			a->update();
			a->checkActive(_camera);
		}
	}





}

void Pikachi::move(const Stage* _stage, int& _dx, int& _dy)
{

	//_dy = (int)(2 * vectorRate * sinf(pi(mTime / 90.0f)));
	if (150 <= mTime ) 
	{
		int d = mTime < 180 ? -1 : 1;
		_dy = 2*d*vectorRate;
	}



}


//==============================================
//内部プライベート関数
//==============================================

void Pikachi::hittedAction()
{

}

void Pikachi::attack(const Stage* _stage)
{
	int dx = mDirection ? 5 : -5;

	//使っていないオブジェクトを再利用
	for (auto& a : attacks)
	{
		if (!a->isActive)
		{
			a->setStatus(*p, dx);
			a->isActive = true;
			return;
		}
	}

	//すべて使っていたらnewする
	attacks.push_back(new Thunder(this, _stage, this->p->raw_x, this->p->raw_y, dx));
}

void Pikachi::draw_other(const Vector2* _camera) const
{
	for (const auto& a : attacks)
	{
		if (a->isActive)a->draw(_camera);
	}

	//for Debug
	DrawFormatString(0, 130, BLACK, "%d", attacks.size());
}

//==============================================
//Thunderクラス
//==============================================
Pikachi::Thunder::Thunder(const EnemyChild* _parent, const Stage* _stage, int _x, int _y, int _dx) :
	Attack(_parent, _x, _y, 32, 32, ObjectID::ID_NONE),
	stage(_stage)
{
	this->dx = _dx * MyData::vectorRate;
	mDirection = _dx < 0;

	//for Debug
	this->damageValue = 20;

//	mImage = 0;
//	int tmp = LoadDivGraph("Data/Image/Thunder.png", 3, 1, 3, 96, 32, images);
	mImage = LoadGraph("Data/Image/PikachiAttack.png");
	assert(mImage != -1 && "PikachiAttack画像読み込みエラー");
}

Pikachi::Thunder::~Thunder()
{
	DeleteGraph(mImage);
}

void Pikachi::Thunder::update()
{
	int dx_tmp = getHorizontalDiffer(stage, dx, false, false);
	this->p->raw_x += dx_tmp;

	if (dx_tmp == 0)this->isActive = false;
}

void Pikachi::Thunder::setStatus(Vector2 _pos, int _dx)
{
	*(this->p) = _pos;
	this->dx = _dx * MyData::vectorRate;
	this->mDirection = _dx < 0;
}

void Pikachi::Thunder::hittedAction()
{
	this->isActive = false;
}





}
}
}