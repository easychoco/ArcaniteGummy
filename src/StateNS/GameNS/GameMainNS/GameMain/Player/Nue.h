#pragma once

#include "PlayerChild.h"
#include "..\Gimmick\DynamicGimmickChild.h"


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
	const int attackInterval = 10;//çUåÇÇÃä‘äu

	void initialize();
	void attack();
	void draw_other() const;
	virtual void loadImage() override;

	virtual int specialAction()override;
	void updateUFO(const Stage*);

	virtual bool onRigidBlock() const override { return isUFO && ufo->onActiveArea(p); }

	//çUåÇï˚ñ@ÇÃì‡ïîÉNÉâÉX
	class Spear : public Attack
	{
	public:
		Spear(const PlayerChild*, int x, int y, bool direction);
		~Spear();
		void update();

		void setStatus(Vector2, int dx);
		void hittedAction();

	private:
		int mTime;
		const Vector2* parent_p;

	};

	class UFO : public DynamicGimmickChild
	{
	public:
		UFO(int x, int y);

		~UFO();
		void initialize();
		void update(const Stage*);
		void draw(const Vector2* camera) const;
		Stage::ChipType getChipType() const { return Stage::ChipType::TYPE_RIGID; };

		void apply(Character*);
		void hittedAction() override;
		void burnedAction() override;
		bool isOverlap(const Vector2*) const;
		bool onActiveArea(const Vector2*) const;

	private:
		int mImage;
		int mTime;
		bool isMove;
		int direction;//0è„1âE2â∫3ç∂

		void loadImage();
		void move();
	};


	bool isUFO;
	UFO* ufo;
};


}
}
}