#include "SlippingFloor.h"

namespace StateNS {
namespace GameNS {
namespace GameMainNS{


SlippingFloor::SlippingFloor(){
	initialize();
}

SlippingFloor::~SlippingFloor()
{

}

void SlippingFloor::initialize()
{

}

void SlippingFloor::update(PlayerChild* _player)
{


}

void SlippingFloor::draw() const
{
	DrawFormatString(0, 20, MyData::WHITE, "SlippingFloor");
}


//==============================================
//内部プライベート関数
//==============================================

//そんなものはない



}
}
}