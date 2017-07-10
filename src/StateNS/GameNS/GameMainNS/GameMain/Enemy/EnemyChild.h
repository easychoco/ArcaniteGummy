#pragma once

#include "..\..\..\..\..\Data.h"
#include "..\Character.h"

namespace StateNS {
namespace GameNS {
namespace GameMainNS{

class EnemyChild
{
public:
	virtual ~EnemyChild() {};
	virtual void update() = 0;
	virtual void draw() = 0;

	//Ç±ÇÃ2Ç¬ÇÕÇ¢ÇÁÇ»Ç¢Ç©Ç‡ÇµÇÍÇ»Ç¢
	virtual void move() = 0;
	virtual void attack() = 0;

	//CharacterÇÃä÷êî
	virtual void damagedAction() = 0;

protected:
	Vector2* point;
};



}
}
}