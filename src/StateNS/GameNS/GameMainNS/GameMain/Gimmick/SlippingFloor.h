#pragma once

#include "GimmickChild.h"



namespace StateNS {
namespace GameNS {


namespace GameMainNS{

class Child;

class SlippingFloor : public GimmickChild
{
public:
	SlippingFloor();
	~SlippingFloor();
	void initialize();
	void update();
	void draw() const;

private:
};




}
}
}