#include "EnemyController.h"

#include "EnemyChild.h"
#include "Usagi.h"
#include "Balloon.h"
#include "Yachamo.h"
#include "Pikachi.h"

#include "..\Player\PlayerChild.h"


namespace StateNS {
namespace GameNS {
namespace GameMainNS{




EnemyController::EnemyController()
{
//	enemies.push_back(new Balloon(300, 1450));
//	enemies.push_back(new Usagi(200, 1450));
	enemies.push_back(new Yachamo(1000, 1482));
	enemies.push_back(new Pikachi(300, 1482));
	//enemies.push_back(new Usagi(320, 240));
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

void EnemyController::update(const StageChild* _stage, const Vector2* _camera)
{
	for (auto& enemy : enemies)
	{
		enemy->update(_stage,_camera);
	}
}

void EnemyController::draw(const Vector2* _camera) const
{
	for (auto& enemy : enemies)
	{
		enemy->draw(_camera);
	}
}

//Ž©‹@‚Æ“G‚Ì–{‘Ì“¯Žm‚ÌÕ“Ë”»’è
void EnemyController::processCollision(PlayerChild* _player)
{
	for (auto& enemy : enemies)
	{
		/*
		if (_player->isHit(enemy))
		{
			_player->hpController.damage(10);
		}
		*/
		//(_player->isHit(enemy->getAttacks()))

	}
}

void EnemyController::createEnemy(/*—ñ‹“Œ^‚Å“GŽw’è*/)
{

}

void EnemyController::deleteEnemy(int _ID)
{

}

void EnemyController::setPlayerPos(const Vector2* player)
{
	for (auto& enemy : enemies)
	{
		enemy->setPlayer(player);
	}
}



}
}
}