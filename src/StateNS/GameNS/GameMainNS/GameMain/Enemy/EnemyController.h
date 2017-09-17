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

	vector<EnemyChild*>& getEnemies() { return enemies; }

	//©‹@‚Æ“G‚ÌUŒ‚‚Æ‚Ì“–‚½‚è”»’è
	void processCollision(PlayerChild*);

	void createEnemy();
	void deleteEnemy(int ID);
	void setPlayerPos(const Vector2* player);

private:
	vector<EnemyChild*> enemies;


};





}
}
}