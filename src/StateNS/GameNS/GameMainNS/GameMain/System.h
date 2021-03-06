#pragma once

#include "..\..\..\..\Data.h"
#include "..\GameMain.h"

namespace StateNS {
namespace GameNS {

namespace GameMainNS{

class Child;

class System
{
public:
	System();
	~System();
	void initialize();
	void update();
	void draw(const Vector2* player) const;

	void setFilter(FilterType _f) { this->f_type = _f; }


private:
	int img_DarkRing;

	FilterType f_type;
	void drawDarkFilter(const Vector2*, int radius) const;

	/*
	こんな大掛かりなこといらないわ
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
	{	//paramはどの範囲をみえるようにするかの半径
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