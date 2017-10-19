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
	sound->stopSoundOfFile();
}

void Over::initialize()
{
	this->cursorPos = 0;
	this->prePush = false;
	sound->playSoundWithPath("Data/Sound/Over.mp3", BACK);
	backImg = LoadGraph("Data/Image/gameover.png");
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


	DrawGraph(0, 0, backImg, TRUE);
	if (cursorPos == 0)	DrawBox(220, 270, 420, 330, WHITE, FALSE);
	if (cursorPos == 1)	DrawBox(220, 350, 420, 410, WHITE, FALSE);

}






}
}

