#pragma once

#include "DynamicGimmickChild.h"



namespace StateNS {
namespace GameNS {


namespace GameMainNS{

class Child;

class Block : public DynamicGimmickChild
{
public:
	Block(int x, int y, double scale);
	Block(int x, int y, double scale, bool isBreakable);
	~Block();
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
	int width;
	int height;
	const bool isBreakable;

	static bool imgLoad;
	static int image;
	void loadImage();
};




}
}
}