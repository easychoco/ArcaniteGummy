#include "PlayerChild.h"
#include "..\Stage.h"

namespace StateNS {
namespace GameNS {
namespace GameMainNS{

PlayerChild::PlayerChild()
{
	this->moveSpeed = 1.0f;
	this->jumpPower = 0.0f;
	this->maxJumpPower = 15.0f;
}

void PlayerChild::standardMove(const Stage* _stage)
{
	int dx = 0;
	int dy = 0;

	//横移動
	if (Input_RIGHT())dx += (int)(moveSpeed * MyData::vectorRate);
	if (Input_LEFT())dx -= (int)(moveSpeed * MyData::vectorRate);

	//縦移動
	dy += gravity() - jump();

	//ジャンプ
	if (Input_JUMP())jumpPower = maxJumpPower;
	

	int nextX = max(0, min(MyData::MAP_WIDTH * MyData::vectorRate, p->pos_x + dx)) / MyData::vectorRate;
	int nextY = max(0, min(MyData::MAP_HEIGHT * MyData::vectorRate, p->pos_y + dy)) / MyData::vectorRate;

	//移動先がいける場所なら の形式
	if (_stage->canPass(Vector2(p->x(),nextY)))
	{
		p->pos_y = nextY * MyData::vectorRate;
	}
	if (_stage->canPass(Vector2(nextX, p->y())))
	{
		p->pos_x = nextX * MyData::vectorRate;
	}
}

//ジャンプでの移動量を返す
//正の値で上方向
int PlayerChild::jump()
{
	jumpPower = max(0.0f, jumpPower - 1.0f);
	return (int)(jumpPower * MyData::vectorRate);
}

//かかる重力を返す
//正の値で下方向
int PlayerChild::gravity()
{
	//for Debug
	//このままいくならconstexprで
	return 5 * MyData::vectorRate;
}


}
}
}