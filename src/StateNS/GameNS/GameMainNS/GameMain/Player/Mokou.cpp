#include "Mokou.h"

#include "..\..\..\..\..\Data.h"
#include "..\..\..\..\..\KeyInput.h"
#include "Sakuya.h"


namespace StateNS {
namespace GameNS {
namespace GameMainNS{

//もこたんいんしたお
Mokou::Mokou(int _x, int _y, int _hp) : PlayerChild(_x, _y, 5.0f, 25.0f, 2, _hp)
{
	this->camera = new Vector2(_x, _y);
	initialize();
}

Mokou::Mokou(int _x, int _y) : Mokou(_x, _y, 100)
{

}

Mokou::~Mokou()
{
	SAFE_DELETE(p);
	SAFE_DELETE(camera);
}

void Mokou::initialize()
{
	//this->moveSpeed = 5.0f;
	loadImage();
	attackTime = 0;
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
	}
	else
	{
		attackTime = 0;
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

//==============================================
//内部プライベート関数
//==============================================
void Mokou::attack()
{
	if (attacks.size() == 0)
	{
		attacks.push_back(new Fire(0, 0, 32, 32, true));
		attacks.push_back(new Fire(0, 0, 32, 32, true));
		attacks.push_back(new Fire(0, 0, 32, 32, true));
	}

	++attackTime;
	//if (attackTime > 0)
	int new_pos = 32000 * ((direction) ? -1 : 1);

	attacks[0]->setStatus(Vector2(this->p->raw_x + new_pos * 1, this->p->raw_y, true), this->direction);
	if (attackTime > 10)attacks[1]->setStatus(Vector2(this->p->raw_x + new_pos * 2, this->p->raw_y, true), this->direction);
	if (attackTime > 20)attacks[2]->setStatus(Vector2(this->p->raw_x + new_pos * 3, this->p->raw_y, true), this->direction);
	
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
Mokou::Fire::Fire(int _x, int _y, int _w, int _h, bool _direction) :
Attack(_x, _y, _w, _h, ObjectID::A_FIRE)
{
	this->mTime = 0;
	mDirection = _direction;

	//for Debug
	this->damageValue = 20;

	mImage = LoadGraph("Data/Image/fire.png");
	assert(mImage != -1 && "Fire画像読み込みエラー");
}

Mokou::Fire::~Fire()
{
	DeleteGraph(mImage);
}

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

void Mokou::Fire::hittedAction()
{
	//do nothing
}



}
}
}