#include "Attack.h"


#include "Collision.h"
//#include "Player\PlayerChild.h"
#include "Character.h"

namespace StateNS {
namespace GameNS {
namespace GameMainNS{

Attack::Attack(const Character* _parent, int x, int y, int w, int h) :
Attack(_parent, x, y, w, h, ObjectID::ID_NONE)
{

}

Attack::Attack(const Character* _parent, int _x, int _y, int _w, int _h, ObjectID _id) :
DynamicObject(_x / MyData::vectorRate, _y / MyData::vectorRate, _w, _h, 0, 0),
parent(_parent),
id(_id)
{
	isActive = true;
	assert(mImage != -1 && "Attack画像読み込みエラー");
}

Attack::~Attack()
{
	DeleteGraph(mImage);
}

void Attack::draw(const Vector2* _camera) const
{
	standardDraw(_camera, p, mImage, mDirection);

	//for Debug
	int draw_x = 320 + (p->x() - _camera->x());
	int draw_y = 240 + (p->y() - _camera->y());
	DrawFormatString(0, 110, MyData::BLACK, "attack : %d %d", draw_x, draw_y);
}

void Attack::checkActive(const Vector2* _camera)
{
	if (abs(p->raw_x - _camera->raw_x) > 480000 || abs(p->raw_y - _camera->raw_y) > 320000)isActive = false;
}

//==============================================
//内部プライベート関数
//==============================================

//そんなものはない



}
}
}