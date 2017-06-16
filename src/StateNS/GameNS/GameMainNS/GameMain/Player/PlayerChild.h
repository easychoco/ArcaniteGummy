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
	PlayerChild(float maxMoveSpeed , float maxJumpPower);
	virtual ~PlayerChild() { SAFE_DELETE(p); };
	virtual PlayerChild* update(const Stage*) = 0;
	virtual void draw() const = 0;
	const Vector2* getVector2() const { return p; }

protected:
	//チップのサイズ
	const int width = 32;
	const int height = 64;

	//キャラごとに移動速度などに違いを出すならここの変数をいじくる
	const float maxMoveSpeed;
	const float maxJumpPower;

	//他の変数
	Vector2* p; //staticではないからキャラ変更のたびにdeleteしよう
	float moveSpeed;
	float jumpPower;
	bool now_jumping;

	//共通の行動
	virtual void attack() = 0;

	void standardMove(const Stage*);
	void move(const Stage*);

	void avoidSinking(const Stage*);
	int jump();
	int gravity();

	//各状態
	enum ActionState
	{
		ACT_NORMAL, //通常状態
		ACT_AIR, //空中にいる
		ACT_ATTACK, //攻撃
		ACT_SIT, //しゃがみ
	};

};






}
}
}