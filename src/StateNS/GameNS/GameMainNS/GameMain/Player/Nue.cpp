#include "Nue.h"

#include "..\..\..\..\..\Data.h"
#include "..\..\..\..\..\KeyInput.h"

namespace StateNS {
namespace GameNS {
namespace GameMainNS{

Nue::Nue() : PlayerChild(5.0f, 15.0f, 1, 200)
{

}

Nue::~Nue()
{

}

PlayerChild* Nue::update(const Stage* _stage)
{
	PlayerChild* next = this;

	return next;
}




//==============================================
//内部プライベート関数
//==============================================
void Nue::initialize(){}

void Nue::attack(){}

void Nue::draw_other() const {};

void Nue::loadImage() {} 

//そんなものはない



}
}
}