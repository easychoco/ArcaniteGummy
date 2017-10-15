#pragma once
#include "..\..\..\..\..\Data.h"
#include "StageChild.h"

namespace StateNS {
namespace GameNS {
namespace GameMainNS{


class Stage32 : public StageChild
{
public:
	Stage32();
	~Stage32();
	void update(GameMain*, PlayerChild*);
	void draw(const Vector2* player) const;
	bool isClear() const;
	
private:
	void initialize();

};




}
}
}