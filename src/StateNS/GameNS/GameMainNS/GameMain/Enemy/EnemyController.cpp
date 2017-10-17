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
#include "Icicle.h"
#include "Mariri.h"
#include "Kawarimi.h"

#include "Reisen.h"
#include "Junko.h"
#include "Nue_boss.h"
#include "Fran.h"
#include "Kaguya.h"


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
			if(enemy->isActive())enemy->update(_stage, _camera);
		}
	}
}

void EnemyController::draw(const Vector2* _camera) const
{
	for (auto& enemy : enemies)
	{
		enemy->draw(_camera);
	}
}

//自機と敵の本体同士の衝突判定
void EnemyController::processCollision(PlayerChild* _player)
{
	//for (auto& enemy : enemies)
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

void EnemyController::addEnemy(EnemyChild* _enemy)
{
	this->enemies.push_back(_enemy);
}

void EnemyController::addEnemy(AllEnemies _enemy, const Vector2* _player, int _x, int _y)
{
	EnemyChild* ene_tmp = 0;
	switch (_enemy)
	{
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
	case ENE_ICE: ene_tmp = new Icicle(_x, _y); break;
	case ENE_MARI: ene_tmp = new Mariri(_x, _y); break;
	case ENE_KAWARI: ene_tmp = new Kawarimi(_x, _y); break;
	case BOSS_REISEN: ene_tmp = new Reisen(_x, _y); break;
	case BOSS_JUNKO: ene_tmp = new Junko(_x, _y); break;
	case BOSS_NUE: ene_tmp = new Nue_Boss(_x, _y); break;
	case BOSS_FRAN: ene_tmp = new Fran(_x, _y); break;

	default: assert(!"EnemyController: 不明な敵です.");
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