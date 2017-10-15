#pragma once

#include "GimmickChild.h"



namespace StateNS {
namespace GameNS {


namespace GameMainNS{

class Child;

class CheckPoint : public GimmickChild
{
public:
	CheckPoint(int x, int y, int stage_num);
	~CheckPoint();
	void initialize();
	void update();
	void draw(const Vector2* camera) const;
	StageChild::ChipType getChipType() const { return StageChild::ChipType::TYPE_BACK; };
	void apply(Character*);
	virtual bool onActiveArea(const Vector2*) const override;

	const int getStageNum() const { return stage_num; }
	const int getX() const { return pos.x(); }
	const int getY() const { return pos.y(); }

	bool visitCheckPoint() { return visited; }

private:
	int time;
	static bool imgLoad;
	static int image;
	void loadImage();

	const int stage_num;
	bool visited;
};




}
}
}