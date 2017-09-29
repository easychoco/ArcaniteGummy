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
		Shot_around(Vector2* pos, EnemyChild*);
		~Shot_around();
		void update();
		void draw(Vector2* pos) const;
		void addAttacks(vector<Attack*>&);

		void setStatus(Vector2* pos);
		bool isActive;
		int time;
	private:
		Character* parent;
		Vector2* p;

		Shot* shot1;
		Shot* shot2;
		Shot* shot3;
		Shot* shot4;
		Shot* shot5;
		Shot* shot6;

		void initialize(Vector2* pos);
	};
};




}
}
}