#pragma once

#include "DynamicGimmickChild.h"



namespace StateNS {
namespace GameNS {
namespace GameMainNS {

//class Child;

class FireBar : public DynamicGimmickChild
{
public:
	FireBar(int x, int y,bool ways);
	~FireBar();
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
	static bool imgLoad;
	static int img_block;
	static int img_bar;
	void loadImage();

	float radian;
	bool ways;//ŽžŒv‰ñ‚è‚È‚çtrue
	const int damageValue = 30;

	const int r_1 =  64 * vectorRate;
	const int r_2 =  96 * vectorRate;
	const int r_3 = 128 * vectorRate;

	int x_1, y_1;
	int x_2, y_2;
	int x_3, y_3;

	void move();

};




}
}
}
