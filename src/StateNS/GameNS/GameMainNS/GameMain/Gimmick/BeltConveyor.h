#pragma once

#include "GimmickChild.h"



namespace StateNS {
namespace GameNS {
namespace GameMainNS{


class BeltConveyor : public GimmickChild
{
public:

	enum BeltPos
	{
		POS_LEFT,
		POS_CENTER,
		POS_RIGHT,
	};

	BeltConveyor(float, Vector2);
	~BeltConveyor();
	void initialize();
	void update();
	void draw(const Vector2*) const;
	void apply(Character*);
	//bool isOverlap(int, int) const;
	bool onActiveArea(const Vector2*) const;
	StageChild::ChipType getChipType() const;

	void setMovingSpeed(float _dx) { dx = _dx; }



private:
	float dx;
	int mTime;
	bool direction;

	static bool imgLoad;
	static int images[3];
	void loadImage();
};




}
}
}
