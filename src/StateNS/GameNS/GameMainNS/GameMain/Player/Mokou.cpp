#include "Mokou.h"

#include "..\..\..\..\..\Data.h"
#include "..\..\..\..\..\KeyInput.h"
#include "Sakuya.h"


namespace StateNS {
namespace GameNS {
namespace GameMainNS{

//もこたんいんしたお
Mokou::Mokou(int _x, int _y, int _hp) : PlayerChild(_x, _y, 3.0f, 22.0f, 2, _hp)
{
	initialize();
}

Mokou::Mokou(int _x, int _y) : Mokou(_x, _y, 100)
{

}

Mokou::~Mokou()
{
	SAFE_DELETE(p);
}

void Mokou::initialize()
{
	//this->moveSpeed = 5.0f;
	loadImage();
	attackTime = 0;
	attacks.push_back(new Fire(this, 0, 0, &direction));
}

PlayerChild* Mokou::update(const Stage* _stage)
{
	PlayerChild* next = this;

	standardAction(_stage);

	//攻撃
	for (auto& a : attacks)
	{
		if (a->isActive)
		{
			a->update();
			a->checkActive(camera);
		}
	}

	if (Input_ATTACK())
	{
		attack();
		canMove = false;
	}
	else
	{
		attacks[0]->setStatus(*p, 0);
		canMove = true;
	}


	//for Debug
	if (canChangeCharacter())
	{
		animationTime = 0;
		int x = p->raw_x / MyData::vectorRate;
		int y = p->raw_y / MyData::vectorRate;

		next = new Sakuya(x, y, hpController.getHP());
	}
	
	return next;
}

int Mokou::specialAction() 
{
	return 0;
}


//==============================================
//内部プライベート関数
//==============================================
void Mokou::attack()
{
	attacks[0]->isActive = true;
}

void Mokou::draw_other() const
{
	for (const auto& a : attacks)
	{
		if (a->isActive)a->draw(camera);
	}

	//for Debug
	DrawFormatString(0, 30, MyData::BLACK, "Mokou");
}


void Mokou::loadImage()
{
//	mImage = LoadGraph("Data/Image/mokou.png");
	LoadDivGraph("Data/Image/Character/chip_mokou.png", 40, 8, 5, 32, 64, mImage, TRUE);
	assert(*mImage != -1 && "自機画像読み込みエラー");
}

//==============================================
//Fireクラス
//==============================================
Mokou::Fire::Fire(const PlayerChild* _parent, int _x, int _y, bool *_direction) :
Attack(_parent, _x, _y, 96, 10, ObjectID::A_FIRE),
direction(_direction)
{
	this->mTime = 0;

	//for Debug
	this->damageValue = 20;

	mImage = 0;
	int tmp = LoadDivGraph("Data/Image/Fire.png", 3, 1, 3, 96, 32, images);
	assert(tmp != -1 && "Fire画像読み込みエラー");
}

Mokou::Fire::~Fire()
{
	DeleteGraph(mImage);
}

/*
void Mokou::Fire::update()
{
	mTime++;
	isActive = false;
}

void Mokou::Fire::setStatus(Vector2 _pos, int direction)
{
	*(this->p) = _pos;
	this->mDirection = direction;

	isActive = true;
}
*/

void Mokou::Fire::update()
{
	mTime++;
	mDirection = *direction;

	this->height = min(mTime, 32) * vectorRate;

	this->p->raw_x = parent->getVector2()->raw_x + ((*direction) ?  -54000 : 54000);
	this->p->raw_y = parent->getVector2()->raw_y;
	isActive = false;

	if (mTime < 5)mImage = images[0];
	else if (mTime < 10)mImage = images[1];
	else
	{
		mImage = images[2];

		float angle = mTime * Pi / 3.0f;
		this->p->raw_x += (int)(3000 * cosf(angle));
		this->p->raw_y += (int)(3000 * sinf(angle));
	}
}

void Mokou::Fire::setStatus(Vector2 _pos, int direction)
{
	this->mTime = 1;

	//ふっとべー
	this->p->raw_x = -100000;
}


void Mokou::Fire::hittedAction()
{
	//do nothing
}



}
}
}