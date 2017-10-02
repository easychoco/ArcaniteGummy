#include "StateParent.h"
#include "Title.h"
#include "Config.h"
#include "GameNS\Play.h"

#include "..\Data.h"


namespace StateNS{

Parent::Parent()
{
	initialize();
}

Parent::~Parent()
{

}

void Parent::initialize()
{
	//セーブデータ読み込み
	//stageNum更新

	//for Debug
	stageNum = 11;

	this->mChild = new GameNS::Play(stageNum);
	mNextSeq = NextSequence::SEQ_NONE;


}

Child* Parent::update(const GrandParent* parent)
{
	Child* next = this;

	GameNS::Child* nextChild = mChild->update(this);

	//シーケンス遷移
	if (nextChild != mChild)
	{
		SAFE_DELETE(mChild);
		mChild = nextChild;
	}

	nextChild = 0;


	//シーケンス間遷移
	switch (mNextSeq)
	{
	case SEQ_TITLE: next = new Title(); break;
	case SEQ_CONFIG: next = new Config(); break;

	}

	mNextSeq = SEQ_NONE;

	return next;
}

void Parent::draw() const
{
	mChild->draw();
}

void Parent::moveTo(NextSequence _next)
{
	mNextSeq = _next;
}

}