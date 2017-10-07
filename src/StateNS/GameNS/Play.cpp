#include "Play.h"
#include "Clear.h"
#include "Over.h"
#include "GameMainNS\GameMain.h"
#include "GameMainNS\GameMainChild.h"

#include "..\StateParent.h"

#include "..\..\Data.h"
#include "..\..\KeyInput.h"
#include <fstream>


namespace StateNS {
namespace GameNS {

Play::Play(int _stageNum)
{
	this->stageNum = _stageNum;

	initialize();
}

Play::~Play()
{
	SAFE_DELETE(gameMain);
}

void Play::initialize()
{
	gameMain = new GameMainNS::GameMain(this->stageNum);

	mNextSeq = NextSequence::SEQ_NONE;
}

Child* Play::update(Parent* _parent)
{
	Child* next = this;
	gameMain = gameMain->update(this);
	if (gameMain->reset())
	{
		SAFE_DELETE(gameMain);
		gameMain = new GameMainNS::GameMain(this->stageNum);
	}

	/*
	//for Debug
	if (Input_X())
	{
		SAFE_DELETE(gameMain);
		next = new Clear();
	}
	*/

	if (mNextSeq != SEQ_NONE)
	{
		switch (mNextSeq)
		{
		case SEQ_TITLE: _parent->moveTo(_parent->NextSequence::SEQ_TITLE); break;
		case SEQ_CLEAR: next = new Clear(); break;
		case SEQ_OVER: next = new Over(); break;
			/*
			TODO ‘¼‚Ì‘JˆÚ‚à‘‚­
			*/
		}
	}
	mNextSeq = SEQ_NONE;

	return next;
}

void Play::draw() const
{
	gameMain->draw();
}

void Play::moveTo(NextSequence _next)
{
	mNextSeq = _next;
}




}
}