#include "EnemyController.h"

#include "EnemyChild.h"
#include "Usagi.h"

#include "..\Player\PlayerChild.h"

//for Debug
#include "..\Collision.h"

namespace StateNS {
namespace GameNS {
namespace GameMainNS{




EnemyController::EnemyController()
{
	//enemies.push_back(new Usagi(96, 96));
	enemies.push_back(new Usagi(480, 128));
	enemies.push_back(new Usagi(320, 240));
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

void EnemyController::update(const Stage* _stage)
{
	for (auto& enemy : enemies)
	{
		enemy->update(_stage);
	}
}

void EnemyController::draw(const Vector2* _camera) const
{
	for (auto& enemy : enemies)
	{
		enemy->draw(_camera);
	}

	//for Debug
	if (enemies.size() >= 2)DrawFormatString(0, 190, MyData::BLACK, "ene1_hp %d", enemies[1]->hpController.getHP());
}

//Ž©‹@‚Æ“G‚Ì–{‘Ì“¯Žm‚ÌÕ“Ë”»’è
void EnemyController::processCollision(PlayerChild* _player)
{
	for (auto& enemy : enemies)
	{
		if (_player->isHit(enemy))
		{
			_player->hpController.damage(10);
		}
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