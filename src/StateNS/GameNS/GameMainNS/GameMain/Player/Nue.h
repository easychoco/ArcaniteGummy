#pragma once

#include "PlayerChild.h"
#include "..\Gimmick\UFO.h"


namespace StateNS {
namespace GameNS {
namespace GameMainNS {


class Nue : public PlayerChild
{
public:
	Nue(int x, int y, int hp);
	Nue(int, int);
	~Nue();
	PlayerChild* update(const Stage*);

private:
	int attackTime;
	const int attackInterval = 10;//UŒ‚‚ÌŠÔŠu

	void initialize();
	void attack();
	void draw_other() const;
	virtual void loadImage() override;

	virtual int specialAction() override;

	//UŒ‚•û–@‚Ì“à•”ƒNƒ‰ƒX
	class Spear : public Attack
	{
	public:
		Spear(int x, int y, int w, int h, bool direction);
		~Spear();
		void update();
		void setStatus(Vector2, int dx);
		void hittedAction();

	private:
		int mTime;

	};
	bool isUFO;
	UFO* ufo;
};


}
}
}