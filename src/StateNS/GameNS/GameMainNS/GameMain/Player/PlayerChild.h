#pragma once

#include "..\..\..\..\..\Data.h"
#include "..\..\..\..\..\KeyInput.h"
#include "..\Character.h"
#include "..\..\GameMain.h"

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
	const Vector2* getCamera() const { return camera; }
	GameMain::HowStageMove getStageMove() const { return nextStageMove; };

protected:
	//変数
	float moveSpeed;
	Vector2* camera;
	int mImage;
	int animationTime;

	//共通の行動
	bool canChangeCharacter();
	virtual void attack() = 0;
	virtual void draw_other() const = 0; //自機以外を描画する
	virtual void loadImage() = 0;

	//Characterの関数
	//virtual void damagedAction() = 0;

	void standardAction(const Stage*);

private:
	//キャラごとに移動速度などの違いを出すならここの変数をいじくる
	const float maxMoveSpeed;
	const float maxJumpPower;
	const int maxJumpCount;

	//他の変数
	float jumpPower;
	int nowJumpCount;
	bool prePush;
	GameMain::HowStageMove nextStageMove;

	//前フレームでの自機の位置
	int post_x;
	int post_y;

	//キャラクター切り換え関連
	bool isCharaChange;
	void changeCharacter();
	void draw_changingAnimation(int, int) const;

	void initialize();
	void move(const Stage*);
	bool isOnGround(const Stage*);

	int getVerticalDiffer(const Stage*, const int) const;
	int getHorizontalDiffer(const Stage*, const int) const;

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