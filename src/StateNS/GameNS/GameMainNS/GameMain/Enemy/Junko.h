#pragma once

#include "..\..\..\..\..\Data.h"
#include "EnemyChild.h"

namespace StateNS {
namespace GameNS {
namespace GameMainNS{

	
class Shot;


class Junko : public EnemyChild
{
public:
	Junko(int x, int y);
	~Junko();
	void draw(const Vector2* camera) const;
	void update(const StageChild* _stage, const Vector2* _camera);
	
private:
	int images;
	int mTime;

	bool init_attacks;


	//Characterの関数
	void hittedAction();

	//Enemychildの関数
	void move(const StageChild*, int& dx, int& dy);
	virtual void draw_other(const Vector2* camera)const override;

	//TODO 画像差し替え
	void loadImage() { images = LoadGraph("Data/Image/balloon.png"); mImage2 = images; }
	void attack(const StageChild*);

	void initialize();


	//==========================================
	//ここから内部クラス
	//==========================================
	class Shot_around
	{
	public:
		Shot_around(const Vector2* pos, EnemyChild*);
		~Shot_around();
		void update();
		void draw(const Vector2* pos) const;
		void addAttacks(vector<Attack*>&);
		void setStatus(const Vector2* pos);
		void setActive(bool);
		bool isActive() const { return this->mIsActive; }
		void checkActive(const Vector2*);


	private:
		int time;
		const int radius = PLAYER_CHIP_HEIGHT_RATE() * 2;
		bool mIsActive;

		Character* parent;

		Shot* shot1;
		Shot* shot2;
		Shot* shot3;
		Shot* shot4;
		Shot* shot5;
		Shot* shot6;

		void initialize(const Vector2* pos);
	};

	class Shot_cycle
	{
	public:
		Shot_cycle(const Vector2* pos, EnemyChild*);
		~Shot_cycle();
		void update();
		void draw(const Vector2* pos) const;
		void addAttacks(vector<Attack*>&);
		void setStatus(const Vector2* pos);
		void setActive(bool);
		bool isActive() const { return this->mIsActive; }
		void checkActive(const Vector2*);
		
	private:
		int time;
		float angle;
		int radius;
		const int first_radius = 2000;
		bool mIsActive;

		Character* parent;
		const Vector2* center_pos;

		Shot* shot1;
		Shot* shot2;
		Shot* shot3;
		Shot* shot4;
		Shot* shot5;
		Shot* shot6;

		void initialize(const Vector2* pos);
	};


	Shot_around* s_a;
	Shot_cycle* s_c;

};




}
}
}