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
	bool isHit(const Vector2&) const;
	Stage::ChipType getChipType() const;

private:
	Vector2 pos;
	int w, h;

};




}
}
}