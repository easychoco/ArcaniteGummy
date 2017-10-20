#pragma once

#include "..\..\..\..\..\Data.h"
#include "..\Character.h"
#include "..\Attack.h"

namespace StateNS {
namespace GameNS {
namespace GameMainNS{

class EnemyChild : public Character
{
public:
	EnemyChild(int hp, int x, int y, int w, int h);
	EnemyChild(int hp, int x, int y, int w, int h, bool hasChild, bool isBoss);

	virtual ~EnemyChild();
	virtual void update(const StageChild*,const Vector2*) = 0;

	virtual void draw(const Vector2* camera) const;
	void standardDraw(const Vector2* _camera, const bool& _direction) const;
	virtual void draw_other(const Vector2* camera)const {}

	bool isAlive()  const { return mIsAlive; }
	bool isActive() const { return mIsActive; }
	void checkIsActive(const Vector2* camera) const;

	virtual void setPlayer(const Vector2* _player) { this->player = _player; }

	virtual vector<Attack*> getAttacks() const { return attacks; }
	virtual vector<EnemyChild*> getChilds() { vector<EnemyChild*> gomi{ this }; return gomi; };

	
	const bool isBoss;

protected:
	int mImage;
	bool mDirection;
	const Vector2* player;
	int aTime;

	bool mIsAlive;
	mutable bool mIsActive;
	int deadTime;

	//dx と dy に移動量を入れる
	virtual void move(const StageChild*, int& dx, int& dy) = 0;
	virtual void loadImage() = 0;
	virtual void setChildActive(bool) const {};

	void standardAction(const StageChild* _stage);

	//HPバーを表示 1,2番目の引数はHPバーの中心
	void draw_hp_bar(int x, int y, int maxHP, int width) const;

	//攻撃のvector
	vector<Attack*> attacks;

	enum ActState 
	{
		ENE_ACT_NONE,
		ENE_ACT_WALK,
		ENE_ACT_ATTACK,
		ENE_ACT_DEAD,
	};
	ActState actState;

	int getTopDiffer(const StageChild* _stage, const int dy, bool _moveLeft) const override { return DynamicObject::getTopDiffer(_stage, dy, _moveLeft, true); }
	int getBottomDiffer(const StageChild* _stage, const int dy, bool _moveLeft) const override { return DynamicObject::getBottomDiffer(_stage, dy, _moveLeft, true); }
	int getHorizontalDiffer(const StageChild* _stage, const int dx, bool _moveUp) const override { return DynamicObject::getHorizontalDiffer(_stage, dx, _moveUp, true); }

private:


	void initialize();
	void standardMove(const StageChild* stage);
	void checkIsAlive(const StageChild* stage);
	void processDamage();



};



}
}
}