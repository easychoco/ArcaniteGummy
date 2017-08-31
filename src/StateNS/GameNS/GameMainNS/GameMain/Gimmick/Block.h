#pragma once

#include "DynamicGimmickChild.h"



namespace StateNS {
namespace GameNS {


namespace GameMainNS{

class Child;

class Block : public DynamicGimmickChild
{
public:
	Block(int x, int y, int w, int h);
	~Block();
	void initialize();
	void update(PlayerChild*);
	void draw(const Vector2* camera) const;
	Stage::ChipType getChipType() const { return Stage::ChipType::TYPE_RIDE; };

private:
	void loadImage();
};




}
}
}