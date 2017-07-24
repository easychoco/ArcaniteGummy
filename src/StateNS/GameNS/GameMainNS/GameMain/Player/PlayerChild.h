#pragma once

#include "..\..\..\..\..\Data.h"
#include "..\..\..\..\..\KeyInput.h"
#include "..\Character.h"

namespace StateNS {
namespace GameNS {
namespace GameMainNS{

class Stage;

class PlayerChild : public Character
{
public:
	PlayerChild(float maxMoveSpeed , float maxJumpPower, int maxJumpCount, int maxHP);
	virtual ~PlayerChild() { SAFE_DELETE(p); };
	virtual PlayerChild* update(const Stage*) = 0;
	void draw() const;
	const Vector2* getVector2() const { return p; }
	const Vector2* getCamera() const { return camera; }

protected:
	//キャラごとに移動速度などの違いを出すならここの変数をいじくる
	const float maxMoveSpeed;
	const float maxJumpPower;
	const int maxJumpCount;

	//他の変数
	Vector2* p; //staticではないからキャラ変更のたびにdeleteしよう
	Vector2* camera;
	float moveSpeed;
	float jumpPower;
	int nowJumpCount;
	bool prePush;

	int img;

	//共通の行動
	virtual void attack() = 0;
	virtual void draw_other() const = 0; //自機以外を描画する
	virtual void loadImage() = 0;

	//Characterの関数
	//virtual void damagedAction() = 0;

	void standardMove(const Stage*);

private:
	void move(const Stage*);

	int jump();
	int gravity();

	int getVerticalDiffer(const Stage*, const int) const;
	int getHorizontalDiffer(const Stage*, const int) const;

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