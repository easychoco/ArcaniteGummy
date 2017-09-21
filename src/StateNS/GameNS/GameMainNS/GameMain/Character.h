#pragma once

#include "..\..\..\..\Data.h"

#include "DynamicObject.h"
#include "HPController.h"
#include "Stages\StageChild.h"


namespace StateNS {
namespace GameNS {
namespace GameMainNS{

//é©ã@Ç∆ìGÇ≈ã§í Ç∑ÇÈçsìÆ
	class Character : public DynamicObject
	{
	public:
		Character(int hp, int x, int y, int w, int h, float jump, int jumpCount);
		Character(int hp, int x, int y, int w, int h, bool isPlayer, float jump, int jumpCount);
		virtual ~Character();
		virtual void hittedAction() = 0;
		void moveCharacter(float _dx, float _dy);
		void warpCharacter(int raw_x, int raw_y);

		HPController hpController;
		bool isPlayer;
		bool damaged;
		int damagedTime;

	protected:
		int next_dx;
		int next_dy;
		int width;
		int height;

		int getTopDiffer(const StageChild*, const int dy, bool moveLeft) const;
		int getBottomDiffer(const StageChild*, const int dy, bool moveLeft) const;
		int getHorizontalDiffer(const StageChild*, const int dx, bool moveUp) const;
};



}
}
}