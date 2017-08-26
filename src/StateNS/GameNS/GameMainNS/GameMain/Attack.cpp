#include "Attack.h"


#include "Collision.h"
#include "Character.h"

namespace StateNS {
namespace GameNS {
namespace GameMainNS{

Attack::Attack(int _x, int _y, int _w, int _h) :
DynamicObject(_x / MyData::vectorRate, _y / MyData::vectorRate, _w, _h)
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
	//画面内にいなければreturn
	if (abs(p->raw_x - _camera->raw_x) > 350000 || abs(p->raw_y - _camera->raw_y) > 270000)return;


	//int draw_x = 320 + (p->pos_x() - _camera->pos_x()) / MyData::vectorRate;
	//int draw_y = 240 + (p->pos_y() - _camera->pos_y()) / MyData::vectorRate;
	int draw_x = 320 + (p->x() - _camera->x());
	int draw_y = 240 + (p->y() - _camera->y());

	//描画
	DrawRotaGraph(draw_x, draw_y, 1.0, 0.0, mImage, true, mDirection);
	DrawFormatString(0, 110, MyData::BLACK, "attack : %d %d", draw_x, draw_y);
}

void Attack::checkActive(const Vector2* _camera)
{
	if (abs(p->raw_x - _camera->raw_x) > 350000 || abs(p->raw_y - _camera->raw_y) > 270000)isActive = false;
}

//==============================================
//内部プライベート関数
//==============================================

//そんなものはない



}
}
}