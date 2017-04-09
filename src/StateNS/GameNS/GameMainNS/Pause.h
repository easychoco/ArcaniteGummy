#pragma once

#include "GameMainChild.h"

namespace StateNS {

class Parent;

namespace GameNS {

namespace GameMainNS{


class Pause : public Child
{
public:
	Pause();
	~Pause();
	void initialize();
	Child* update(GameParent*);
	void draw() const;

};



}
}
}