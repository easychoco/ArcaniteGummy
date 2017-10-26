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
	PlayerChild* update(const StageChild*);

private:
	int attackTime;
	const int attackInterval = 15;//UŒ‚‚ÌŠÔŠu

	bool isStoppingTime;
	int notStoppingTime;
	int stoppingTime;
	const int maxStoppingTime = 120;//‚ğ~‚ß‚Ä‚¢‚ç‚ê‚éŠÔ(ƒtƒŒ[ƒ€”)

	void initialize();
	virtual void attack() override {}//‰¼‘z
	void attack(const StageChild*);
	int getAttackDx() const;
	void processAttack(const StageChild*);
	void processStopDynamics();

	void draw_other() const;
	virtual void loadImage() override;
	virtual void animation() override;
	virtual StageChild::ChangeableCharacter getThisCharacter() override
	{
		return StageChild::ChangeableCharacter::CHARA_SAKUYA;
	}

	//UŒ‚•û–@‚Ì“à•”ƒNƒ‰ƒX
	class Knife : public Attack
	{
	public:
		Knife(const PlayerChild*, const StageChild*, int x, int y, int dx);
		virtual ~Knife() override;
		void update();

		void setStatus(Vector2, int dx);
		void hittedAction();

	private:
		int dx;
		bool up;
		const StageChild* stage = 0;
	};
};




}
}
}