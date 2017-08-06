#pragma once

#include "GimmickChild.h"



namespace StateNS {
namespace GameNS {


namespace GameMainNS{

class Child;

class Dossunn : public GimmickChild
{
public:
	Dossunn();
	~Dossunn();
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