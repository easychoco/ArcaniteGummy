#pragma once

#include "StateChild.h"
#include "GameNS\GameChild.h"


class Parent;

namespace StateNS{

class Parent : public StateNS::Child
{
public:
	enum NextSequence
	{
		SEQ_TITLE,
		SEQ_MUSICROOM,
		SEQ_CONFIG,
		SEQ_NONE,
	};

	Parent(int stageNum);
	~Parent();
	void initialize();
	StateNS::Child* update(const GrandParent*);
	void draw() const;
	void moveTo(NextSequence);

	int stageNum;

private:
	GameNS::Child* mChild;
	NextSequence mNextSeq;

};




};






