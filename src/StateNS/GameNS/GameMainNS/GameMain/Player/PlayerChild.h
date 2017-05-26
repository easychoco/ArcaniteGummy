#pragma once

#include "..\..\..\..\..\Data.h"
#include "..\..\..\..\..\KeyInput.h"


namespace StateNS {
namespace GameNS {
namespace GameMainNS{


class PlayerChild
{
public:
	virtual ~PlayerChild() {};
	virtual PlayerChild* update() = 0;
	virtual void draw() const = 0;
	const Vector2* getVector2() const { return p; }

protected:
	float speed;
	Vector2* p; //staticではないからキャラ変更のたびにdeleteしよう

	//あとで、ここら辺の共通の処理はPlayerChild.cppに書き直す
	void standardMove() 
	{
		int dx = 0;
		int dy = 0;

		if (Input_RIGHT())dx += (int)(speed * MyData::vectorRate);
		if (Input_LEFT())dx -= (int)(speed * MyData::vectorRate);

		//for Debug	
		//後で重力移動に書き換え
		if (Input_UP())dy -= (int)(speed * MyData::vectorRate);
		if (Input_DOWN())dy += (int)(speed * MyData::vectorRate);

		p->pos_x += dx;
		p->pos_y += dy;

		p->pos_x = max(0, min(MyData::MAP_WIDTH * MyData::vectorRate, p->pos_x));
		p->pos_y = max(0, min(MyData::MAP_HEIGHT * MyData::vectorRate, p->pos_y));
	};

};




}
}
}