#pragma once

#include "..\..\..\..\..\Data.h"
#include "EnemyChild.h"

namespace StateNS {
namespace GameNS {
namespace GameMainNS{

	
class Shot;


class Kaguya : public EnemyChild
{
public:
	Kaguya(int x, int y, int, int);
	~Kaguya();
	virtual void draw(const Vector2* camera) const override;
	void update(const StageChild* _stage, const Vector2* _camera);
	bool makeEnemy() const { return isMakingEnemy;}
	bool makeDark() const { return darkTime > 0; }
	void setMuteki(bool _muteki) { mutekiByEne = _muteki; }

	const int maxCreateEnemyNum = 3;

private:
	int mTime;
	int timeToNextMotion;
	int move_type;

	bool init_attacks;

	bool attack_vanish;
	bool attack_reflect;
	bool attack_spread;
	bool attack_dark;
	bool attack_enemy;

	void processReflect(const StageChild*, int&, int&);
	void processSpread(const StageChild*, int&, int&);
	void processEnemy(const StageChild*, int&, int&);

	const int maxHP;
	const Vector2 initial_pos;

	bool isMakingEnemy;
	bool mutekiByEne;


	const int maxDarkTime = 300;
	int darkTime;
	void setDark(int _darkTime) { darkTime = _darkTime; }

	int vanishTime = 0;

	bool imgLoad;
	int images[32];
	void loadImage();

	int dx = 4000;

	//CharacterÇÃä÷êî
	void hittedAction();

	//EnemychildÇÃä÷êî
	void move(const StageChild*, int& dx, int& dy);
	virtual void draw_other(const Vector2* camera)const override;

	void initialize();
	void initialize_attacks();

	//==========================================
	//Ç±Ç±Ç©ÇÁì‡ïîÉNÉâÉX
	//==========================================
	class Shot_reflect
	{
	public:
		Shot_reflect(const Vector2* pos, EnemyChild*);
		~Shot_reflect();
		void update(const Vector2* camera);
		void draw(const Vector2* camera) const;
		void addAttacks(vector<Attack*>&);
		void setStatus(const Vector2* pos, const Vector2* player);
		void setActive(bool);
		bool isActive() const { return this->mIsActive; }
		void checkActive(const StageChild*);

	private:
		int time;
		bool mIsActive;
		const int maxShotNum = 6;

		double getAngleToPlayer(const Vector2&);

		EnemyChild* parent = 0;
		const Vector2* player = 0;
		vector<Shot*> shots{};

		void initialize();
	};

	class Shot_spread
	{
	public:
		Shot_spread(const Vector2* pos, EnemyChild*);
		~Shot_spread();
		void update();
		void draw(const Vector2* camera) const;
		void addAttacks(vector<Attack*>&);
		void setStatus(const Vector2* pos);
		void setActive(bool);
		bool isActive() const { return this->mIsActive; }
		void checkActive(const StageChild*);

	private:
		int time;
		bool mIsActive;
		const int maxShotNum = 6;
		const int radius = 50000;

		EnemyChild* parent = 0;
		Vector2 center_pos;
		vector<Shot*> shots{};

		void initialize(const Vector2* pos);
	};

	vector<Shot_reflect*> reflects{};
	vector<Shot_spread*> spreads{};


	const int maxReflectNum = 3;
	const int maxSpreadNum = 3;

};

}
}
}