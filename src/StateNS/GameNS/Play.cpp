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
	std::ifstream fin("Data/Text/stagelist.txt");
	int a, b, x, y;
	for (int i = 0; i < 3; i++) {
		fin >> a >> b >> x >> y;
		stageMapID[i] = a * 10 + b;
		stageMapXNum[i] = x;
		stageMapYNum[i] = y;
	}

//	int stage_index = (stageNum / 10 - 1) * 3 + stageNum % 10 - 1;
	int stage_index = 0;
	gameMain = new GameMainNS::GameMain(stageMapID[stage_index], stageMapXNum[stage_index], stageMapYNum[stage_index]);

	mNextSeq = NextSequence::SEQ_NONE;
}

Child* Play::update(Parent* _parent)
{
	Child* next = this;
	gameMain = gameMain->update(this);

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