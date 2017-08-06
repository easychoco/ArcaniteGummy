#pragma once

#include "..\..\..\..\..\Data.h"
#include "..\Stage.h"

namespace StateNS {
namespace GameNS {
namespace GameMainNS{

class PlayerChild;
class Character;

class GimmickChild
{
public:
	virtual ~GimmickChild() {};
	virtual void update() = 0;
	virtual void draw(const Vector2*) const = 0;
	virtual void apply(Character*) = 0;

	//画面上で重なっているか，当たり判定用
	virtual bool isOverlap(const Vector2*) const = 0;

	//対象がギミックの効果範囲内にいるか
	virtual bool onActiveArea(const Vector2*) const = 0;

	virtual Stage::ChipType getChipType() const = 0;

	//画面状に表示して、更新するかどうかのpublic変数
	bool isActive;
};




}
}
}