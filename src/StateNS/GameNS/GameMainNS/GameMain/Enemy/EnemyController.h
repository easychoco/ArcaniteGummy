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

	//é©ã@Ç∆ìGÇÃçUåÇÇ∆ÇÃìñÇΩÇËîªíË
	void processCollision(PlayerChild*);

	void addEnemy(EnemyChild*);
	void addEnemy(AllEnemies, const Vector2*, int x, int y);
	void deleteEnemy(int ID);
	void setPlayerPos(const Vector2* player);

	void minimize_enemies();

private:
	int time;
	vector<EnemyChild*> enemies;



	template<typename T>
	void remove(std::vector<T>& vector, unsigned int index)
	{
		vector.erase(vector.begin() + index);
	}
};





}
}
}