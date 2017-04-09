#include "Pause.h"
#include "..\..\StateParent.h"

#include "..\..\..\Data.h"
#include "..\..\..\KeyInput.h"


namespace StateNS {
namespace GameNS {
namespace GameMainNS {


Pause::Pause()
{

}

Pause::~Pause()
{

}

void Pause::initialize()
{

}

Child* Pause::update(GameParent* _parent)
{
	Child* next = this;


	return next;
}

void Pause::draw() const
{
	DrawFormatString(0, 0, MyData::WHITE, "Pause");
}





}
}
}

