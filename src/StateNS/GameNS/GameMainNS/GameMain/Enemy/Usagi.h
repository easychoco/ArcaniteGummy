#pragma once

#include "..\..\..\..\..\Data.h"
#include "EnemyChild.h"

namespace StateNS {
namespace GameNS {
namespace GameMainNS{


class Usagi : public EnemyChild
{
public:
	Usagi(int x, int y);
	~Usagi();

	void update(const Stage* _stage);

private:
	//Character�̊֐�
	void hittedAction();

	//Enemychild�̊֐�
	void move(const Stage*, int& dx, int& dy);
	void loadImage() { images = LoadGraph("Data/Image/usagi.png"); mImage = images; imgLoad = true; }


	void initialize();

	int images;
	bool imgLoad = false;
	
	int mTime;

	int moveSpeed;
};




}
}
}