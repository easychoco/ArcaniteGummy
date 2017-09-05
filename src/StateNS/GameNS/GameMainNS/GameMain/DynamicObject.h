#pragma once

#include "..\..\..\..\Data.h"


namespace StateNS {
namespace GameNS {

namespace GameMainNS{

class Collision;

class DynamicObject
{
public:
	DynamicObject(int x, int y, int w, int h, float jump, int jumpCount);
	virtual ~DynamicObject();
	virtual void hittedAction() = 0;
	const Vector2* getVector2() const { return p; }
	bool isHit(const DynamicObject*) const;

	Vector2* p;
	Collision* collision;

	void setJumpPower(float _x) { jumpPower = _x; }

	//for Debug
	int getColliX() const;
	int getColliY() const;

protected:
	//自機だけでなく敵もジャンプさせるのでここに書く
	const float maxJumpPower;
	const int maxJumpCount;
	float jumpPower;
	int nowJumpCount;

	int jump();
	int gravity();

	//cameraを中心とした描画
	void standardDraw(const Vector2* camera, const Vector2* pos, const int& image, const bool& direction) const;
	//拡大率指定版
	void standardDraw(const Vector2* camera, const Vector2* pos, const double& scale_x, const double& scale_y, const int& image, const bool& direction) const;
};




}
}
}