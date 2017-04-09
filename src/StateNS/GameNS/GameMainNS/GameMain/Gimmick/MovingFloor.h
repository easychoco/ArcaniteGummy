#pragma once

#include "GimmickChild.h"



namespace StateNS {
namespace GameNS {


namespace GameMainNS{

class Child;

class MovingFloor : public GimmickChild
{
public:
	MovingFloor();
	~MovingFloor();
	void initialize();
	void update();
	void draw() const;

private:
};




}
}
}