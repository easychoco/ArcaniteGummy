#pragma once

#include "GimmickChild.h"



namespace StateNS {
	namespace GameNS {


		namespace GameMainNS {

			class Child;

			class Dossunn : public GimmickChild
			{
			public:
				Dossunn(Vector2);
				~Dossunn();
				void initialize();
				void update();
				void draw(const Vector2*) const;
				void apply(Character*);
				void move(int);
				bool isOverlap(int, int) const;
				bool onActiveArea(const Vector2*) const;
				Stage::ChipType getChipType() const;



			private:
				float dx;
				Vector2 pos;
				int mImage;
				int mTime;
				bool isMove;
			};




		}
	}
}
