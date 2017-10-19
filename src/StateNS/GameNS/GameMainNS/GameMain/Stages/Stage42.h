#pragma once
#include "..\..\..\..\..\Data.h"
#include "StageChild.h"

namespace StateNS {
namespace GameNS {
namespace GameMainNS{


class Stage42 : public StageChild
{
public:
	Stage42();
	~Stage42();
	void update(GameMain*, PlayerChild*);
	void draw(const Vector2* player) const;
	bool isClear() const;
	
private:
	void initialize();
	void updateConverse(GameMain*, PlayerChild*);
	bool converseFlag0;
	int time;
};




}
}
}