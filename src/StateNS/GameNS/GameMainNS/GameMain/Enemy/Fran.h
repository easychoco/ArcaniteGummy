#pragma once

#include "..\..\..\..\..\Data.h"
#include "EnemyChild.h"

namespace StateNS {
namespace GameNS {
namespace GameMainNS{

	
class Shot;


class Fran : public EnemyChild
{
public:
	Fran(int x, int y);
	~Fran();
	void update(const StageChild* _stage, const Vector2* _camera);
	
private:
	int mTime;
	bool init_attacks;

	int dx = 5000;

	//召喚された位置
	//ステージの真ん中にする
	const Vector2 initial_pos;

	static bool imgLoad;
	static int images[32];
	void loadImage();

	void processAttack(const StageChild*);
	void initialize();
	void initialize_attacks();


	//Characterの関数
	void hittedAction();

	//Enemychildの関数
	void move(const StageChild*, int& dx, int& dy);
	virtual void draw_other(const Vector2* camera)const override;



	//==========================================
	//ここから内部クラス
	//==========================================
	class StarBow
	{
	public:
		StarBow(const Vector2* pos, EnemyChild*);
		~StarBow();
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
		const int differ_x[6] = { -300, -200, -100, 100, 200, 300 };

		Vector2 center_pos;
		const EnemyChild* parent;
		vector<Shot*> shots;

		void initialize(const Vector2* pos);
	};

	class Wave495
	{
	public:
		Wave495(const Vector2* pos, EnemyChild*);
		~Wave495();
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

	class Kind4
	{
	public:
		Kind4(const Vector2* pos, EnemyChild*);
		~Kind4();
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
		const int maxShotNum = 4;

		EnemyChild* parent;
		vector<Shot*> shots;

		void initialize(const Vector2* pos);

		class Childs
		{
		public:
			Childs(int x, int y, EnemyChild*, int phase);
			~Childs();
			void update();
			void draw(const Vector2*) const;
			void addAttacks(vector<Attack*>&);
			void setStatus(int, int);
			void setActive(bool);
			bool isActive() const { return this->mIsActive; }
			void checkActive(const StageChild*);
		private:
			bool mIsActive;
			int time;
			int images[32];

			int dx;
			int dy;

			//初期位相
			const int init_phase;
			const int maxShotNum = 4;
			Vector2* p;
			vector<Shot*> shots;

			void setDiffer();
		};

		Childs* child1;
		Childs* child2;
		Childs* child3;
	};

	class LockOn
	{
	public:
		LockOn(EnemyChild*);
		~LockOn();
		void update();
		void draw(const Vector2* camera) const;
		void addAttacks(vector<Attack*>&);
		void setStatus(const Vector2* player);
		void setActive(bool);
		bool isActive() const { return this->mIsActive; }
		void checkActive(const StageChild*);

	private:
		int time;
		bool mIsActive;
		int image;
		
		Vector2 p;
		const Vector2* player;
		EnemyChild* parent;
		Shot* shot;
	};

	vector<StarBow*> stars;
	vector<Wave495*> waves;
	Kind4* kind4;
	LockOn* focus;

	const int maxStarBowNum = 5;
	const int maxWave495Num = 5;
};

}
}
}