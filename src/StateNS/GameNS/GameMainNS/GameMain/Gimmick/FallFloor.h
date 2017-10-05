#pragma once

#include "DynamicGimmickChild.h"



namespace StateNS {
namespace GameNS {


namespace GameMainNS{

class Child;

class FallFloor : public DynamicGimmickChild
{
public:
	FallFloor(int start_x, int start_y,bool ways);
	~FallFloor();
	void initialize();
	void update(const StageChild*);
	void draw(const Vector2* camera) const;
	StageChild::ChipType getChipType() const { return StageChild::ChipType::TYPE_RIGID; };

	void apply(Character*);
	void hittedAction() override;
	void burnedAction() override;
	bool isOverlap(const Vector2*) const;
	bool onActiveArea(const Vector2*) const;


private:
	int mTime;
	int mTime2;

	static bool imgLoad;
	static int image;
	void loadImage();

	bool falldown;//falseÇ≈è„Ç…è„Ç™ÇÈ
	bool nowFall;
	void move(const StageChild*);
	int sy;
};



}
}
}