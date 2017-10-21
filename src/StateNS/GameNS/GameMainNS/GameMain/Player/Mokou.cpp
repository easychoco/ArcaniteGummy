#include "Mokou.h"

#include "..\..\..\..\..\KeyInput.h"
#include "Sakuya.h"
#include "Nue.h"


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

	sound->deleteSound("fire");
}

void Mokou::initialize()
{
	//this->moveSpeed = 5.0f;
	loadImage();
	attackTime = 0;
	attacks.push_back(new Fire(this, 0, 0, &direction));

	sound->setSound("Data/Sound/attack_fire.mp3", "fire");
}

PlayerChild* Mokou::update(const StageChild* _stage)
{
	PlayerChild* next = this;

	if (lock)
	{
		lock = false;
		return next;
	}

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
		if (actionState != ACT_LADDER)
		{
			attack();
			if (Input_UP())
			{
				actionState = ACT_ATTACK_UP;
				animeNum = 4;
			}
			canMove = false;
		}
	}
	else
	{
		attacks[0]->setStatus(*p, 0);
		canMove = true;
	}

	if (!canMove)
	{
		if (Input_RIGHT())this->direction = false;
		else if (Input_LEFT())this->direction = true;
	}

	if (canChangeCharacter())
	{
		animationTime = 0;
		int x = p->raw_x / MyData::vectorRate;
		int y = p->raw_y / MyData::vectorRate;

		int nextCharacter = _stage->getChangeableCharacter();

		if (nextCharacter & StageChild::ChangeableCharacter::CHARA_SAKUYA)
			next = new Sakuya(x, y, hpController.getHP());
		else if (nextCharacter & StageChild::ChangeableCharacter::CHARA_NUE)
			next = new Nue(x, y, hpController.getHP());

		if (this->cameraLocked)next->lockCameraPos(this->camera);
	}
	
	return next;
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

}

void Mokou::loadImage()
{
//	mImage = LoadGraph("Data/Image/mokou.png");
	LoadDivGraph("Data/Image/Character/chip_mokou.png", 32, 8, 4, 32, 64, mImage, TRUE);
	assert(*mImage != -1 && "自機画像読み込みエラー");
}

void Mokou::animation()
{
	int num = 0;
	switch (actionState)
	{
	case ACT_WALK:num = 8 + (animeCount / 10) % 4; break;
	case ACT_RUN:num = 12 + (animeCount / 10) % 4; break;
	case ACT_SIT:num = 5; break;
	case ACT_ATTACK_UP:num = 4; break;
	case ACT_AIR:num = 1; break;
	case ACT_RUNJUMP:num = 1; break;
	case ACT_ATTACK_SIDE:num = 2; break;
	//case ACT_ATTACK_SIDE_WALK:num = 16 + (animeCount / 10) % 4; break;
	//case ACT_ATTACK_SIDE_RUN:num = 20 + (animeCount / 10) % 4; break;
	//case ACT_ATTACK_UP_WALK:num = 24 + (animeCount / 10) % 4; break;
	//case ACT_ATTACK_UP_RUN:num = 28 + (animeCount / 10) % 4; break;
	case ACT_LADDER:num = 3; break;
	default:animeCount = 0; break;
	}

	animeCount++;

	assert(!(num < 0 || 33 <= num) && "自機画像範囲外");
	animeNum = num;
}

//==============================================
//Fireクラス
//==============================================
Mokou::Fire::Fire(const PlayerChild* _parent, int _x, int _y, bool *_direction) :
Attack(_parent, _x, _y, 96, 48, ObjectID::A_FIRE),
direction(_direction)
{
	this->mTime = 0;

	this->damageValue = 34;

	mImage = 0;
	int tmp = LoadDivGraph("Data/Image/Fire.png", 3, 1, 3, 96, 32, images);
	int tmp2 = LoadDivGraph("Data/Image/Fire2.png", 3, 3, 1, 32, 96, images2);
	assert(tmp != -1 && "Fire画像読み込みエラー");
	assert(tmp2 != -1 && "Fire画像読み込みエラー");

}

Mokou::Fire::~Fire()
{
	DeleteGraph(mImage);
}

void Mokou::Fire::update()
{
	mTime++;
	mDirection = *direction;
	int img[3];

	if (mTime % 10 == 0)sound->playSound("fire", BACK, true);

	if(Input_UP()) {
		this->height = 96;
		this->width = min(mTime, 32) * vectorRate;
		this->p->raw_x = parent->getVector2()->raw_x;
		this->p->raw_y = parent->getVector2()->raw_y - 64000;
		for (int i = 0; i < 3; i++)img[i] = images2[i];
	}
	else{
		this->width = 96;
		this->height = min(mTime, 32) * vectorRate;
		this->p->raw_x = parent->getVector2()->raw_x + ((*direction) ? -54000 : 54000);
		this->p->raw_y = parent->getVector2()->raw_y;
		for (int i = 0; i < 3; i++)img[i] = images[i];
	}


	if (mTime < 5)mImage = img[0];
	else if (mTime < 10)mImage = img[1];
	else
	{
		mImage = img[2];

		float angle = mTime * Pi / 3.0f;
		this->p->raw_x += (int)(3000 * cosf(angle));
		this->p->raw_y += (int)(3000 * sinf(angle));
	}

	isActive = false;
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