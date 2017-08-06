#pragma once

#include "GimmickChild.h"



namespace StateNS {
namespace GameNS {


namespace GameMainNS{

class Child;

class BeltConveyor : public GimmickChild
{
public:
	BeltConveyor(int, Vector2);
	~BeltConveyor();
	void initialize();
	void update();
	void draw(const Vector2*) const;
	void apply(Character*);
	bool isOverlap(const Vector2*) const;
	bool onActiveArea(const Vector2*) const;
	Stage::ChipType getChipType() const;

	void setMovingParam(int _dx) { dx = _dx; }

private:
	int dx;
	Vector2 pos;
	int mImage;
	int mTime;
};




}
}
}
