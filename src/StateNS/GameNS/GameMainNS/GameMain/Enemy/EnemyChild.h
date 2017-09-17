#pragma once

#include "..\..\..\..\..\Data.h"
#include "..\Character.h"

namespace StateNS {
namespace GameNS {
namespace GameMainNS{

class EnemyChild : public Character
{
public:
	EnemyChild(int hp, int x, int y, int w, int h, float jump, int jumpCount);
	virtual ~EnemyChild();
	virtual void update(const Stage*) = 0;
	void draw(const Vector2* camera) const;
	bool isAlive() const { return mIsAlive; }
	void setPlayer(const Vector2* _player) { this->player = _player; }

protected:
	int mTime;
	int mImage;
	bool mDirection;
	const Vector2* player;

	//dx ‚Æ dy ‚ÉˆÚ“®—Ê‚ð“ü‚ê‚é
	virtual void move(const Stage*, int& dx, int& dy) = 0;
	virtual void loadImage() = 0;

	void standardAction(const Stage* _stage);

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