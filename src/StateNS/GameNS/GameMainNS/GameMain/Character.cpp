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
hpController(HPController(this, _hp))
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

int Character::getTopDiffer(const StageChild* _stage, const int dy, bool _moveLeft) const { return DynamicObject::getTopDiffer(_stage, dy, _moveLeft, true); }
int Character::getBottomDiffer(const StageChild* _stage, const int dy, bool _moveLeft) const { return DynamicObject::getBottomDiffer(_stage, dy, _moveLeft, true); }
int Character::getHorizontalDiffer(const StageChild* _stage, const int dx, bool _moveUp) const { return DynamicObject::getHorizontalDiffer(_stage, dx, _moveUp, true); }



}
}
}