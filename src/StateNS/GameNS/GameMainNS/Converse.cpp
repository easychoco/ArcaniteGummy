#include "Converse.h"

#include "..\..\..\Data.h"
#include "..\..\..\KeyInput.h"


namespace StateNS {
namespace GameNS {
namespace GameMainNS {


Converse::Converse()
{

}

Converse::~Converse()
{

}

void Converse::initialize()
{

}

Child* Converse::update(GameParent* _parent)
{
	Child* next = this;

	return next;
}

void Converse::draw() const
{
	DrawFormatString(0, 0, MyData::WHITE, "Converse");
}






}
}
}
