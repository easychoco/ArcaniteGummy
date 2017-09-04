#include "Sakuya.h"

#include "..\..\..\..\..\Data.h"
#include "..\..\..\..\..\KeyInput.h"
#include "Mokou.h"

namespace StateNS {
namespace GameNS {
namespace GameMainNS{

Sakuya::Sakuya(int _x, int _y, int _hp) : PlayerChild(_x, _y, 7.0f, 25.0f, 1, _hp)
{
	this->camera = new Vector2(_x, _y);
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
	loadImage();
}

PlayerChild* Sakuya::update(const Stage* _stage)
{
	PlayerChild* next = this;

	standardAction(_stage);
	

	//攻撃
	attackTime++;
	if (Input_ATTACK() && attackTime > attackInterval)
	{
		attack();
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

	if (canChangeCharacter())
	{
		animationTime = 0;
		int x = p->raw_x / MyData::vectorRate;
		int y = p->raw_y / MyData::vectorRate;

		//for Debug
		next = new Mokou(x, y, hpController.getHP());
	}

	return next;
}

 
//==============================================
//内部プライベート関数
//==============================================
void Sakuya::attack()
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
	attacks.push_back(new Knife(this->p->raw_x, this->p->raw_y, 32, 32, dx));
}

int Sakuya::getAttackDx() const
{
	//5は棒立ち時の速さ
	int ret = 5 + (int)moveSpeed * (Input_RIGHT() | Input_LEFT());
	ret *= ((direction) ? -1 : 1);

	return ret;
}

void Sakuya::draw_other() const
{
	for (const auto& a : attacks)
	{
		if(a->isActive)a->draw(camera);
	}

	//for Debug
	DrawFormatString(0, 30, MyData::BLACK, "Sakuya");
	DrawFormatString(0, 130, MyData::BLACK, "cam_raw : %d %d", camera->raw_x, camera->raw_y);
	if (attacks.size() > 0)if (attacks[0]->isActive)
	{
		DrawFormatString(0, 150, MyData::BLACK, "atk0     : %d %d", attacks[0]->p->raw_x, attacks[0]->p->raw_y);
		DrawFormatString(0, 170, MyData::BLACK, "atk0_col : %d %d", attacks[0]->getColliX(),  attacks[0]->getColliY());
	}
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
Sakuya::Knife::Knife(int _x, int _y, int _w, int _h, int _dx) :
Attack(_x, _y, _w, _h, ObjectID::A_KNIFE)
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
	this->p->raw_x += dx;
}

void Sakuya::Knife::setStatus(Vector2 _pos, int _dx)
{
	*(this->p) = _pos;
	this->dx = _dx * MyData::vectorRate;
}

void Sakuya::Knife::hittedAction()
{
	this->isActive = false;
}


}
}
}