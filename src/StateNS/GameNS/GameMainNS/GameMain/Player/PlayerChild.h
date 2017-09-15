#pragma once

#include "..\Character.h"
#include "..\Attack.h"

#include "..\..\..\..\..\Data.h"
#include "..\..\..\..\..\KeyInput.h"
#include "..\..\GameMain.h"


namespace StateNS {
namespace GameNS {
namespace GameMainNS{

class Stage;
class Attack;

class PlayerChild : public Character
{
public:
	PlayerChild(int x, int y, float maxMoveSpeed ,float jump,int jumpCount, int maxHP);
	virtual ~PlayerChild();
	virtual PlayerChild* update(const Stage*) = 0;
	void draw() const;
	const Vector2* getCamera() const { return camera; }
	vector<Attack*> getAttacks() const { return attacks; }
	GameMain::HowStageMove getStageMove() const { return nextStageMove; };

	virtual int specialAction() = 0;

	const StopType getStopDynamicObject() const { return stopDynamics; }

protected:
	//変数
	float moveSpeed;
	Vector2* camera;
	int mImage[40];
	int animationTime;
	bool direction;

	int animeNum;
	int animeCount;
	bool canMove;
	bool prePushC;
	StopType stopDynamics;

	//入力関係
	bool in_right;
	bool in_left;
	bool in_up;
	bool in_down;
	bool in_jump;


	//攻撃のvector
	vector<Attack*> attacks;

	//共通の行動
	bool canChangeCharacter();
	virtual void attack() = 0;
	virtual void draw_other() const = 0; //自機以外を描画する
	virtual void loadImage() = 0;
	virtual bool onRigidBlock() const override { return false; }

	void standardAction(const Stage*);
	int animation();

	void actCheck();

	//各状態
	enum ActionState
	{
		ACT_NORMAL, //通常状態
		ACT_WALK,//歩いている
		ACT_RUN,//走っている
		ACT_AIR, //空中にいる
		ACT_ATTACK, //攻撃
		ACT_SIT, //しゃがみ
		ACT_LADDER, //はしご

	};
	ActionState actionState;


private:
	//キャラごとに移動速度などの違いを出すならここの変数をいじくる
	const float maxMoveSpeed;

	//他の変数
	bool prePush;
	GameMain::HowStageMove nextStageMove;

	//前フレームでの自機の位置
	int post_x;
	int post_y;

	//キャラクター切り換え関連
	bool isCharaChange;
	void changeCharacter();
	void draw_changingAnimation(int, int) const;

	//今いる位置関係
	bool onGround;
	bool onLadder;

	//その他
	void initialize();
	void processDamage();
	void hittedAction() override;
	void move(const Stage*);
	void updateCamera();
	bool isOnGround(const Stage*);
	bool isOnLadder(const Stage*) const;



};






}
}
}