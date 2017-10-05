#pragma once

#include "DynamicGimmickChild.h"



namespace StateNS {
namespace GameNS {


namespace GameMainNS {

class Child;

class Burner : public DynamicGimmickChild
{
public:
	Burner(int x, int y, float angle, bool order);
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
	static bool imgLoad;
	static int img_block;
	static int img_bar;
	void loadImage();

	float angle;//radian
	bool order;//タイミングをずらすため
	int mTime;
	const int damageValue = 50;
	bool isEmerge;

	//ブロック部分の長さ(ピクセル)
	const int l_block =  32;
	//バーナー部分の長さ(ピクセル)
	const int l_burn =  112;

	//右、左、上、下の座標
	int r, l, u, d;



	void move();
};




}
}
}
