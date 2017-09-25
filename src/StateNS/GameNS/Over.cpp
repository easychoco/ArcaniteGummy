#include "Over.h"
#include "..\StateParent.h"
#include "Play.h"

#include "..\..\Data.h"
#include "..\..\KeyInput.h"


namespace StateNS {
namespace GameNS {


Over::Over()
{

	initialize();
}

Over::~Over()
{

}

void Over::initialize()
{
	this->cursorPos = 0;
	this->prePush = false;
}

Child* Over::update(StateNS::Parent* _parent)
{
	Child* next = this;

	if (!prePush)
	{

		if (Input_UP())
		{
			--cursorPos;
		}
		if (Input_DOWN())
		{
			++cursorPos;
		}
	}

	cursorPos = (cursorPos + 2) % 2;

	if (Input_Z())
	{
		if (cursorPos == 0)next = new Play(_parent->stageNum);
		else if (cursorPos == 1)_parent->moveTo(_parent->NextSequence::SEQ_TITLE);
	}

	prePush = Input_UP() || Input_DOWN();

	return next;
}

void Over::draw() const
{
	DrawFormatString(180, 100, WHITE, "ゲームオーバー");

	DrawFormatString(200, 300, WHITE, "つづける？");

	DrawFormatString(220, 350, GLAY, "はい");
	DrawFormatString(220, 380, GLAY, "いいえ");

	if (cursorPos == 0)	DrawFormatString(220, 350, WHITE, "はい");
	if (cursorPos == 1)	DrawFormatString(220, 380, WHITE, "いいえ");

	//for Debug
	DrawFormatString(0, 0, WHITE, "%d", cursorPos);
}






}
}

