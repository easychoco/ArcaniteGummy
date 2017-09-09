#pragma once

#include "GimmickChild.h"

namespace StateNS {
namespace GameNS {
namespace GameMainNS{

GimmickChild::GimmickChild(Vector2 _pos)
{
	pos = _pos;
	isActive = true;
}

void GimmickChild::standardDraw(const Vector2* _camera) const
{
	if (!isActive)return;

	//‰æ–Ê“à‚É‚¢‚È‚¯‚ê‚Îreturn
	if (abs(pos.pos_x() - _camera->pos_x()) > 480000 || abs(pos.pos_y() - _camera->pos_y()) > 320000)return;

	int draw_x = 320 + pos.x() - _camera->x();
	int draw_y = 240 + pos.y() - _camera->y();

	//•`‰æ
	DrawRotaGraph(draw_x, draw_y, 1.0, 0.0, mImage, true, mDirection);

	//for Debug
	DrawFormatString(0, 90, BLACK, "C: %d %d", draw_x, draw_y);
}




}
}
}