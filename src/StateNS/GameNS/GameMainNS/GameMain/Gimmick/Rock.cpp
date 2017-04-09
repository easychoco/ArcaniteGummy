#include "Rock.h"

namespace StateNS {
namespace GameNS {
namespace GameMainNS{


Rock::Rock(){
	initialize();
}

Rock::~Rock()
{

}

void Rock::initialize()
{

}

void Rock::update()
{


}

void Rock::draw() const
{
	DrawFormatString(0, 20, MyData::WHITE, "Rock");
}


//==============================================
//内部プライベート関数
//==============================================

//そんなものはない



}
}
}