#pragma once

#include "..\..\..\..\..\Data.h"
#include "..\Character.h"

namespace StateNS {
namespace GameNS {
namespace GameMainNS{

class EnemyChild : public Character
{
public:
	EnemyChild(int _hp) : Character(_hp) { this->time = 0; }
	virtual ~EnemyChild() { SAFE_DELETE(point); };
	virtual void update() = 0;
	virtual void draw(const Vector2* player) const = 0;

	//Character‚ÌŠÖ”
	//virtual void damagedAction() = 0;

protected:
	Vector2* point;
	int time;
};



}
}
}