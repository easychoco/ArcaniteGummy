#pragma once

#include "..\..\..\..\..\Data.h"


namespace StateNS {
namespace GameNS {
namespace GameMainNS{

class EnemyChild;
class Stage;
class PlayerChild;

class EnemyController
{
public:
	EnemyController();
	~EnemyController();

	void update(const Stage*);
	void draw(const Vector2*) const;

	void processCollision(PlayerChild*);

	void createEnemy();
	void deleteEnemy(int ID);

private:
	vector<EnemyChild*> enemies;


};





}
}
}