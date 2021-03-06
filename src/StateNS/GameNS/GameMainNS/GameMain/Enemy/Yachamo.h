#pragma once

#include "..\..\..\..\..\Data.h"
#include "EnemyChild.h"
#include "..\Attack.h"

namespace StateNS {
namespace GameNS {
namespace GameMainNS{


class Yachamo : public EnemyChild
{
public:
	Yachamo(int x, int y);
	~Yachamo();

	void update(const StageChild* _stage,const Vector2* _camera);

private:
	int mTime;

	static bool imgLoad;
	static int images[8];
	void loadImage();

	//Characterの関数
	void hittedAction();

	//Enemychildの関数
	void move(const StageChild*, int& dx, int& dy);


	void initialize();
	virtual void setChildActive(bool _active) const override { for (auto& a : attacks)a->setActive(_active); }

	int moveSpeed;
	bool preOnGround;
	void attack(const StageChild*);
	void draw_other(const Vector2*)const override;

	//攻撃方法の内部クラス
	class Fire : public Attack
	{
	public:
		Fire(const EnemyChild*, const StageChild*, int x, int y, int dx);
		~Fire();
		void update();
		void setStatus(Vector2, int dx);
		void hittedAction();

	private:
		static bool imgLoad_fire;
		static int image;
		int dx;
		const StageChild* stage = 0;
	};

};





}
}
}