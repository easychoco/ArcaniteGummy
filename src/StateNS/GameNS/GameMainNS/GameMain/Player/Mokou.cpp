#include "Mokou.h"

#include "..\..\..\..\..\Data.h"
#include "..\..\..\..\..\KeyInput.h"
#include "Sakuya.h"


namespace StateNS {
namespace GameNS {
namespace GameMainNS{

//もこたんいんしたお
Mokou::Mokou(int _x, int _y, int _hp) : PlayerChild(_x, _y, 5.0f, 20.0f, 2, _hp)
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
}

PlayerChild* Mokou::update(const Stage* _stage)
{
	PlayerChild* next = this;

	standardAction(_stage);

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

}

void Mokou::draw_other() const
{
	//for Debug
	DrawFormatString(0, 30, MyData::BLACK, "Mokou");
}


void Mokou::loadImage()
{
	mImage = LoadGraph("Data/Image/mokou.png");
	assert(mImage != -1 && "自機画像読み込みエラー");
}


}
}
}