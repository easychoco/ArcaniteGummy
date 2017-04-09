#pragma once

#include "..\..\..\..\..\Data.h"


namespace StateNS {
namespace GameNS {

namespace GameMainNS{


class GimmickChild
{
public:
	virtual ~GimmickChild() {};
	virtual void update() = 0;
	virtual void draw() const = 0;
};




}
}
}