#pragma once

#include "..\..\..\..\..\Data.h"
#include "EnemyChild.h"
#include "..\Attack.h"

namespace StateNS {
namespace GameNS {
namespace GameMainNS{


class Pikachi : public EnemyChild
{
public:
	Pikachi(int x, int y);
	~Pikachi();

	void update(const StageChild* _stage,const Vector2* _camera);

private:
	//Character‚ÌŠÖ”
	void hittedAction();

	//Enemychild‚ÌŠÖ”
	void move(const StageChild*, int& dx, int& dy);
	
	void loadImage() { images = LoadGraph("Data/Image/Pikachi.png"); mImage = images; imgLoad = true; }


	void initialize();

	int images;
	bool imgLoad = false;
	
	int mTime;

	int moveSpeed;
	bool preOnGround;
	void attack(const StageChild*);
	void draw_other(const Vector2*)const override;

	//UŒ‚•û–@‚Ì“à•”ƒNƒ‰ƒX
	class Thunder : public Attack
	{
	public:
		Thunder(const Character*, const StageChild*, int x, int y, int speed);
		~Thunder();
		void update();
		virtual void draw(const Vector2*) const override;
		void setStatus(Vector2, int speed);
		void hittedAction();

	private:
		int mTime;
		int dx;
		int dy;
		const StageChild* stage;
	};

};




}
}
}