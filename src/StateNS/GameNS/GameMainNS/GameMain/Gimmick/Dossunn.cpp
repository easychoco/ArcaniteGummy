#include "Dossunn.h"
#include "..\Character.h"

namespace StateNS {
	namespace GameNS {
		namespace GameMainNS {


			Dossunn::Dossunn(Vector2 _pos)
			{
				initialize();

				pos = _pos;

				mImage = LoadGraph("Data/Image/Dossunn.png");
				assert(mImage != -1 && "どっすん画像読み込みエラー！");
			}

			Dossunn::~Dossunn()
			{

			}

			void Dossunn::initialize()
			{
				isActive = true;
				//dx = 1.0f;
				mTime = 0;
				isMove = false;
			}

			void Dossunn::update()
			{
				if (isMove && mTime<=150)
				{
					mTime++;
					move(mTime);
				}
				else 
				{
					mTime = 0;
					isMove = false;

				}
			}

			void Dossunn::move(int time) 
			{
				if(time<30)pos.raw_y += MyData::CHIP_WIDTH * 100;
				else pos.raw_y -= MyData::CHIP_WIDTH * 25;

				
			}

			void Dossunn::draw(const Vector2* _camera) const
			{
				//画面内にいなければreturn
				if (abs(pos.pos_x() - _camera->pos_x()) > 350000 || abs(pos.pos_y() - _camera->pos_y()) > 270000)return;


				int draw_x = 320 + (pos.pos_x() - _camera->pos_x()) / MyData::vectorRate;
				int draw_y = 240 + (pos.pos_y() - _camera->pos_y()) / MyData::vectorRate;

				//描画
				DrawRotaGraph(draw_x, draw_y, 1.0, 0.0, mImage, true);


			}


			void Dossunn::apply(Character* _character)
			{
				this->isMove = true;

			}

			bool Dossunn::isOverlap(int _sub_x, int _sub_y) const
			{
				return
					this->pos.x() / MyData::CHIP_WIDTH == _sub_x &&
					this->pos.y() / MyData::CHIP_HEIGHT == _sub_y;
			}

			bool Dossunn::onActiveArea(const Vector2* _player) const
			{
				return
					abs(this->pos.x() - _player->x()) <= MyData::CHIP_WIDTH * 5 &&
					abs(this->pos.y() - _player->y()) <= MyData::CHIP_WIDTH * 5;
			}

			Stage::ChipType Dossunn::getChipType() const
			{
				return Stage::ChipType::TYPE_RIGID;
			}

			//==============================================
			//内部プライベート関数
			//==============================================

			//そんなものはない



		}
	}
}