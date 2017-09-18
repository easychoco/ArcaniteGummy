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
	int attackTime;
	const int attackInterval = 10;//UŒ‚‚ÌŠÔŠu

	bool isStoppingTime;
	int stoppingTime;
	const int maxStoppingTime = 120;//‚ğ~‚ß‚Ä‚¢‚ç‚ê‚éŠÔ(ƒtƒŒ[ƒ€”)

	void initialize();
	virtual void attack() override {}//‰¼‘z
	void attack(const Stage*);
	int getAttackDx() const;
	void processAttack(const Stage*);
	void processStopDynamics();

	void draw_other() const;
	virtual void loadImage() override;
	virtual int specialAction()override;
	//UŒ‚•û–@‚Ì“à•”ƒNƒ‰ƒX
	class Knife : public Attack
	{
	public:
		Knife(const PlayerChild*, const Stage*, int x, int y, int dx);
		~Knife();
		void update();

		void setStatus(Vector2, int dx);
		void hittedAction();

	private:
		int dx;
		const Stage* stage;
	};
};




}
}
}