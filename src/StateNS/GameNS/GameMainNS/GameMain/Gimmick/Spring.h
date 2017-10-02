#pragma once

#include "GimmickChild.h"



namespace StateNS {
namespace GameNS {


namespace GameMainNS{

class Child;

class Spring : public GimmickChild
{
public:
	Spring(Vector2);
	~Spring();
	void initialize();
	void update();
	void draw(const Vector2*) const;
	void apply(Character*);
	bool isOverlap(int, int) const;
	bool onActiveArea(const Vector2*) const;
	StageChild::ChipType getChipType() const;

//	void setMovingSpeed(float _dx) { dx = _dx; }

private:
	int images[2];
	float dy;
	int mTime;
	int aTime;
	bool onPlayer;

	void loadImage();
};




}
}
}
