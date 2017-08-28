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
	void update(PlayerChild*);
	void draw() const;
	bool isHit(const Vector2&) const;
	Stage::ChipType getChipType() const;

private:
};




}
}
}