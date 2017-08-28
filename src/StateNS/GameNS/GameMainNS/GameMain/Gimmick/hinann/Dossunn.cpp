#include "Dossunn.h"
#include "..\Player\PlayerChild.h"

namespace StateNS {
namespace GameNS {
namespace GameMainNS{


Dossunn::Dossunn(){
	initialize();
}

Dossunn::~Dossunn()
{

}

void Dossunn::initialize()
{

}

void Dossunn::update(PlayerChild* _player)
{


}

void Dossunn::draw() const
{
	DrawFormatString(0, 20, MyData::WHITE, "Dossunn");
}


//==============================================
//内部プライベート関数
//==============================================

//そんなものはない



}
}
}