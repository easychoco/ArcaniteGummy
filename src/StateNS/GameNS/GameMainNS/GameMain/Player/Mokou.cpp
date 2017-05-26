#include "Mokou.h"

#include "..\..\..\..\..\Data.h"
#include "..\..\..\..\..\KeyInput.h"

namespace StateNS {
namespace GameNS {
namespace GameMainNS{

//もこたんいんしたお
Mokou::Mokou(int _x, int _y)
{
	this->p = new Vector2(_x, _y);
	initialize();
}

Mokou::~Mokou()
{
	SAFE_DELETE(p);
}

void Mokou::initialize()
{
	this->speed = 5.0f;
}

PlayerChild* Mokou::update()
{
	PlayerChild* next = this;

	standardMove();
	
	return next;
}

void Mokou::draw() const
{
	DrawFormatString(0, 60, MyData::WHITE, "Mokou");

	//自機を描画する場所
	int draw_x = MyData::CX;
	int draw_y = MyData::CY;

	//左端
	if (p->x() < MyData::CX)draw_x = p->x();

	//右端
	if (p->x() > MyData::MAP_WIDTH - MyData::CX)draw_x = p->x() - MyData::MAP_WIDTH + 640;

	//上端
	if (p->y() < MyData::CY)draw_y = p->y();

	//下端
	if (p->y() > MyData::MAP_HEIGHT - MyData::CY)draw_y = p->y() - MyData::MAP_HEIGHT + 480;
	

	DrawCircle(draw_x, draw_y, 5, MyData::GREEN, true);
}



//==============================================
//内部プライベート関数
//==============================================

//そんなものはない



}
}
}