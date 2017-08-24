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
	SAFE_DELETE(p);
	SAFE_DELETE(camera);
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
		a->update();
		if (!a->isActive)SAFE_DELETE(a);
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
	attacks.push_back(new Knife(this->p->x(), this->p->y(), 32, 32, 5));
}

void Sakuya::draw_other() const
{
	for (auto& a : attacks)
	{
		a->draw(camera);
	}

	//for Debug
	DrawFormatString(0, 30, MyData::BLACK, "Sakuya");
}

void Sakuya::loadImage()
{
	mImage = LoadGraph("Data/Image/sakuya.png");
	assert(mImage != -1 && "自機画像読み込みエラー");
}

//Knifeクラス
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

void Sakuya::Knife::draw(const Vector2* _camera) const
{
	//画面内にいなければreturn
	if (abs(p->pos_x() - _camera->pos_x()) > 350000 || abs(p->pos_y() - _camera->pos_y()) > 270000)return;


	int draw_x = 320 + (p->pos_x() - _camera->pos_x()) / MyData::vectorRate;
	int draw_y = 240 + (p->pos_y() - _camera->pos_y()) / MyData::vectorRate;

	//描画
	DrawRotaGraph(draw_x, draw_y, 1.0, 0.0, mImage, true, mDirection);
}

void Sakuya::Knife::hittedAction()
{
	this->isActive = false;
}

}
}
}