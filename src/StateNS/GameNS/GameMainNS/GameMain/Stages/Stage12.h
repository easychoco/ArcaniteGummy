#pragma once
#include "..\..\..\..\..\Data.h"
#include "StageChild.h"

namespace StateNS {
namespace GameNS {
namespace GameMainNS{


class Stage12 : public StageChild
{
public:
	Stage12();
	~Stage12();
	void update(GameMain*, PlayerChild*);
	void draw(const Vector2* player) const;
	bool isClear() const;
	
private:
	void initialize();
	bool converseFlag0,converseFlag0fin;
	void updateConverse(GameMain*, PlayerChild*);
	int imageReisen;

};




}
}
}