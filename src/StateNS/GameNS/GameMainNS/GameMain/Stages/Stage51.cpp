#include "Stage51.h"
#include "Map.h"
#include "..\..\GameMain.h"
#include "..\Gimmick\ClearFlag.h"

#include <fstream>

namespace StateNS {
namespace GameNS {
namespace GameMainNS{

Stage51::Stage51() :
StageChild(5, 1) //エリアの数: よこ，たて
{
	initialize();
}

Stage51::~Stage51()
{

}

void Stage51::initialize()
{

	//変更できるキャラクターを設定
	this->changeableCharacter |= CHARA_MOKOU;
	this->changeableCharacter |= CHARA_SAKUYA;
	this->changeableCharacter |= CHARA_NUE;

	//左上から右にpushしていく
	//StageID, 0から昇順, エリアの形
	this->maps.push_back(new Map(51, 0, MapPos::POS_RIGHT_FREE));
	this->maps.push_back(new Map(51, 1, MapPos::POS_UP_DOWN));
	this->maps.push_back(new Map(51, 2, MapPos::POS_UP_DOWN));
	this->maps.push_back(new Map(51, 3, MapPos::POS_UP_DOWN));
	this->maps.push_back(new Map(51, 4, MapPos::POS_LEFT_FREE));


	flag = new ClearFlag(Vector2(176, 1552));
	maps[0]->addGimmick(flag);
	now_stage_num = 2;
	startX = 144, startY = 1536;


}


void Stage51::update(GameMain* gameMain, PlayerChild* _player)
{
	standardUpdate(_player);

	//for Debug
	if(CheckHitKey(KEY_INPUT_1))
		gameMain->startConverse(12);
}

void Stage51::draw(const Vector2* _camera) const
{
	standardDraw(_camera);
}

bool Stage51::isClear() const
{
	return !flag->isActive;
}


}
}
}


