#pragma once

#include "..\..\..\..\..\Data.h"
#include "..\DynamicObject.h"
#include "..\Stage.h"

namespace StateNS {
namespace GameNS {
namespace GameMainNS{

class PlayerChild;
class Character;

class DynamicGimmickChild : public DynamicObject
{
public:
	DynamicGimmickChild(int x, int y, int w, int h) : DynamicObject(x, y, w, h, 0, 0) {};
	virtual ~DynamicGimmickChild() {};
	virtual void update(PlayerChild*) = 0;
	virtual void draw(const Vector2* camera) const = 0;
	virtual void apply(Character*) = 0;
	virtual void hittedAction() override = 0;

	//画面上で重なっているか，当たり判定用
	//引数はマップ換算の値
	virtual bool isOverlap(int sub_x, int sub_y) const = 0;

	//対象がギミックの効果範囲内にいるか
	//引数はマップ換算の値
	virtual bool onActiveArea(const Vector2*) const = 0;

	virtual Stage::ChipType getChipType() const = 0;

	//画面上に表示して、更新するかどうかのpublic変数
	bool isActive;

protected:
	int mImage;
	bool mDirection;

	virtual void loadImage() = 0;
};




}
}
}