#pragma once

#include "..\..\..\..\..\Data.h"
#include "EnemyChild.h"
#include "..\Attack.h"

namespace StateNS {
namespace GameNS {
namespace GameMainNS{


class Pikachi : public EnemyChild
{
public:
	Pikachi(int x, int y);
	~Pikachi();

	void update(const StageChild* _stage,const Vector2* _camera);

private:
	//Characterの関数
	void hittedAction();

	//Enemychildの関数
	void move(const StageChild*, int& dx, int& dy);
	
	int images[8];
	void loadImage()
	{
		if (!imgLoad)LoadDivGraph("Data/Image/Pikachi.png", 8, 8, 1, 32, 32, images);
		for (int i = 0; i < 8; i++)mImage[i] = images[i];
		imgLoad = true;
	}


	void initialize();


	bool imgLoad = false;
	
	int mTime;

	int moveSpeed;
	bool preOnGround;
	void attack(const StageChild*);
	void draw_other(const Vector2*)const override;

	//攻撃方法の内部クラス
	class Thunder : public Attack
	{
	public:
		Thunder(const Character*, const StageChild*, int x, int y, int speed);
		~Thunder();
		void update();
		virtual void draw(const Vector2*) const override;
		void setStatus(Vector2, int speed);
		void hittedAction();

	private:
		int mTime;
		int dx;
		int dy;
		const StageChild* stage;
	};

};




}
}
}