#pragma once

#include "..\..\..\..\Data.h"

namespace StateNS {
namespace GameNS {
namespace GameMainNS{

class EnemyChild
{
public:
	virtual ~EnemyChild() {};
	virtual void update() = 0;
	virtual void draw() = 0;

	//‚±‚Ì2‚Â‚Í‚¢‚ç‚È‚¢‚©‚à‚µ‚ê‚È‚¢
	virtual void move() = 0;
	virtual void attack() = 0;

protected:
	Vector2* point;
};



}
}
}