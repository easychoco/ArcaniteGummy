#pragma once

#include "DynamicGimmickChild.h"



namespace StateNS {
namespace GameNS {


namespace GameMainNS {

class Child;

class Dossunn : public DynamicGimmickChild
{
public:
	Dossunn(int x, int y, double scale);
	~Dossunn();
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
	int interval;
	const Vector2 originPos;

	static bool imgLoad;
	static int image;
	void loadImage();

	bool isDown;
	bool isMove;
	void move();
};




}
}
}
