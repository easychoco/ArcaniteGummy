#pragma once

#include "..\Character.h"
#include "..\Attack.h"

#include "..\..\..\..\..\Data.h"
#include "..\..\..\..\..\KeyInput.h"
#include "..\..\GameMain.h"
#include "..\Stages\StageChild.h"


namespace StateNS {
namespace GameNS {
namespace GameMainNS{

class Attack;

class PlayerChild : public Character
{
public:
	PlayerChild(int x, int y, float maxMoveSpeed ,float jump,int jumpCount, int maxHP);
	virtual ~PlayerChild();
	virtual PlayerChild* update(const StageChild*) = 0;
	virtual void draw() const;
	const Vector2* getCamera() const { return camera; }
	vector<Attack*> getAttacks() const { return attacks; }
	StageChild::HowStageMove getStageMove() const { return nextStageMove; }
	int getFloorCoordinate() override;
	virtual bool hasAdditionalGimmick() const { return false; }
	virtual DynamicGimmickChild* getAdditionalGimmick() const { assert(!"ここにはこない"); return NULL; }


	const StopType getStopDynamicObject() const { return stopDynamics; }
	void moveCamera(int dx, int dy);
	void setCamera(const Vector2& _camera) { *(this->camera) = _camera; };

protected:
	//変数
	float moveSpeed;
	Vector2* camera;
	int mImage[32];
	bool direction;

	int animationTime;
	virtual StageChild::ChangeableCharacter getThisCharacter() { return StageChild::ChangeableCharacter::CHARA_NONE; };

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

	//今いる位置関係
	bool onGround;
	bool onLadder;
	
	//攻撃のvector
	vector<Attack*> attacks;


	//共通の行動
	bool canChangeCharacter();
	virtual void attack() = 0;
	virtual void draw_other() const = 0; //自機以外を描画する
	void draw_changingAnimation(int, int) const;
	virtual void loadImage() = 0;
	virtual bool onRigidBlock() const override { return false; }
	virtual void animation();

	void standardAction(const StageChild*);
	void actCheck();
	bool runCheck() 
	{
		return 
			actionState == ACT_ATTACK_SIDE_RUN ||
			actionState == ACT_ATTACK_UP_RUN ||
			actionState == ACT_RUN ||
			actionState == ACT_RUNJUMP;
	}
	int ladderTime;

	//各状態
	enum ActionState
	{
		ACT_NORMAL, //通常状態
		ACT_WALK,//歩いている
		ACT_RUN,//走っている
		ACT_AIR, //空中にいる
		ACT_RUNJUMP,//走ってジャンプしている
		ACT_ATTACK_SIDE, //横攻撃
		ACT_ATTACK_UP,//上攻撃
		ACT_ATTACK_SIDE_WALK, //横歩き攻撃
		ACT_ATTACK_UP_WALK,//上歩き攻撃
		ACT_ATTACK_SIDE_RUN, //横走り攻撃
		ACT_ATTACK_UP_RUN,//上走り攻撃
		ACT_SIT, //しゃがみ
		ACT_LADDER, //はしご
	};
	ActionState actionState;

	int getTopDiffer(const StageChild* _stage, const int dy, bool _moveLeft) const override { return DynamicObject::getTopDiffer(_stage, dy, _moveLeft, true); }
	int getBottomDiffer(const StageChild* _stage, const int dy, bool _moveLeft) const override { return DynamicObject::getBottomDiffer(_stage, dy, _moveLeft, true); }
	int getHorizontalDiffer(const StageChild* _stage, const int dx, bool _moveUp) const override { return DynamicObject::getHorizontalDiffer(_stage, dx, _moveUp, true); }


private:
	//キャラごとに移動速度などの違いを出すならここの変数をいじくる
	const float maxMoveSpeed;

	//他の変数
	bool prePush;
	StageChild::HowStageMove nextStageMove;

	//前フレームでの自機の位置
	int post_x;
	int post_y;

	//キャラクター切り換え関連
	bool isCharaChange;
	void changeCharacter(const StageChild*);

	//その他
	void initialize();
	void processDamage();
	void hittedAction() override;
	void move(const StageChild*);
	void updateCamera();
	bool isOnGround(const StageChild*);
	bool isOnLadder(const StageChild*) const;
	bool isOnLesal(const StageChild*);



};






}
}
}