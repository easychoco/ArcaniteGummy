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
	EnemyChild(int hp, int x, int y, int w, int h, float jump, int jumpCount);
	virtual ~EnemyChild();
	virtual void update(const Stage*,const Vector2*) = 0;
	void draw(const Vector2* camera) const;
	virtual void draw_other(const Vector2* camera)const {}
	bool isAlive() const { return mIsAlive; }
	void setPlayer(const Vector2* _player) { this->player = _player; }
	vector<Attack*> getAttacks() const { return attacks; }
protected:
	int mTime;
	int mImage;
	bool mDirection;
	const Vector2* player;

	//dx ‚Æ dy ‚ÉˆÚ“®—Ê‚ğ“ü‚ê‚é
	virtual void move(const Stage*, int& dx, int& dy) = 0;
	virtual void loadImage() = 0;

	void standardAction(const Stage* _stage);
	//UŒ‚‚Ìvector
	vector<Attack*> attacks;
private:
	bool mIsAlive;


	void initialize();
	void standardMove(const Stage* stage);
	void checkIsAlive(const Stage* stage);
	void processDamage();



};



}
}
}