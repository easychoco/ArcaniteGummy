#pragma once

#include "GimmickChild.h"



namespace StateNS {
namespace GameNS {
namespace GameMainNS {

class Guide : public GimmickChild
{
public:
	Guide(int x, int y, vector<string>);
	~Guide();
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

	vector<string> messages;
	bool playerLooking;

	int frameHeight;
	int frameWidth;
};




}
}
}
