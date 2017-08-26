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
	PlayerChild(int x, int y, float maxMoveSpeed , float maxJumpPower, int maxJumpCount, int maxHP);
	virtual ~PlayerChild();
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
	bool direction;

	//攻撃のvector
	vector<Attack*> attacks;

	//共通の行動
	bool canChangeCharacter();
	virtual void attack() = 0;
	virtual void draw_other() const = 0; //自機以外を描画する
	virtual void loadImage() = 0;
	
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

	//その他
	void initialize();
	void processDamage();
	void hittedAction() override;
	void move(const Stage*);
	void updateCamera();
	bool isOnGround(const Stage*);

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