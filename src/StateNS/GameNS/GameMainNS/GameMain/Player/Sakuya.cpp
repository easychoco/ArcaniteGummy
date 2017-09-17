#include "Sakuya.h"

#include "..\..\..\..\..\Data.h"
#include "..\..\..\..\..\KeyInput.h"
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

}

void Sakuya::initialize()
{
	attackTime = 0;

	stoppingTime = 0;
	isStoppingTime = false;

	loadImage();
}

PlayerChild* Sakuya::update(const Stage* _stage)
{
	PlayerChild* next = this;

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

		//for Debug
		next = new Nue(x, y, hpController.getHP());
	}

	return next;
}

int Sakuya::specialAction()
{
	return 0;
}

 
//==============================================
//内部プライベート関数
//==============================================
void Sakuya::attack(const Stage* _stage)
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

void Sakuya::processAttack(const Stage* _stage)
{
	attackTime++;
	if (Input_ATTACK() && attackTime > attackInterval)
	{
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
	//Cで時止め
	if (Input_C() && !prePushC)
	{
		isStoppingTime = true;
		stopDynamics = StopType::TYPE_SAKUYA;
	}

	if (!isStoppingTime)return;

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

	//for Debug
	DrawFormatString(0, 130, BLACK, "%d", attacks.size());
}

void Sakuya::loadImage()
{
//	mImage = LoadGraph("Data/Image/sakuya.png");
	int tmp = LoadDivGraph("Data/Image/Character/chip_sakuya.png", 40, 8, 5, 32, 64, mImage);
	assert(tmp != -1 && "自機画像読み込みエラー");
}

//==============================================
//Knifeクラス
//==============================================
Sakuya::Knife::Knife(const PlayerChild* _parent, const Stage* _stage, int _x, int _y, int _dx) :
Attack(_parent, _x, _y, 32, 32, ObjectID::A_KNIFE),
stage(_stage)
{
	this->dx = _dx * MyData::vectorRate;
	mDirection = _dx < 0;

	//for Debug
	this->damageValue = 20;

	mImage = LoadGraph("Data/Image/Knife.png");
	assert(mImage != -1 && "Knife画像読み込みエラー");
}

Sakuya::Knife::~Knife()
{
	DeleteGraph(mImage);
}

void Sakuya::Knife::update()
{
	int dx_tmp = getHorizontalDiffer(stage, dx, false, false);
	this->p->raw_x += dx_tmp;

	if (dx_tmp == 0)this->isActive = false;
}

void Sakuya::Knife::setStatus(Vector2 _pos, int _dx)
{
	*(this->p) = _pos;
	this->dx = _dx * MyData::vectorRate;
	this->mDirection = _dx < 0;
}

void Sakuya::Knife::hittedAction()
{
	this->isActive = false;
}


}
}
}