#pragma once

#include "GimmickChild.h"



namespace StateNS {
namespace GameNS {
namespace GameMainNS{

class Child;

class Door : public GimmickChild
{
public:
	Door(Vector2*, Vector2*);
	~Door();
	void initialize();
	void update();
	void draw(const Vector2*) const;
	void draw_front(const Vector2*) const override;
	void apply(Character*);
	bool isOverlap(int, int) const;
	bool onActiveArea(const Vector2*) const;
	StageChild::ChipType getChipType() const { return StageChild::ChipType::TYPE_BACK; }

private:
	bool onDoor1;
	bool onDoor2;
	int animeTime;

	Vector2* door1;
	Vector2* door2;

	static bool imgLoad;
	static int image;
	void loadImage();
};




}
}
}
