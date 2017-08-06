#pragma once

#include "..\..\..\..\..\Data.h"


namespace StateNS {
namespace GameNS {
namespace GameMainNS{

class EnemyChild;

class EnemyController
{
public:
	EnemyController();
	~EnemyController();

	void update();
	void draw(const Vector2*) const;

	void createEnemy();
	void deleteEnemy(int ID);

private:
	vector<EnemyChild*> enemies;


};





}
}
}