#pragma once

#include "GameMainChild.h"

namespace StateNS {
namespace GameNS {
namespace GameMainNS {

class Converse : public Child
{
public:
	Converse();
	~Converse();
	void initialize();
	Child* update(GameParent*);
	void draw() const;

};



}
}
}