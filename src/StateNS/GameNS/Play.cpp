#include "Play.h"
#include "Clear.h"
#include "GameMainNS\GameMain.h"
#include "GameMainNS\GameMainChild.h"


#include "..\..\Data.h"
#include "..\..\KeyInput.h"



namespace StateNS {
namespace GameNS {

Play::Play()
{
	initialize();
}

Play::~Play()
{

}

void Play::initialize()
{
	gameMain = new GameMainNS::GameMain();
}

Child* Play::update(Parent* parent)
{
	Child* next = this;
	gameMain = gameMain->update(this);

	if (Input_X())
	{
		SAFE_DELETE(gameMain);
		next = new Clear();
	}

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