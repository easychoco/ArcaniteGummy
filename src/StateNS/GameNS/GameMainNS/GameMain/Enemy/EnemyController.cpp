#include "EnemyController.h"

#include <stack>

#include "EnemyChild.h"
#include "Usagi.h"
#include "Balloon.h"
#include "Yachamo.h"
#include "Pikachi.h"
#include "Poppy.h"
#include "Rarashi.h"
#include "Broth.h"
#include "Karon.h"
#include "Airmz.h"
#include "Teresa.h"

#include "Reisen.h"
#include "Junko.h"

#include "..\Player\PlayerChild.h"


namespace StateNS {
namespace GameNS {
namespace GameMainNS{




EnemyController::EnemyController()
{
	//速度を上げるため敵20体分のメモリを確保しておく
	enemies.reserve(20);

	time = 0;
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
	time++;

	//15秒毎にvectorのメモリ使用量を最小化する
	if (time % 900 == 10)minimize_enemies();
	else
	{
		for (auto& enemy : enemies)
		{
			enemy->update(_stage, _camera);
		}
	}
}

void EnemyController::draw(const Vector2* _camera) const
{
	for (auto& enemy : enemies)
	{
		enemy->draw(_camera);
	}
	
	//for Debug
	DrawFormatString(20,  60, BLACK, "time : %d", time % 300);
	DrawFormatString(20,  80, BLACK, "size : %d", enemies.size());
	DrawFormatString(20, 100, BLACK, "capa : %d", enemies.capacity());
}

//自機と敵の本体同士の衝突判定
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

void EnemyController::addEnemy(AllEnemies _enemy, const Vector2* _player, int _x, int _y)
{
	EnemyChild* ene_tmp;
	switch (_enemy)
	{
	/*
	case ENE_USA: enemies.push_back(new Usagi(_x, _y)); break;
	case ENE_BALL: enemies.push_back(new Balloon(_x, _y)); break;
	case ENE_YACH: enemies.push_back(new Yachamo(_x, _y)); break;
	case ENE_PIKA: enemies.push_back(new Pikachi(_x, _y)); break;
	case ENE_POPPY: enemies.push_back(new Poppy(_x, _y)); break;
	case ENE_RARA: enemies.push_back(new Rarashi(_x, _y)); break;
	case ENE_BROTH: enemies.push_back(new Broth(_x, _y)); break;
	case ENE_KARON: enemies.push_back(new Karon(_x, _y)); break;
	case ENE_AIRMZ: enemies.push_back(new Airmz(_x, _y)); break;
	case ENE_TERESA: enemies.push_back(new Teresa(_x, _y)); break;

	case BOSS_REISEN: enemies.push_back(new Reisen(_x, _y)); break;
	case BOSS_JUNKO: enemies.push_back(new Junko(_x, _y)); break;
	default: assert(!"不明な敵です.");
	*/
	case ENE_USA: ene_tmp = new Usagi(_x, _y); break;
	case ENE_BALL: ene_tmp = new Balloon(_x, _y); break;
	case ENE_YACH: ene_tmp = new Yachamo(_x, _y); break;
	case ENE_PIKA: ene_tmp = new Pikachi(_x, _y); break;
	case ENE_POPPY: ene_tmp = new Poppy(_x, _y); break;
	case ENE_RARA: ene_tmp = new Rarashi(_x, _y); break;
	case ENE_BROTH: ene_tmp = new Broth(_x, _y); break;
	case ENE_KARON: ene_tmp = new Karon(_x, _y); break;
	case ENE_AIRMZ: ene_tmp = new Airmz(_x, _y); break;
	case ENE_TERESA: ene_tmp = new Teresa(_x, _y); break;

	case BOSS_REISEN: ene_tmp = new Reisen(_x, _y); break;
	case BOSS_JUNKO: ene_tmp = new Junko(_x, _y); break;

	default: assert(!"不明な敵です.");
	}
	
	if(_player != &Vector2::ZERO)ene_tmp->setPlayer(_player);

	//TODO : Flyweightチックにする?
	enemies.push_back(ene_tmp);
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


//=================================
//内部private関数
//=================================
void EnemyController::minimize_enemies()
{
	//isAliveがfalseになっている敵のインデックスをstackに記憶
	std::stack<int> erase_subs;
	int ene_size = (int)enemies.size();
	for (int i = 0; i < ene_size; i++)
	{
		if (!enemies[i]->isAlive())
		{
			erase_subs.push(i);
		}
	}

	//そして削除
	while (!erase_subs.empty())
	{
		if(!enemies[erase_subs.top()]->isBoss)remove(enemies, erase_subs.top());
		erase_subs.pop();
	}
	enemies.shrink_to_fit();
}


}
}
}