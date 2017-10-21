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
	//void draw(const Vector2* camera) const;
	void update(const StageChild* _stage, const Vector2* _camera);
	
private:
	int mTime;
	bool init_attacks;

	bool attack_around;
	bool attack_cycle;

	const int maxHP;
	const int radius = 4000;

	int images[32];
	void loadImage();

	//CharacterÇÃä÷êî
	void hittedAction();

	//EnemychildÇÃä÷êî
	void move(const StageChild*, int& dx, int& dy);
	virtual void draw_other(const Vector2* camera) const override;
	void attack(const StageChild*);
	void initialize();

	//void setMotion();

	//==========================================
	//Ç±Ç±Ç©ÇÁì‡ïîÉNÉâÉX
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
		const int radius = PLAYER_CHIP_HEIGHT_RATE() * 5 / 2;
		bool mIsActive;

		Character* parent = 0;

		Shot* shot1 = 0;
		Shot* shot2 = 0;
		Shot* shot3 = 0;
		Shot* shot4 = 0;
		Shot* shot5 = 0;
		Shot* shot6 = 0;

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

		Character* parent = 0;
		const Vector2* center_pos = 0;

		Shot* shot1 = 0;
		Shot* shot2 = 0;
		Shot* shot3 = 0;
		Shot* shot4 = 0;
		Shot* shot5 = 0;
		Shot* shot6 = 0;

		void initialize(const Vector2* pos);
	};


	Shot_around* s_a = 0;
	Shot_cycle* s_c = 0;

};

}
}
}