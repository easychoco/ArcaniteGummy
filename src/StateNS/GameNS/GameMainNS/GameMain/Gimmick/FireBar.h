#pragma once

#include "DynamicGimmickChild.h"



namespace StateNS {
namespace GameNS {


namespace GameMainNS {

class Child;

class FireBar : public DynamicGimmickChild
{
public:
	FireBar(int x, int y,bool ways);
	~FireBar();
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
	int img_block;
	int img_bar;
	float radian;
	bool ways;//ŽžŒv‰ñ‚è‚È‚çtrue
	const int damageValue = 50;

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
