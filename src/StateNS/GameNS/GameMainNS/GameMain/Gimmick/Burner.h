#pragma once

#include "DynamicGimmickChild.h"



namespace StateNS {
namespace GameNS {


namespace GameMainNS {

class Child;

class Burner : public DynamicGimmickChild
{
public:
	Burner(int x, int y,float angle,bool order);
	~Burner();
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
	int img_block;
	int img_bar;
	float angle;//radian
	bool order;//タイミングをずらすため
	int mTime;
	const int damageValue = 50;
	bool isEmerge;

	const int r_1 =  64 * vectorRate;
	const int r_2 =  96 * vectorRate;
	const int r_3 = 128 * vectorRate;

	int x_1, y_1;
	int x_2, y_2;
	int x_3, y_3;

	void loadImage();
	void move();
};




}
}
}
