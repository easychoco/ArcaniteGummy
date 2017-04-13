#include "System.h"

#include "..\..\..\..\Data.h"
#include "..\..\..\..\KeyInput.h"

namespace StateNS {
namespace GameNS {
namespace GameMainNS{


System::System(){
	initialize();
}

System::~System()
{

}

void System::initialize()
{

}

void System::update()
{


}

void System::draw() const
{
	DrawFormatString(0, 80, MyData::WHITE, "System");
}


//==============================================
//内部プライベート関数
//==============================================

//そんなものはない



}
}
}