#pragma once

#include "GimmickChild.h"



namespace StateNS {
namespace GameNS {


namespace GameMainNS{

class Child;

class MovingFloor : public GimmickChild
{
public:
	MovingFloor(Vector2);
	~MovingFloor();
	void initialize();
	void update(PlayerChild*);
	void draw(const Vector2*) const;
	bool isHit(const Vector2*) const;
	Stage::ChipType getChipType() const;

private:
	void loadImage();
};




}
}
}