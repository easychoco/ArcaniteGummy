#pragma once

#include "..\..\..\..\..\Data.h"
#include "EnemyChild.h"

namespace StateNS {
namespace GameNS {
namespace GameMainNS{

	
class Shot;


class Nue_Boss : public EnemyChild
{
public:
	Nue_Boss(int x, int y);
	~Nue_Boss();
	void update(const StageChild* _stage, const Vector2* _camera);
	
private:
	int mTime;
	bool init_attacks;
	const Vector2 initial_pos;

	bool attack_3way;
	bool attack_bomb;
	bool attack_flower;

	int move_type;

	int dx;
	int dy;

	static bool imgLoad;
	static int images[32];
	void loadImage();

	//CharacterÇÃä÷êî
	void hittedAction();

	//EnemychildÇÃä÷êî
	void move(const StageChild*, int& dx, int& dy);
	void setMotion(const StageChild*, int& _dx, int& _dy);
	virtual void draw_other(const Vector2* camera)const override;
	void processAttack(const StageChild* _stage);
	void initialize();
	void initialize_attacks();


	//==========================================
	//Ç±Ç±Ç©ÇÁì‡ïîÉNÉâÉX
	//==========================================
	class Shot_3way
	{
	public:
		Shot_3way(const Vector2* pos, EnemyChild*);
		~Shot_3way();
		void update();
		void draw(const Vector2* camera) const;
		void addAttacks(vector<Attack*>&);
		void setStatus(const Vector2* pos, bool direction);
		void setActive(bool);
		bool isActive() const { return this->mIsActive; }
		void checkActive(const StageChild*);

	private:
		int time;
		bool mIsActive;

		const EnemyChild* parent;
		vector<Shot*> shots;

		void initialize(const Vector2* pos);
	};

	class Bombing : public Attack
	{
	public:
		Bombing(const Vector2* pos, EnemyChild*);
		~Bombing();
		void update();
		void draw(const Vector2* camera) const;
		void setStatus(Vector2 pos, int direction) override;
		void hittedAction() override {};
		void checkOnGround(const StageChild*);

	private:
		int time;
		int dx;
		int dy;

		bool onGround;
		int image;
		int img_fire[3];

		void initialize(const Vector2* pos);
	};

	class FireFlower
	{
	public:
		FireFlower(EnemyChild*);
		~FireFlower();
		void update();
		void draw(const Vector2* camera) const;
		void setStatus(Vector2 pos, bool);
		void addAttacks(vector<Attack*>&);
		bool isActive() const { return this->mIsActive; }
		void setActive(bool);
		void checkActive();
		void checkOnGround(const StageChild*);

	private:
		int time;
		bool mIsActive;
		int image;
		int dx;
		int dy;
		Vector2* p;
		
		const EnemyChild* parent;
		const int maxBombNum = 4;
		vector<Bombing*> f_bombs;

		void initialize(EnemyChild*);
	};

	vector<Shot_3way*> shot3;
	vector<Bombing*> bombs;
	FireFlower* flower;


	const int maxShot3Num = 3;
	const int maxBombNum = 3;

};

}
}
}