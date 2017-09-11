#pragma once

#include "DynamicGimmickChild.h"



namespace StateNS {
namespace GameNS {


namespace GameMainNS{

class Child;

class MovingFloor : public DynamicGimmickChild
{
public:
	MovingFloor(int start_x, int start_y, int term_x, int term_y, float movingSpeed);
	~MovingFloor();
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
	int mTime = 0;

	//‚ ‚Á‚¿‚És‚Á‚ÄŒ³‚ÌêŠ‚É–ß‚é‚Ü‚Å‚ÌƒtƒŒ[ƒ€”
	int interval;
	
	float motion_dx;
	float motion_dy;

	void loadImage();
};



}
}
}