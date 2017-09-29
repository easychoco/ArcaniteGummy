#pragma once

#include "DynamicGimmickChild.h"



namespace StateNS {
namespace GameNS {


namespace GameMainNS {

class Child;

class Needle : public DynamicGimmickChild
{
public:
	Needle(int x, int y, float angle);
	~Needle();
	void initialize();
	void update(const StageChild*);
	void draw(const Vector2* camera) const;
	StageChild::ChipType getChipType() const { return StageChild::ChipType::TYPE_BACK; };

	void apply(Character*);
	void hittedAction() override;
	void burnedAction() override;
	bool isOverlap(const Vector2*) const;
	bool onActiveArea(const Vector2*) const;


private:
	int img;
	float angle;//radian
	int mTime;
	const int damageValue = 10000;

	void loadImage();
	void move();
};




}
}
}
