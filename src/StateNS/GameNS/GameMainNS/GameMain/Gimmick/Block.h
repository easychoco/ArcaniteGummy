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
	~Block();
	void initialize();
	void update(const Stage*);
	void draw(const Vector2* camera) const;
	Stage::ChipType getChipType() const { return Stage::ChipType::TYPE_RIGID; };

	void apply(Character*);
	void hittedAction() override;
	void burnedAction() override;
	bool isOverlap(const Vector2*) const;
	bool onActiveArea(const Vector2*) const;


private:
	int dy;
	int width;
	int height;

	void loadImage();
};




}
}
}