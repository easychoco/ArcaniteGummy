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
	PlayerChild* update(const StageChild*);

private:
	int attackTime;
	const int attackInterval = 10;//UŒ‚‚ÌŠÔŠu

	void initialize();
	void attack();
	void draw_other() const;
	virtual void loadImage() override;
	virtual void animation() override;
	virtual StageChild::ChangeableCharacter getThisCharacter() override
	{
		return StageChild::ChangeableCharacter
			::CHARA_MOKOU;
	}

	//UŒ‚•û–@‚Ì“à•”ƒNƒ‰ƒX
	class Fire : public Attack
	{
	public:
		Fire(const PlayerChild*, int x, int y, bool *direction);
		~Fire();
		void update();

		void setStatus(Vector2, int dx);
		void hittedAction();

	private:
		bool up;
		int images[3];
		int images2[3];
		int mTime;
		const bool *direction;
	};
};


}
}
}