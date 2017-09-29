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

	void update(const StageChild* _stage, const Vector2* _camera);
	
private:
	int images;
	bool imgLoad = false;
	int mTime;

	bool attack_around;



	//CharacterÇÃä÷êî
	void hittedAction();

	//EnemychildÇÃä÷êî
	void move(const StageChild*, int& dx, int& dy);
	virtual void draw_other(const Vector2* camera)const override;

	//TODO âÊëúç∑Çµë÷Ç¶
	void loadImage() { images = LoadGraph("Data/Image/balloon.png"); mImage = images; imgLoad = true; }
	void attack(const StageChild*);

	void initialize();

	class Shot_around
	{
	public:
		Shot_around(const Vector2* pos, EnemyChild*);
		~Shot_around();
		void update();
		void draw(const Vector2* pos) const;
		void addAttacks(vector<Attack*>&);

		void setStatus(const Vector2* pos);
		bool isActive;
		int time;

	private:
		const int radius = PLAYER_CHIP_HEIGHT_RATE() * 2;

		Character* parent;
		Vector2* p;

		Shot* shot1;
		Shot* shot2;
		Shot* shot3;
		Shot* shot4;
		Shot* shot5;
		Shot* shot6;

		void initialize(const Vector2* pos);
	};

	Shot_around* s_a;
};




}
}
}