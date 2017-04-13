#include "Mokou.h"

#include "..\..\..\..\Data.h"
#include "..\..\..\..\KeyInput.h"

namespace StateNS {
namespace GameNS {
namespace GameMainNS{

Mokou::Mokou()
{

}

Mokou::~Mokou()
{

}

PlayerChild* Mokou::update()
{
	PlayerChild* next = this;

	return next;
}

void Mokou::draw() const
{
	DrawFormatString(0, 60, MyData::WHITE, "Mokou");
}



//==============================================
//内部プライベート関数
//==============================================

//そんなものはない



}
}
}