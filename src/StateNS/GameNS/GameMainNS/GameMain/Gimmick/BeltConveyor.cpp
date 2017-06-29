#include "BeltConveyor.h"

namespace StateNS {
namespace GameNS {
namespace GameMainNS{


BeltConveyor::BeltConveyor(){
	initialize();
}

BeltConveyor::~BeltConveyor()
{

}

void BeltConveyor::initialize()
{

}

void BeltConveyor::update(PlayerChild* _player)
{


}

void BeltConveyor::draw() const
{
	DrawFormatString(0, 20, MyData::WHITE, "BeltConveyor");
}


//==============================================
//内部プライベート関数
//==============================================

//そんなものはない



}
}
}