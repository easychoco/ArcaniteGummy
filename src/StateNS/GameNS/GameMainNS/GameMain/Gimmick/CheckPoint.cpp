#include "CheckPoint.h"

namespace StateNS {
namespace GameNS {
namespace GameMainNS{


CheckPoint::CheckPoint(){
	initialize();
}

CheckPoint::~CheckPoint()
{

}

void CheckPoint::initialize()
{

}

void CheckPoint::update()
{


}

void CheckPoint::draw() const
{
	DrawFormatString(0, 20, MyData::WHITE, "CheckPoint");
}


//==============================================
//内部プライベート関数
//==============================================

//そんなものはない



}
}
}