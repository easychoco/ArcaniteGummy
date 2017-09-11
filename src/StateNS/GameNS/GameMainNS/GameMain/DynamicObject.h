#pragma once

#include "..\..\..\..\Data.h"


namespace StateNS {
namespace GameNS {

namespace GameMainNS{

class Collision;
class Stage;

class DynamicObject
{
public:
	DynamicObject(int x, int y, int w, int h, float jump, int jumpCount);
	virtual ~DynamicObject();
	virtual void hittedAction() = 0;
	const Vector2* getVector2() const { return p; }
	bool isHit(const DynamicObject*) const;

	Collision* collision;

	void setJumpPower(float _x) { jumpPower = _x; }

	//for Debug
	int getColliX() const;
	int getColliY() const;

protected:
	Vector2* p;

	//自機だけでなく敵もジャンプさせるのでここに書く
	const float maxJumpPower;
	const int maxJumpCount;
	float jumpPower;
	int nowJumpCount;
	int width;
	int height;

	int jump();
	int gravity();

	int getTopDiffer(const Stage*, const int dy, bool isPlayer) const;
	int getBottomDiffer(const Stage*, const int dy, bool isPlayer) const;
	int getHorizontalDiffer(const Stage*, const int dx, bool isPlayer) const;

	//cameraを中心とした描画
	void standardDraw(const Vector2* camera, const Vector2* pos, const int& image, const bool& direction) const;
	//拡大率指定版
	void standardDraw(const Vector2* camera, const Vector2* pos, const double& scale, const int& image, const bool& direction) const;
};




}
}
}