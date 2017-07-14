#pragma once

#include "..\..\..\..\..\Data.h"


namespace StateNS {
namespace GameNS {
namespace GameMainNS{

class PlayerChild;

class GimmickChild
{
public:
	virtual ~GimmickChild() {};
	virtual void update(PlayerChild*) = 0;
	virtual void draw() const = 0;

	//画面状に表示して、更新するかどうかのpublic変数
	bool isActive;
};




}
}
}