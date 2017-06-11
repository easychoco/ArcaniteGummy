#pragma once

#include "..\..\..\..\..\Data.h"
#include "..\..\..\..\..\KeyInput.h"


namespace StateNS {
namespace GameNS {
namespace GameMainNS{

class Stage;

class PlayerChild
{
public:
	PlayerChild();
	virtual ~PlayerChild() { SAFE_DELETE(p); };
	virtual PlayerChild* update(const Stage*) = 0;
	virtual void draw() const = 0;
	const Vector2* getVector2() const { return p; }

protected:
	//キャラごとに移動速度などに違いを出すならここの変数をいじくる
	float moveSpeed;
	float maxJumpPower;

	//他の変数
	Vector2* p; //staticではないからキャラ変更のたびにdeleteしよう
	float jumpPower;


	//共通の行動
	void standardMove(const Stage*);
	int jump();
	int gravity();
};




}
}
}