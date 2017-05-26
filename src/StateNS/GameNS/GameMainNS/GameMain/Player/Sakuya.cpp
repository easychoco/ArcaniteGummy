#include "Sakuya.h"

#include "..\..\..\..\..\Data.h"
#include "..\..\..\..\..\KeyInput.h"

namespace StateNS {
namespace GameNS {
namespace GameMainNS{

Sakuya::Sakuya()
{

}

Sakuya::~Sakuya()
{

}

PlayerChild* Sakuya::update()
{
	PlayerChild* next = this;

	return next;
}

void Sakuya::draw() const
{
	DrawFormatString(0, 40, MyData::WHITE, "Sakuya");
}



//==============================================
//内部プライベート関数
//==============================================

//そんなものはない



}
}
}