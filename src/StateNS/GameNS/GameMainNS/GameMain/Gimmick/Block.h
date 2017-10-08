#pragma once

#include "DynamicGimmickChild.h"



namespace StateNS {
namespace GameNS {
namespace GameMainNS{

enum BlockType
{
	TYPE_FRAGILE	= 0b0001,
	TYPE_WOOD		= 0b0010,
	TYPE_SWITCH		= 0b0100,
	TYPE_LOCK		= 0b1000,
};

class Block : public DynamicGimmickChild
{
public:
	Block(int x, int y, double scale);
	Block(int x, int y, double scale, BlockType);
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
	const BlockType blockType;

	static bool imgLoad;
	static int image[4];
	void loadImage();
};




}
}
}