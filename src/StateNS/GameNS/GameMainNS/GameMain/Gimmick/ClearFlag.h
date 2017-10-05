#pragma once

#include "GimmickChild.h"



namespace StateNS {
namespace GameNS {


namespace GameMainNS{


class ClearFlag : public GimmickChild
{
public:
	ClearFlag(Vector2);
	~ClearFlag();
	void initialize();
	void update();
	void draw(const Vector2*) const;
	void apply(Character*);
	bool isOverlap(int, int) const;
	bool onActiveArea(const Vector2*) const;
	StageChild::ChipType getChipType() const;

//	void setMovingSpeed(float _dx) { dx = _dx; }

private:
	static bool imgLoad;
	static int image;
	void loadImage();
};




}
}
}
