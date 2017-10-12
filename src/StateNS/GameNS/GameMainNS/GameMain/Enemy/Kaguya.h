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
	void draw(const Vector2* camera) const;
	void update(const StageChild* _stage, const Vector2* _camera);
	bool makeEnemy() const { return isMakingEnemy;}
	bool makeDark() const { return makeItDark; }
	void setMuteki(bool _muteki) { this->hpController.isMuteki = _muteki; }
	
private:
	int mTime;
	bool init_attacks;

	bool isMakingEnemy;
	bool makeItDark;
	bool isVanish;

	static bool imgLoad;
	static int images[32];
	void loadImage();

	//Character‚ÌŠÖ”
	void hittedAction();

	//Enemychild‚ÌŠÖ”
	void move(const StageChild*, int& dx, int& dy);
	virtual void draw_other(const Vector2* camera)const override;

	void initialize();


	//==========================================
	//‚±‚±‚©‚ç“à•”ƒNƒ‰ƒX
	//==========================================


};

}
}
}