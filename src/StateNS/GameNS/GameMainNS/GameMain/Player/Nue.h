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
	PlayerChild* update(const StageChild*);
	virtual void draw() const override;

private:
	int attackTime;
	const int attackInterval = 10;//çUåÇÇÃä‘äu

	int mImageR[32];
	int mImageL[32];

	void initialize();
	void attack();
	virtual void draw_other() const override;
	virtual void loadImage() override;
	virtual void animation() override;
	void updateUFO(const StageChild*);

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
		int img1, img2;
		const Vector2* parent_p;

	};

	class UFO : public DynamicGimmickChild
	{
	public:
		UFO(int x, int y);

		~UFO();
		void initialize();
		void update(const StageChild*);
		void draw(const Vector2* camera) const;
		StageChild::ChipType getChipType() const { return StageChild::ChipType::TYPE_RIGID; };

		void apply(Character*);
		void hittedAction() override;
		void burnedAction() override;
		bool isOverlap(const Vector2*) const;
		bool onActiveArea(const Vector2*) const;

	private:
		int mImage;
		int mTime;
		bool isMove;
		enum Direction {
			RIGHT,
			LEFT,
			NONE
		};
		Direction direction;
		void loadImage();
		void move();
	};


	bool isUFO;
	UFO* ufo;
};


}
}
}