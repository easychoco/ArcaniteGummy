#pragma once

#include "GimmickChild.h"

namespace StateNS {
namespace GameNS {
namespace GameMainNS{

GimmickChild::GimmickChild(Vector2 _pos)
{
	pos = _pos;
	isActive = true;
	assert(_pos.x() % 32 == 16 && _pos.y() % 32 == 16 && "Gimmick‚ÌÀ•W‚ª (32 * n + 16) ‚¶‚á‚È‚¢‚Å‚·");
}

void GimmickChild::standardDraw(const Vector2* _camera) const
{
	if (!isActive)return;

	//‰æ–Ê“à‚É‚¢‚È‚¯‚ê‚Îreturn
	if (abs(pos.raw_x - _camera->raw_x) > 480000 || abs(pos.raw_y - _camera->raw_y) > 320000)return;

	int draw_x = MyData::CX + pos.x() - _camera->x();
	int draw_y = MyData::CY + pos.y() - _camera->y();

	//•`‰æ
	DrawRotaGraph(draw_x, draw_y, 1.0, 0.0, mImage, true, mDirection);
}

bool GimmickChild::isOverlap(const Vector2* _other) const
{
	int half_w = 17000;
	int half_h = 17000;

	return
		this->pos.raw_x - half_w <= _other->raw_x &&
		this->pos.raw_x + half_w >= _other->raw_x &&
		this->pos.raw_y - half_h <= _other->raw_y &&
		this->pos.raw_y + half_h >= _other->raw_y;
}



}
}
}