#pragma once

#include "..\DynamicGimmickChild.h"


namespace StateNS {
namespace GameNS {
namespace GameMainNS{

class Child;
class Block;

class SwitchWithBlock : public DynamicGimmickChild
{
public:
	SwitchWithBlock(int x, int y);
	~SwitchWithBlock();
	void initialize();
	void update(const Stage*);
	void draw(const Vector2*) const;
	void apply(Character*);

	void hittedAction() override;
	void burnedAction() override;
	bool isOverlap(const Vector2*) const override;

	bool onActiveArea(const Vector2*) const;
	void checkOnActiveArea(const Vector2* player) { this->onActiveArea(player); }
	Stage::ChipType getChipType() const;

	vector<Block*> blocks;
	vector<Block*> tmp;
	void push_block(Block* b) { blocks.push_back(b); }
	vector<Block*> getBlocks() { return ((isPushed) ? tmp : blocks); }

private:
	bool isPushed;
	bool preOnActiveArea;
	mutable bool tmpOnActiveArea;
	int mTime;

	void loadImage();
};




}
}
}
