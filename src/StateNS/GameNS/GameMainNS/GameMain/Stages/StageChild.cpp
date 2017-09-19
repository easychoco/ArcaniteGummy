#include "StageChild.h"
#include "Map.h"

//#include "..\Player\PlayerChild.h"
//#include "..\Gimmick\GimmickChild.h"
//#include "..\Gimmick\AllGimmicks.h"
//#include "..\Gimmick\DynamicGimmickChild.h"

#include "..\..\..\..\..\KeyInput.h"

namespace StateNS {
namespace GameNS {
namespace GameMainNS{


StageChild::StageChild(int _stage_max_x,int _stage_max_y)
{
	stage_max_x = _stage_max_x;
	stage_max_y = _stage_max_y;

	initialize();
	mBackImg = LoadGraph("Data/Image/back.jpg");
	assert(mBackImg != -1 && "背景画像読み込みエラー");
}

StageChild::~StageChild()
{
	for (auto& map : maps)
	{
		SAFE_DELETE(map);
	}
	maps.clear();
	maps.shrink_to_fit();

	DeleteGraph(mBackImg);
	for (int i = 0; i < 256; i++)
		DeleteGraph(mapChip[i]);
}

void StageChild::initialize()
{
	this->now_stage_num = 0;

	// for Debug
	//mDynamicGimmicks.push_back(new MovingFloor(300, 1400, 360, 1200, 3.0));
	//mDynamicGimmicks.push_back(new FireBar(304, 1488,true));
	//mDynamicGimmicks.push_back(new Block(656, 1488, 1.0));
	//mDynamicGimmicks.push_back(new Block(688, 1488, 1.0, false));
	//mSwitchWithBlocks.push_back(new SwitchWithBlock(208, 1488));
	
	//mSwitchWithBlocks[0]->push_block(new Block(208, 1296, 1.0));
	//mSwitchWithBlocks[0]->push_block(new Block(256, 1312, 2.0));
}

void StageChild::standardUpdate(PlayerChild* _player)
{
	maps[now_stage_num]->update(_player, this);
}

void StageChild::standardDraw(const Vector2* _camera) const
{
	DrawGraph(0, 0, mBackImg, true);
	maps[now_stage_num]->draw(_camera);
}

StageChild::ChipType StageChild::getChipType(const Vector2& _other, bool isPlayer) const
{
	return maps[now_stage_num]->getChipType(_other, isPlayer);
}

//ポリモーフィズム
StageChild::ChipType StageChild::getChipType(const Vector2& _other) const
{
	return getChipType(_other, true);
}

//ポリモーフィズム
StageChild::ChipType StageChild::getChipType(const RawVector2& _other, bool _isPlayer) const
{
	return getChipType(Vector2(_other.pos_x, _other.pos_y), _isPlayer);
}

int StageChild::getTopPosition(const Vector2* _pos, const int& _dy) const
{
	return maps[now_stage_num]->getTopPosition(_pos, _dy);
}

int StageChild::getBottomPosition(const Vector2* _pos, const int& _dy) const
{
	return maps[now_stage_num]->getBottomPosition(_pos, _dy);
}

vector< DynamicGimmickChild* > StageChild::getDynamicGimmicks()
{
	return maps[now_stage_num]->getDynamicGimmicks();
}

vector< SwitchWithBlock* > StageChild::getSwitchWithBlocks()
{
	return maps[now_stage_num]->getSwitchWithBlocks();
}

EnemyController* StageChild::getEController()
{
	return maps[now_stage_num]->getEController();
}

void StageChild::moveStage(HowStageMove _stageMove)
{
	switch (_stageMove)
	{
	case MOVE_RIGHT:
		now_stage_num++;
		break;
	case MOVE_LEFT:
		now_stage_num--;
		break;
	case MOVE_UP:
		now_stage_num -= stage_max_y;
		break;
	case MOVE_DOWN:
		now_stage_num += stage_max_y;
		break;
	}
	assert(now_stage_num < maps.size() && "StageChild: map index out of range!");

}


//========================================================================
// 内部private関数
//========================================================================




}
}
}


