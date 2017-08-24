#include "Attack.h"


#include "Collision.h"
#include "Character.h"

namespace StateNS {
namespace GameNS {
namespace GameMainNS{

Attack::Attack(int _x, int _y, int _w, int _h) :
DynamicObject(_x, _y, _w, _h)
{
	isActive = true;
}

Attack::~Attack()
{

}




//==============================================
//内部プライベート関数
//==============================================

//そんなものはない



}
}
}