#include "EnemyController.h"

#include "EnemyChild.h"
#include "Usagi.h"


namespace StateNS {
namespace GameNS {
namespace GameMainNS{




EnemyController::EnemyController()
{
	enemies.push_back(new Usagi(96, 96));
	enemies.push_back(new Usagi(480, 128));
}

EnemyController::~EnemyController()
{
	for (auto& enemy : enemies)
	{
		SAFE_DELETE(enemy);

	}
	enemies.clear();
	enemies.shrink_to_fit();
}

void EnemyController::update()
{
	for (auto& enemy : enemies)
	{
		enemy->update();
	}
}

void EnemyController::draw(const Vector2* _camera) const
{
	for (auto& enemy : enemies)
	{
		enemy->draw(_camera);
	}
}

void EnemyController::createEnemy()
{

}

void EnemyController::deleteEnemy(int _ID)
{

}



}
}
}