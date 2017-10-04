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

	void draw(const Vector2* camera) const;
	void standardDraw(const Vector2* _camera, const bool& _direction) const;
	virtual void draw_other(const Vector2* camera)const {}

	bool isAlive() const { return mIsAlive; }

	virtual void setPlayer(const Vector2* _player) { this->player = _player; }

	virtual vector<Attack*> getAttacks() const { return attacks; }
	virtual vector<EnemyChild*> getChilds() { vector<EnemyChild*> gomi{ this }; return gomi; };

	const bool isBoss;

protected:
	//int mImage[8];
	//int mImage2;
	int mImage;
	bool mDirection;
	const Vector2* player;
	int aTime;

	//dx ‚Æ dy ‚ÉˆÚ“®—Ê‚ğ“ü‚ê‚é
	virtual void move(const StageChild*, int& dx, int& dy) = 0;
	virtual void loadImage() = 0;

	void standardAction(const StageChild* _stage);
	//UŒ‚‚Ìvector
	vector<Attack*> attacks;

	enum ActState {
		ENE_ACT_NONE,
		ENE_ACT_WALK,
		ENE_ACT_ATTACK,
		ENE_ACT_DEAD,
	};
	ActState actState;

private:
	bool mIsAlive;


	void initialize();
	void standardMove(const StageChild* stage);
	void checkIsAlive(const StageChild* stage);
	void processDamage();



};



}
}
}