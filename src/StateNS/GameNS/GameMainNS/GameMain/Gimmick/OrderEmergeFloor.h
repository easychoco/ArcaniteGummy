#pragma once

#include "DynamicGimmickChild.h"



namespace StateNS {
namespace GameNS {


namespace GameMainNS{

class Child;

class OrderEmergeFloor : public DynamicGimmickChild
{
public:
	OrderEmergeFloor(int x, int y, double scale,int order);
	~OrderEmergeFloor();
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
	int dy;
	int mTime;
	int order;//èoåªÇ∑ÇÈèáî‘
	bool isEmerge;

	static bool imgLoad;
	static int image;
	void loadImage();
};




}
}
}