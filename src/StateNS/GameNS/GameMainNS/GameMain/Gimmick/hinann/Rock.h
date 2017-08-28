#pragma once

#include "GimmickChild.h"



namespace StateNS {
namespace GameNS {


namespace GameMainNS{

class Child;

class Rock : public GimmickChild
{
public:
	Rock();
	~Rock();
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