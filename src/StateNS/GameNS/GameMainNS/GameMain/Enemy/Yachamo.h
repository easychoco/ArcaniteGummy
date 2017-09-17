#pragma once

#include "..\..\..\..\..\Data.h"
#include "EnemyChild.h"
#include "..\Attack.h"

namespace StateNS {
namespace GameNS {
namespace GameMainNS{


class Yachamo : public EnemyChild
{
public:
	Yachamo(int x, int y);
	~Yachamo();

	void update(const Stage* _stage,const Vector2* _camera);

private:
	//Character‚ÌŠÖ”
	void hittedAction();

	//Enemychild‚ÌŠÖ”
	void move(const Stage*, int& dx, int& dy);
	void loadImage() { images = LoadGraph("Data/Image/Yachamo.png"); mImage = images; imgLoad = true; }


	void initialize();

	int images;
	bool imgLoad = false;
	
	int mTime;

	int moveSpeed;
	bool preOnGround;
	void attack(const Stage*);
	void draw_other(const Vector2*)const override;

	//UŒ‚•û–@‚Ì“à•”ƒNƒ‰ƒX
	class Fire : public Attack
	{
	public:
		Fire(const EnemyChild*, const Stage*, int x, int y, int dx);
		~Fire();
		void update();
		void setStatus(Vector2, int dx);
		void hittedAction();

	private:
		int dx;
		const Stage* stage;
	};

};




}
}
}