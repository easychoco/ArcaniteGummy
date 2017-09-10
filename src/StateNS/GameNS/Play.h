#pragma once

#include "GameChild.h"

namespace StateNS {

class Parent;

namespace GameNS {
namespace GameMainNS {
	class Child;
}

//SateNS::GameNS‚Å‚ÌParent‚Ì–ð–Ú
class Play : public Child
{
public:
	enum NextSequence
	{
		SEQ_TITLE,
		//SEQ_PAUSE,
		//SEQ_CONVERSE,
		SEQ_LOAD,
		SEQ_SAVE,
		SEQ_CLEAR,
		SEQ_OVER,

		SEQ_NONE
	};


	Play();
	~Play();
	void initialize();
	Child* update(Parent*);
	void draw() const;
	void moveTo(NextSequence);

private:
	GameMainNS::Child* gameMain;
	NextSequence mNextSeq;
	int stageMapID[15];
	int stageMapXNum[15];
	int stageMapYNum[15];

};




}
}

