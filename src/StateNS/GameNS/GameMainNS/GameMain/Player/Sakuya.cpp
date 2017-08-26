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
	//this->moveSpeed = 5.0f;
	loadImage();
}

PlayerChild* Sakuya::update(const Stage* _stage)
{
	PlayerChild* next = this;

	standardAction(_stage);

	//攻撃
	if (Input_ATTACK())
	{
		attack();
	}
	
	for (auto& a : attacks)
	{
		if (a->isActive)
		{
			a->update();
			a->checkActive(camera);
		}
	}

	//for Debug
	if (canChangeCharacter())
	{
		animationTime = 0;
		int x = p->raw_x / MyData::vectorRate;
		int y = p->raw_y / MyData::vectorRate;

		next = new Mokou(x, y, hpController.getHP());
	}

	return next;
}




//==============================================
//内部プライベート関数
//==============================================
void Sakuya::attack()
{
	//使っていないオブジェクトを再利用
	for (auto& a : attacks)
	{
		if (!a->isActive)
		{
			a->setStatus(*p, 5);
			a->isActive = true;
			return;
		}
	}

	//すべて使っていたらnewする
	attacks.push_back(new Knife(this->p->raw_x, this->p->raw_y, 32, 32, 5));
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
	if(attacks.size() > 0)if(attacks[0]->isActive)DrawFormatString(0, 150, MyData::BLACK, "atk0   : %d %d", attacks[0]->p->raw_x, attacks[0]->p->raw_y);
}

void Sakuya::loadImage()
{
	mImage = LoadGraph("Data/Image/sakuya.png");
	assert(mImage != -1 && "自機画像読み込みエラー");
}

//==============================================
//Knifeクラス
//==============================================
Sakuya::Knife::Knife(int _x, int _y, int _w, int _h, int _dx) :
Attack(_x, _y, _w, _h)
{
	this->dx = _dx * MyData::vectorRate;
	mDirection = _dx < 0;

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