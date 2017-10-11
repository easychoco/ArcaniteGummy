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
	void draw(const Vector2* camera) const;
	void update(const StageChild* _stage, const Vector2* _camera);
	
private:
	int mTime;
	bool init_attacks;

	static bool imgLoad;
	static int images[32];
	void loadImage();

	//CharacterÇÃä÷êî
	void hittedAction();

	//EnemychildÇÃä÷êî
	void move(const StageChild*, int& dx, int& dy);
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

	class Bombing
	{
	public:
		Bombing(const Vector2* pos, EnemyChild*);
		~Bombing();
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

		Vector2 center_pos;
		const EnemyChild* parent;
		vector<Shot*> shots;

		void initialize(const Vector2* pos);
	};

	vector<Shot_3way*> shot3;


	const int maxShot3Num = 3;

};

}
}
}