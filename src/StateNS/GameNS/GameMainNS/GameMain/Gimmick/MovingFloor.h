#pragma once

#include "DynamicGimmickChild.h"



namespace StateNS {
namespace GameNS {


namespace GameMainNS{

class Child;

enum MoveType
{
	LINEAR,			//線形
	UP_PARABOLA,	//上に凸な放物線
	DOWN_PARADOLA,	//下に凸な放物線
	CLOCKWISE,		//時計回り
	ANTI_CLOCKWISE	//逆時計回り
};

class MovingFloor : public DynamicGimmickChild
{
public:
	MovingFloor(int start_x, int start_y, int term_x, int term_y, float movingSpeed,int moveType);
	~MovingFloor();
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
	int mTime = 0;

	//あっちに行って元の場所に戻るまでのフレーム数
	int interval;
	int r;
	float motion_dx;
	float motion_dy;
	int moveType;
	void move();
	void loadImage();
};



}
}
}