#pragma once

#include "..\..\..\..\..\Data.h"
#include "..\Character.h"

namespace StateNS {
namespace GameNS {
namespace GameMainNS{

class EnemyChild : public Character
{
public:
	EnemyChild(int hp, int x, int y, int w, int h);
	virtual ~EnemyChild();
	virtual void update(const Stage*) = 0;
	void draw(const Vector2* camera) const;


protected:
	int mTime;
	int mImage;
	bool mDirection;

	//dx と dy に移動量を入れる
	virtual void move(const Stage*, int& dx, int& dy) = 0;
	virtual void loadImage() = 0;

	void standardAction(const Stage* _stage);
	void standardMove(const Stage* _stage);

private:
	bool isAlive;

	void initialize();




};



}
}
}