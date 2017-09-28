#pragma once

#include "..\..\..\..\..\Data.h"
#include "EnemyChild.h"

namespace StateNS {
namespace GameNS {
namespace GameMainNS{


//ジャンプ移動の間隔(フレーム)
//大きくすると移動にかかる時間が長くなる
//大きくすると移動の距離も大きくなる
constexpr int jump_interval = 60;
static_assert(jump_interval > 5, "A variable \'jump_interval\' is Too small");

class Reisen : public EnemyChild
{
public:
	Reisen(int x, int y);
	~Reisen();

	void update(const StageChild* _stage, const Vector2* _camera);


private:
	int images;
	bool imgLoad = false;
	int mTime;

	bool nowMoving;

	//Characterの関数
	void hittedAction();

	//Enemychildの関数
	void move(const StageChild*, int& dx, int& dy);
	virtual void draw_other(const Vector2* camera)const override;

	//TODO 画像差し替え
	void loadImage() { images = LoadGraph("Data/Image/balloon.png"); mImage = images; imgLoad = true; }
	void attack(const StageChild*);

	void initialize();

	class Shot : public Attack
	{
	public:
		Shot(const EnemyChild*, const StageChild*, const Vector2* player, int x, int y);
		~Shot();
		void update();
		virtual void draw(const Vector2*) const override;
		void setStatus(Vector2, int);
		void hittedAction();

	private:
		int time;
		int dx;
		bool nowFast;
		const StageChild* stage;
		const Vector2* player;

		const int fast_speed = 10 * vectorRate;
		const int slow_speed =  2 * vectorRate;

		void initialize();
	};

	vector<Shot*> shots;

};




}
}
}