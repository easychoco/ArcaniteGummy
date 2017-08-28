#pragma once

#include "..\..\..\..\Data.h"
#include "HPController.h"
#include "Stage.h"


namespace StateNS {
namespace GameNS {
namespace GameMainNS{

class Collision;

//é©ã@Ç∆ìGÇ≈ã§í Ç∑ÇÈçsìÆ
class Character
{
public:
	Character(int hp, int x, int y, int w, int h);
	virtual ~Character();
	virtual void damagedAction() = 0;
	const Vector2* getVector2() const { return p; }
	void moveCharacter(float _dx, float _dy);
	bool isHit(const Character*) const;
	HPController hpController;
	Collision* collision;

protected:
	Vector2* p;
	int next_dx;
	int next_dy;
	int width;
	int height;

	int getTopDiffer(const Stage*, const int) const;
	int getBottomDiffer(const Stage*, const int) const;
	int getHorizontalDiffer(const Stage*, const int) const;
};



}
}
}