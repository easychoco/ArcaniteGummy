#pragma once
#include "..\..\..\..\..\Data.h"
#include "StageChild.h"

namespace StateNS {
namespace GameNS {
namespace GameMainNS{


class Stage51 : public StageChild
{
public:
	Stage51();
	~Stage51();
	void update(GameMain*, PlayerChild*);
	void draw(const Vector2* player) const;
	bool isClear() const;
	
private:
	void initialize();
	void updateConverse(GameMain*,PlayerChild*);
	int imageKaguya;
	bool converseFlag0, converseFlag0fin;


};




}
}
}