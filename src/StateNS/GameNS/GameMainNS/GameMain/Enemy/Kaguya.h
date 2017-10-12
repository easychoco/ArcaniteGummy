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
	Kaguya(int x, int y);
	~Kaguya();
	virtual void draw(const Vector2* camera) const override;
	void update(const StageChild* _stage, const Vector2* _camera);
	bool makeEnemy() const { return isMakingEnemy;}
	bool makeDark() const { return darkTime > 0; }
	void setMuteki(bool _muteki) { this->hpController.isMuteki = _muteki; }

	const int maxCreateEnemyNum = 3;

private:
	int mTime;
	bool init_attacks;

	bool isMakingEnemy;

	const int maxDarkTime = 300;
	int darkTime;

	int vanishTime = 0;

	static bool imgLoad;
	static int images[32];
	void loadImage();

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

		EnemyChild* parent;
		const Vector2* player;
		vector<Shot*> shots;

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

		EnemyChild* parent;
		Vector2 center_pos;
		vector<Shot*> shots;

		void initialize(const Vector2* pos);
	};

	vector<Shot_reflect*> reflects;
	vector<Shot_spread*> spreads;


	const int maxReflectNum = 3;
	const int maxSpreadNum = 3;

};

}
}
}