#include "Parent.h"
#include "StateNS\Title.h"
#include "StateNS\Config.h"
#include "StateNS\StateParent.h"

#include "Data.h"


Parent::Parent()
{
	mChild = 0;
	initialize();
}

Parent::~Parent()
{
	SAFE_DELETE(mChild);

	sound->deleteSound("ok");
	sound->deleteSound("no");
}

void Parent::initialize()
{
	mChild = new StateNS::Title();

	sound->setSound("Data/Sound/ok.mp3", "ok");
	sound->setSound("Data/Sound/no.mp3", "no");
}

void Parent::update()
{
	Child* next = mChild->update(this);

	//‘JˆÚ
	if (mChild != next)
	{
		SAFE_DELETE(mChild);
		mChild = next;
	}

	next = 0;
}

void Parent::draw() const
{
	mChild->draw();
}

