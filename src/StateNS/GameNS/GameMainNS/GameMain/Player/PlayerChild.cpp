#include "PlayerChild.h"
#include "..\Stage.h"

namespace StateNS {
namespace GameNS {
namespace GameMainNS{


void PlayerChild::standardMove(const Stage* _stage)
{
	int dx = 0;
	int dy = 0;

	if (Input_RIGHT())dx += (int)(speed * MyData::vectorRate);
	if (Input_LEFT())dx -= (int)(speed * MyData::vectorRate);

	//for Debug	
	//Œã‚Åd—ÍˆÚ“®‚É‘‚«Š·‚¦
	if (Input_UP())dy -= (int)(speed * MyData::vectorRate);
	if (Input_DOWN())dy += (int)(speed * MyData::vectorRate);


	int nextX = max(0, min(MyData::MAP_WIDTH * MyData::vectorRate, p->pos_x + dx)) / MyData::vectorRate;
	int nextY = max(0, min(MyData::MAP_HEIGHT * MyData::vectorRate, p->pos_y + dy)) / MyData::vectorRate;

	if (_stage->canPass(Vector2(p->x(),nextY)))
	{
		p->pos_y = nextY * MyData::vectorRate;
	}
	if (_stage->canPass(Vector2(nextX, p->y())))
	{
		p->pos_x = nextX * MyData::vectorRate;
	}
}




}
}
}