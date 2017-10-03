#pragma once

#include "..\..\..\..\..\Data.h"


namespace StateNS {
namespace GameNS {
namespace GameMainNS{

class EnemyChild;
class StageChild;
class PlayerChild;

class EnemyController
{
public:
	EnemyController();
	~EnemyController();

	void update(const StageChild* _stage, const Vector2* _camera);
	void draw(const Vector2*) const;

	vector<EnemyChild*>& getEnemies() { return enemies; }

	//©‹@‚Æ“G‚ÌUŒ‚‚Æ‚Ì“–‚½‚è”»’è
	void processCollision(PlayerChild*);

	//void addEnemy(AllEnemies, int x, int y);
	void addEnemy(AllEnemies, const Vector2*, int x, int y);
	void deleteEnemy(int ID);
	void setPlayerPos(const Vector2* player);

private:
	vector<EnemyChild*> enemies;


};





}
}
}