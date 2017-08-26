#pragma once

#include "PlayerChild.h"


namespace StateNS {
namespace GameNS {
namespace GameMainNS{


class Sakuya : public PlayerChild
{
public:
	Sakuya(int, int);
	Sakuya(int, int, int);
	~Sakuya();
	PlayerChild* update(const Stage*);

private:
	void initialize();
	void attack();
	void draw_other() const;
	virtual void loadImage() override;

	//UŒ‚•û–@‚Ì“à•”ƒNƒ‰ƒX
	class Knife : public Attack
	{
	public:
		Knife(int x, int y, int w, int h, int dx);
		~Knife();
		void update();
		void setStatus(Vector2, int dx);
		void hittedAction();

	private:
		int dx;
	};
};




}
}
}