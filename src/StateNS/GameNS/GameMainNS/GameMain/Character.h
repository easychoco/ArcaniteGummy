#pragma once

#include "..\..\..\..\Data.h"

#include "DynamicObject.h"
#include "HPController.h"
#include "Stage.h"


namespace StateNS {
namespace GameNS {
namespace GameMainNS{

//自機と敵で共通する行動
class Character : public DynamicObject
{
public:
	Character(int hp, int x, int y, int w, int h,float jump,int jumpCount);
	virtual ~Character();
	virtual void hittedAction() = 0;
	void moveCharacter(float _dx, float _dy);
	void warpCharacter(float _x, float _y);

	HPController hpController;
	bool damaged;
	int damagedTime;

protected:
	int next_dx;
	int next_dy;
	int width;
	int height;

	int getTopDiffer(const Stage*, const int dy) const;
	int getBottomDiffer(const Stage*, const int dy) const;
	int getHorizontalDiffer(const Stage*, const int dx) const;
};



}
}
}