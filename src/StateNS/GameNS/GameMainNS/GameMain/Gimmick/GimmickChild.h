#pragma once

#include "..\..\..\..\..\Data.h"
#include "..\Stages\StageChild.h"

namespace StateNS {
namespace GameNS {
namespace GameMainNS{

class PlayerChild;
class Character;

class GimmickChild
{
public:
	GimmickChild(Vector2);
	virtual ~GimmickChild() {};
	virtual void update() = 0;
	virtual void draw(const Vector2*) const = 0;
	virtual void draw_front(const Vector2*) const {}
	virtual void apply(Character*) = 0;

	//画面上で重なっているか，当たり判定用
	//引数はマップ換算の値
	//virtual bool isOverlap(int sub_x, int sub_y) const = 0;
	bool isOverlap(const Vector2*) const;

	//対象がギミックの効果範囲内にいるか
	//引数はマップ換算の値
	virtual bool onActiveArea(const Vector2*) const = 0;

	virtual StageChild::ChipType getChipType() const = 0;


	//画面状に表示して、更新するかどうかのpublic変数
	bool isActive;

	//時が止まっているときでも有効かどうか
	bool activeWhenStopping;

protected:
	Vector2 pos;
	int mImage;
	bool mDirection;
	
	void standardDraw(const Vector2* _camera) const;
	virtual void loadImage() = 0;
};




}
}
}