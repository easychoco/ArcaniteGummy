#include "Switch.h"

namespace StateNS {
namespace GameNS {
namespace GameMainNS{


Switch::Switch(){
	initialize();
}

Switch::~Switch()
{

}

void Switch::initialize()
{

}

void Switch::update(PlayerChild* _player)
{


}

void Switch::draw() const
{
	DrawFormatString(0, 20, MyData::WHITE, "Switch");
}


//==============================================
//内部プライベート関数
//==============================================

//そんなものはない



}
}
}