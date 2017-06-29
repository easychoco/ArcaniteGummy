#pragma once

#include "GimmickChild.h"



namespace StateNS {
namespace GameNS {


namespace GameMainNS{

class Child;

class Switch : public GimmickChild
{
public:
	Switch();
	~Switch();
	void initialize();
	void update(PlayerChild*);
	void draw() const;

private:
};




}
}
}