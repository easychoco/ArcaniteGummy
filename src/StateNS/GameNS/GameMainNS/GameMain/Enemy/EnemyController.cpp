#include "EnemyController.h"

#include "EnemyChild.h"
#include "Usagi.h"
#include "Balloon.h"
#include "Yachamo.h"
#include "Pikachi.h"
#include "Poppy.h"
#include "Rarashi.h"
#include "Reisen.h"
#include "..\Player\PlayerChild.h"


namespace StateNS {
namespace GameNS {
namespace GameMainNS{




EnemyController::EnemyController()
{
	//enemies.push_back(new Poppy(60, 1450));
	//enemies.push_back(new Rarashi(600, 1386));
	//enemies.push_back(new Yachamo(1000, 1482));
	//enemies.push_back(new Pikachi(300, 1482));
	//enemies.push_back(new Usagi(220, 1000));
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

void EnemyController::addEnemy(AllEnemies _enemy, int _x, int _y)
{
	switch (_enemy)
	{
	case ENE_USA: enemies.push_back(new Usagi(_x, _y)); break;
	case ENE_BALL: enemies.push_back(new Balloon(_x, _y)); break;
	case ENE_YACH: enemies.push_back(new Yachamo(_x, _y)); break;
	case ENE_PIKA: enemies.push_back(new Pikachi(_x, _y)); break;
	case ENE_POPPY: enemies.push_back(new Poppy(_x, _y)); break;
	case ENE_RARA: enemies.push_back(new Rarashi(_x, _y)); break;
	case BOSS_REISEN: enemies.push_back(new Reisen(_x, _y)); break;
	default: assert(!"•s–¾‚È“G‚Å‚·.");
	}
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