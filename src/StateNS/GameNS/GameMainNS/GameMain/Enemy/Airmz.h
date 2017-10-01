#pragma once

#include "..\..\..\..\..\Data.h"
#include "EnemyChild.h"

namespace StateNS {
namespace GameNS {
namespace GameMainNS{


class Airmz : public EnemyChild
{
public:
	Airmz(int x, int y);
	~Airmz();

	void update(const StageChild* _stage, const Vector2* _camera);


private:

	bool imgLoad = false;
	int mTime;

	//Characterの関数
	void hittedAction();

	//Enemychildの関数
	void move(const StageChild*, int& dx, int& dy);
	int images[8];
	void loadImage()
	{
		if (!imgLoad)LoadDivGraph("Data/Image/Airmz.png", 8, 8, 1, 32, 32, images);
		for (int i = 0; i < 8; i++)mImage[i] = images[i];
		imgLoad = true;
	}


	void attack(const StageChild*);
	void draw_other(const Vector2*)const override;

	void initialize();


	//攻撃方法の内部クラス
	class Bomb : public Attack
	{
	public:
		Bomb(const Character*, const StageChild*, int x, int y, int speed);
		~Bomb();
		void update();
		virtual void draw(const Vector2*) const override;
		void setStatus(Vector2, int speed);
		void hittedAction();

	private:
		int mTime;
		int dx;
		int dy;
		int sy;//初期座標

		const StageChild* stage;
	};

};




}
}
}