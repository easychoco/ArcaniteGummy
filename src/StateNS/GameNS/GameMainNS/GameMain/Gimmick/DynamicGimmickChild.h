#pragma once

#include "..\..\..\..\..\Data.h"
#include "..\DynamicObject.h"
#include "..\Stages\StageChild.h"

namespace StateNS {
namespace GameNS {
namespace GameMainNS{

class PlayerChild;
class Character;

class DynamicGimmickChild : public DynamicObject
{
public:
	DynamicGimmickChild(int x, int y, double scale);
	DynamicGimmickChild(int x, int y, double scale, bool isDeletable);
	virtual ~DynamicGimmickChild();
	virtual void update(const StageChild*) = 0;
	virtual void draw(const Vector2* camera) const = 0;
	virtual void draw_front(const Vector2* camera) const {}
	virtual void apply(Character*) = 0;
	virtual void hittedAction() override = 0;
	virtual void burnedAction() = 0;

	//画面上で重なっているか，当たり判定用
	//引数はマップ換算の値
	virtual bool isOverlap(const Vector2* player) const = 0;

	//対象がギミックの効果範囲内にいるか
	//引数はマップ換算の値
	virtual bool onActiveArea(const Vector2*) const = 0;

	virtual StageChild::ChipType getChipType() const = 0;

	//自分の上端の座標を返す
	int getTopPosition() const { return p->raw_y - height * vectorRate / 2; }
	int getBottomPosition() const { return p->raw_y + height * vectorRate / 2 - vectorRate; }

	//画面上に表示して、更新するかどうかのpublic変数
	bool isActive = true;

	const bool isDeletable;

	//ギミックの上に乗っているかどうかの判定
	bool rideOnGimmick(const Vector2*) const;

	float getDX() const { return dx / (float)vectorRate; }
	float getDY() const { return dy / (float)vectorRate; }

protected:
	int dx;
	int dy;
	int mImage;
	bool mDirection;
	double scale;



	virtual void loadImage() = 0;

	void standardMove(const StageChild*);
	bool standardOverLap(const Vector2*) const;
	int getTopDiffer(const StageChild*, const int dy, bool moveLeft) const;
	int getBottomDiffer(const StageChild*, const int dy, bool moveLeft) const;
	int getHorizontalDiffer(const StageChild*, const int dx, bool moveUp) const;

};




}
}
}