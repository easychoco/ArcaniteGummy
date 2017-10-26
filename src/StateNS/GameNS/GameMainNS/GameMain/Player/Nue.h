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
	virtual bool hasAdditionalGimmick() const override { return true; }
	virtual DynamicGimmickChild* getAdditionalGimmick() const override { return ufo; }


private:
	int attackTime;
	const int attackInterval = 10;//çUåÇÇÃä‘äu
	bool preSit;

	int mImageR[32];
	int mImageL[32];

	void initialize();
	void attack();
	virtual void draw_other() const override;
	virtual void loadImage() override;
	virtual void animation() override;
	virtual StageChild::ChangeableCharacter getThisCharacter() override
	{
		return StageChild::ChangeableCharacter::CHARA_NUE;
	}

	void updateUFO(const StageChild*);

	virtual bool onRigidBlock() const override { return ufo->isActive && ufo->onActiveArea(p); }

	//çUåÇï˚ñ@ÇÃì‡ïîÉNÉâÉX
	class Spear : public Attack
	{
	public:
		Spear(const PlayerChild*, int x, int y, bool direction);
		virtual ~Spear() override;
		void update();

		void setStatus(Vector2, int dx);
		void hittedAction();

	private:
		int mTime;
		int img1, img2;
		const Vector2* parent_p = 0;

	};

	class UFO : public DynamicGimmickChild
	{
	public:
		UFO();

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

		void setStatus(int, int);

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

	static UFO* ufo;
	bool createdUFO;
};


}
}
}