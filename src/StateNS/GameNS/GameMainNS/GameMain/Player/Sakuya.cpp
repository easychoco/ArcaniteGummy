#include "Sakuya.h"

#include "..\..\..\..\..\Data.h"
#include "..\..\..\..\..\KeyInput.h"
#include "Mokou.h"

namespace StateNS {
namespace GameNS {
namespace GameMainNS{

Sakuya::Sakuya(int _x, int _y, int _hp) : PlayerChild(5.0f, 25.0f, 1, _hp)
{
	this->p = new Vector2(_x, _y);
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
	this->moveSpeed = 5.0f;
	loadImage();
}

PlayerChild* Sakuya::update(const Stage* _stage)
{
	PlayerChild* next = this;

	standardAction(_stage);

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

void Sakuya::attack(){}

void Sakuya::draw_other() const
{
	//for Debug
	DrawFormatString(0, 30, MyData::BLACK, "Sakuya");
}

void Sakuya::loadImage()
{
	mImage = LoadGraph("Data/Image/sakuya.png");
	assert(mImage != -1 && "自機画像読み込みエラー");
}


//そんなものはない



}
}
}