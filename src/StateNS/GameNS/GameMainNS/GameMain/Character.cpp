#include "Character.h"
#include "Collision.h"

namespace StateNS {
namespace GameNS {
namespace GameMainNS{

Character::Character(int hp, int x, int y, int w, int h, float jump, int jumpCount):
Character(hp, x, y, w, h, false, jump, jumpCount, false)
{ }

Character::Character(int _hp, int _x, int _y, int _w, int _h, bool _isPlayer, float _jump,int _jumpCount, bool _hasChild) : 
DynamicObject(_x, _y, _w, _h, _jump, _jumpCount, _hasChild),
hpController(HPController(this, PLAYER_MAX_HP, _hp))
{
	width = _w;
	height = _h;
	next_dx = next_dy = 0;

	isPlayer = _isPlayer;
	damaged = false;
	damagedTime = 0;
}

Character::~Character()
{

}

//ƒLƒƒƒ‰‚ðdx, dy‚¾‚¯ˆÚ“®‚³‚¹‚é
void Character::moveCharacter(float _dx, float _dy)
{
	this->next_dx += (int)(_dx * vectorRate);
	this->next_dy += (int)(_dy * vectorRate);
}

//ƒLƒƒƒ‰‚ðx, y‚ÌˆÊ’u‚ÉˆÚ“®‚³‚¹‚é
void Character::warpCharacter(int _x, int _y)
{
	p->raw_x = _x;
	p->raw_y = _y;
}




}
}
}