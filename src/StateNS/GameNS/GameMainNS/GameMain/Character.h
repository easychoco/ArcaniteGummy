#pragma once

#include "..\..\..\..\Data.h"

#include "DynamicObject.h"
#include "HPController.h"
#include "Stages\StageChild.h"


namespace StateNS {
namespace GameNS {
namespace GameMainNS{

//自機と敵で共通する行動
class Character : public DynamicObject
{
public:
	Character(int hp, int x, int y, int w, int h, float jump, int jumpCount);
	Character(int hp, int x, int y, int w, int h, bool isPlayer, float jump, int jumpCount, bool hasChild);
	virtual ~Character();
	virtual void hittedAction() = 0;
	void moveCharacter(float _dx, float _dy);
	void warpCharacter(int raw_x, int raw_y);
	virtual int getFloorCoordinate() { return 0; }

	HPController hpController;
	bool isPlayer;
	bool damaged;
	int damagedTime;

protected:
	int next_dx;
	int next_dy;
	int width;
	int height;

	virtual int getTopDiffer(const StageChild*, const int dy, bool moveLeft) const = 0;
	virtual int getBottomDiffer(const StageChild*, const int dy, bool moveLeft) const = 0;
	virtual int getHorizontalDiffer(const StageChild*, const int dx, bool moveUp) const = 0;
};



}
}
}