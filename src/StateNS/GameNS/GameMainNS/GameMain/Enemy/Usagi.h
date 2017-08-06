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

	void update();
	void draw(const Vector2*) const;

private:

	//CharacterÇÃä÷êî
	void damagedAction();

	void initialize();
	void loadImage() { mImage = LoadGraph("Data/Image/usagi.png"); imgLoad = true; }

	int mImage;
	bool imgLoad = false;
	
	int mTime;
	bool mDirection;
};




}
}
}