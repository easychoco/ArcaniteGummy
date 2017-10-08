#pragma once

#include "GimmickChild.h"



namespace StateNS {
namespace GameNS {
namespace GameMainNS {

class Needle : public GimmickChild
{
public:
	Needle(int x, int y, float angle);
	~Needle();
	void initialize();
	void update();
	void draw(const Vector2* camera) const;
	StageChild::ChipType getChipType() const { return StageChild::ChipType::TYPE_BACK; };

	void apply(Character*);
	virtual bool onActiveArea(const Vector2*) const override;


private:
	int mTime;
	static bool imgLoad;
	static int image;
	void loadImage();

	float angle;//radian
	const int damageValue = 20;

};




}
}
}
