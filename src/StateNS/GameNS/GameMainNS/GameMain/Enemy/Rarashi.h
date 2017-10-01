#pragma once

#include "..\..\..\..\..\Data.h"
#include "EnemyChild.h"

namespace StateNS {
namespace GameNS {
namespace GameMainNS{


class Rarashi : public EnemyChild
{
public:
	Rarashi(int x, int y);
	~Rarashi();

	void update(const StageChild* _stage, const Vector2* _camera);


private:

	bool imgLoad = false;
	
	int mTime;

	int moveSpeed;
	bool preOnGround;

	//Character‚ÌŠÖ”
	void hittedAction();

	//Enemychild‚ÌŠÖ”
	void move(const StageChild*, int& dx, int& dy);
	int images[8];
	void loadImage()
	{
		if (!imgLoad)LoadDivGraph("Data/Image/Rarashi.png", 8, 8, 1, 32, 32, images);
		for (int i = 0; i < 8; i++)mImage[i] = images[i];
		imgLoad = true;
	}


	void initialize();
};




}
}
}