#include "MovingFloor.h"
#include "..\Player\PlayerChild.h"

namespace StateNS {
namespace GameNS {
namespace GameMainNS{


MovingFloor::MovingFloor(){
	initialize();
}

MovingFloor::~MovingFloor()
{

}

void MovingFloor::initialize()
{

}

void MovingFloor::update(PlayerChild* _player)
{


}

void MovingFloor::draw() const
{
	DrawFormatString(0, 20, MyData::WHITE, "MovingFloor");
}


//==============================================
//内部プライベート関数
//==============================================

//そんなものはない



}
}
}