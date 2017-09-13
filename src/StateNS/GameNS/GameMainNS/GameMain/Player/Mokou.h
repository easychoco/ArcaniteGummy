#pragma once

#include "PlayerChild.h"


namespace StateNS {
namespace GameNS {
namespace GameMainNS{


class Mokou : public PlayerChild
{
public:
	Mokou(int x, int y, int hp);
	Mokou(int, int);
	~Mokou();
	PlayerChild* update(const Stage*);

private:
	int attackTime;
	const int attackInterval = 10;//UŒ‚‚ÌŠÔŠu

	void initialize();
	void attack();
	void draw_other() const;
	virtual void loadImage() override;
	virtual int specialAction()override;
	//UŒ‚•û–@‚Ì“à•”ƒNƒ‰ƒX
	class Fire : public Attack
	{
	public:
		Fire(const PlayerChild*, int x, int y, int w, int h, bool direction);
		~Fire();
		void update();
		void setStatus(Vector2, int dx);
		void hittedAction();

	private:
		int mTime;

	};
};


}
}
}