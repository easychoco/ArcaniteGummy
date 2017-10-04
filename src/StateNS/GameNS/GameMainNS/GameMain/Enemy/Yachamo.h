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

	void update(const StageChild* _stage,const Vector2* _camera);

private:
	int mTime;

	static bool imgLoad;
	static int images[8];
	void loadImage();

	//Character‚ÌŠÖ”
	void hittedAction();

	//Enemychild‚ÌŠÖ”
	void move(const StageChild*, int& dx, int& dy);


	void initialize();



	int moveSpeed;
	bool preOnGround;
	void attack(const StageChild*);
	void draw_other(const Vector2*)const override;

	//UŒ‚•û–@‚Ì“à•”ƒNƒ‰ƒX
	class Fire : public Attack
	{
	public:
		Fire(const EnemyChild*, const StageChild*, int x, int y, int dx);
		~Fire();
		void update();
		void setStatus(Vector2, int dx);
		void hittedAction();

	private:
		int dx;
		const StageChild* stage;
	};

};





}
}
}