#pragma once

#include "DynamicGimmickChild.h"



namespace StateNS {
namespace GameNS {


namespace GameMainNS{

class Child;

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

	//‚ ‚Á‚¿‚És‚Á‚ÄŒ³‚ÌêŠ‚É–ß‚é‚Ü‚Å‚ÌƒtƒŒ[ƒ€”
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