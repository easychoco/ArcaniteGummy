#pragma once

#include "..\GameMain.h"
#include "..\..\..\..\Data.h"


namespace StateNS {
namespace GameNS {

namespace GameMainNS{

class Child;

class System
{
public:
	System(int stagenum,int stageX,int stageY);
	~System();
	void initialize();
	void update(GameMain::HowStageMove);
	void draw(const Vector2* player) const;
	int getNowStage() const { return nowStage; }

	enum FilterType
	{
		TYPE_DARK,
		TYPE_NONE,
	};

	FilterType filter;

	void setFilter(FilterType _f) { this->f_type = _f; }


private:
	int nowStage;
	int stage_x;
	int stage_y;
	int stage_num;

	int img_DarkRing;

	FilterType f_type;
	void drawDarkFilter(const Vector2*, int radius) const;

	/*
	‚±‚ñ‚È‘åŠ|‚©‚è‚È‚±‚Æ‚¢‚ç‚È‚¢‚í
	class Filter
	{
	public:
		Filter(int _param) { this->param = _param; }
		virtual ~Filter() {};
		virtual void update() = 0;
		virtual void draw(const Vector2* player) const = 0;
		void setFilterParam(int _p) { this->param = _p; }
	private:
		int param;
	};

	class DarkFilter : public Filter
	{	//param‚Í‚Ç‚Ì”ÍˆÍ‚ð‚Ý‚¦‚é‚æ‚¤‚É‚·‚é‚©‚Ì”¼Œa
		DarkFilter(int param);
		~DarkFilter();
		void update();
		void draw(const Vector2* player) const;
	};

	Filter* filter;
	*/

};




}
}
}