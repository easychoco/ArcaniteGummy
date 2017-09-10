#include "Play.h"
#include "Clear.h"
#include "GameMainNS\GameMain.h"
#include "GameMainNS\GameMainChild.h"

#include "..\StateParent.h"

#include "..\..\Data.h"
#include "..\..\KeyInput.h"
#include <fstream>


namespace StateNS {
namespace GameNS {

Play::Play()
{
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
//	for (int i = 0; i < 15; i++) {
	for (int i = 0; i < 2; i++) {
		fin >> a >> b >> x >> y;
		stageMapID[i] = a * 10 + b;
		stageMapXNum[i] = x;
		stageMapYNum[i] = y;
	}


	gameMain = new GameMainNS::GameMain(stageMapID[1],stageMapXNum[1],stageMapYNum[1]);
	mNextSeq = NextSequence::SEQ_NONE;
}

Child* Play::update(Parent* _parent)
{
	Child* next = this;
	gameMain = gameMain->update(this);

	if (Input_X())
	{
		SAFE_DELETE(gameMain);
	}

	if (mNextSeq != SEQ_NONE)
	{
		switch (mNextSeq)
		{
		case SEQ_TITLE: _parent->moveTo(_parent->NextSequence::SEQ_TITLE);
		case SEQ_CLEAR: next = new Clear();
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