#include "Clear.h"
#include "..\StateParent.h"

#include "Play.h"

#include "..\..\Data.h"
#include "..\..\KeyInput.h"


namespace StateNS {
namespace GameNS {


Clear::Clear()
{

}

Clear::~Clear()
{

}

void Clear::initialize()
{

}

Child* Clear::update(StateNS::Parent* _parent)
{
	Child* next = this;

	if (Input_C())
	{
		_parent->moveTo(_parent->NextSequence::SEQ_TITLE);
	}
	if (Input_Z())
	{
		next = new Play(++_parent->stageNum);
	}

	return next;
}

void Clear::draw() const
{
	DrawFormatString(250, 220, MyData::WHITE, "Ç≠ÇËÇ†Å[ÅI");
}






}
}

