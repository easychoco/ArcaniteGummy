#include "Sakuya.h"

#include "..\..\..\..\..\KeyInput.h"
#include "Mokou.h"
#include "Nue.h"

namespace StateNS {
namespace GameNS {
namespace GameMainNS{

Sakuya::Sakuya(int _x, int _y, int _hp) : PlayerChild(_x, _y, 3.0f, 22.0f, 1, _hp)
{
	initialize();
}

Sakuya::Sakuya(int _x, int _y) : Sakuya(_x, _y, 100)
{

}

Sakuya::~Sakuya()
{
	sound->deleteSound("knife");
	sound->deleteSound("stoptime");
}

void Sakuya::initialize()
{
	attackTime = 0;

	notStoppingTime = 0;
	stoppingTime = 0;
	isStoppingTime = false;

	sound->setSound("Data/Sound/attack_knife.mp3", "knife");
	sound->setSound("Data/Sound/stoptime.mp3", "stoptime");

	loadImage();
}

PlayerChild* Sakuya::update(const StageChild* _stage)
{
	PlayerChild* next = this;

	if (lock)
	{
		lock = false;
		return next;
	}


	standardAction(_stage);
	
	//攻撃
	processAttack(_stage);

	//時止めの処理
	processStopDynamics();

	prePushC = Input_C();

	if (canChangeCharacter())
	{
		animationTime = 0;
		int x = p->raw_x / MyData::vectorRate;
		int y = p->raw_y / MyData::vectorRate;

		int nextCharacter = _stage->getChangeableCharacter();
		
		if(nextCharacter & StageChild::ChangeableCharacter::CHARA_NUE)
			next = new Nue(x, y, hpController.getHP());
		else if (nextCharacter & StageChild::ChangeableCharacter::CHARA_MOKOU)
			next = new Mokou(x, y, hpController.getHP());
	}

	return next;
}


 
//==============================================
//内部プライベート関数
//==============================================
void Sakuya::attack(const StageChild* _stage)
{
	int dx = getAttackDx();

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
	attacks.push_back(new Knife(this, _stage, this->p->raw_x, this->p->raw_y, dx));
}

int Sakuya::getAttackDx() const
{
	//5は棒立ち時の速さ
	int ret = 5 + (int)moveSpeed * (in_right | in_left);
	ret *= ((direction) ? -1 : 1);

	return ret;
}

void Sakuya::processAttack(const StageChild* _stage)
{
	attackTime++;
	if (Input_ATTACK() && attackTime > attackInterval && actionState!=ACT_LADDER)
	{
		sound->playSound("knife", BACK, true);
		attack(_stage);
		attackTime = 0;
	}

	for (auto& a : attacks)
	{
		if (a->isActive)
		{
			a->update();
			a->checkActive(camera);
		}
	}
}

void Sakuya::processStopDynamics()
{
	if(!isStoppingTime)++notStoppingTime;
	

	//Cで時止め
	if (Input_C() && !prePushC && notStoppingTime > 60)
	{
		isStoppingTime = true;
		notStoppingTime = 0;
		stopDynamics = StopType::TYPE_SAKUYA;
	}

	if (!isStoppingTime)return;

	if (stoppingTime == 0)sound->playSound("stoptime");
	stoppingTime++;

	//制限時間を超えたら解除
	if (stoppingTime > maxStoppingTime)
	{
		stoppingTime = 0;
		isStoppingTime = false;
		stopDynamics = StopType::TYPE_NONE;
	}
}

void Sakuya::draw_other() const
{
	for (const auto& a : attacks)
	{
		if(a->isActive)a->draw(camera);
	}
}

void Sakuya::loadImage()
{
//	mImage = LoadGraph("Data/Image/sakuya.png");
	int tmp = LoadDivGraph("Data/Image/Character/chip_sakuya.png", 32, 8, 4, 32, 64, mImage);
	assert(tmp != -1 && "自機画像読み込みエラー");
}

void Sakuya::animation()
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
	case ACT_ATTACK_SIDE_WALK:num = 16 + (animeCount / 10) % 4; break;
	case ACT_ATTACK_SIDE_RUN:num = 20 + (animeCount / 10) % 4; break;
	case ACT_ATTACK_UP_WALK:num = 24 + (animeCount / 10) % 4; break;
	case ACT_ATTACK_UP_RUN:num = 28 + (animeCount / 10) % 4; break;
	case ACT_LADDER:num = 3; break;
	default:animeCount = 0; break;
	}

	animeCount++;

	assert(!(num < 0 || 33 <= num) && "自機画像範囲外");
	animeNum = num;
}

//==============================================
//Knifeクラス
//==============================================
Sakuya::Knife::Knife(const PlayerChild* _parent, const StageChild* _stage, int _x, int _y, int _dx) :
Attack(_parent, _x, _y, 32, 32, ObjectID::A_KNIFE),
stage(_stage)
{
	this->up = Input_UP();
	this->dx =  _dx * MyData::vectorRate;

	mDirection = _dx < 0;

	//for Debug
	this->damageValue = 100;

	if(up)this->mImage = LoadGraph("Data/Image/Knife2.png");
	else this->mImage = LoadGraph("Data/Image/Knife.png");
	assert(mImage != -1 && "Knife画像読み込みエラー");
}

Sakuya::Knife::~Knife()
{
	DeleteGraph(mImage);
}

void Sakuya::Knife::update()
{
	int tmp = 0;
	if (up) 
	{
		tmp = getTopDiffer(stage, -abs(dx), false, true);
		this->p->raw_y += tmp;
	}
	else 
	{
		tmp = getHorizontalDiffer(stage, dx, false, true);
		this->p->raw_x += tmp;
	}

	if (tmp == 0)this->isActive = false;
}

void Sakuya::Knife::setStatus(Vector2 _pos, int _dx)
{
	*(this->p) = _pos;
	this->up = Input_UP();
	this->dx = _dx * MyData::vectorRate;
	this->mDirection = _dx < 0;

	////////////////////////重そう///////////////////////////
	if (up)this->mImage = LoadGraph("Data/Image/Knife2.png");
	else this->mImage = LoadGraph("Data/Image/Knife.png");
	assert(mImage != -1 && "Knife画像読み込みエラー");

}

void Sakuya::Knife::hittedAction()
{
	this->isActive = false;
}


}
}
}