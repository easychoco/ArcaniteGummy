#include "MusicRoom.h"
#include "StateParent.h"
#include "..\Data.h"
#include "..\KeyInput.h"
#include "Title.h"


namespace StateNS{



MusicRoom::MusicRoom()
{
	initialize();
}

MusicRoom::~MusicRoom()
{
	sound->deleteSound("titlebgm2");
	sound->deleteSound("boss1");
	sound->deleteSound("boss2");
	sound->deleteSound("boss3");
	sound->deleteSound("boss4");
	sound->deleteSound("boss5");
	sound->deleteSound("bgm2");
	sound->deleteSound("bgm3");
	sound->deleteSound("bgm4");
	DeleteGraph(*images);
}

void MusicRoom::initialize()
{
	sound->stopAllSound();
	sound->setSound("Data/Sound/OP.wav", "titlebgm2");
	sound->setSound("Data/Sound/Invisible_Full_Moon.wav", "boss1");
	sound->setSound("Data/Sound/Ousa-sama3.wav", "bgm2");
	sound->setSound("Data/Sound/Pure_Furies.wav", "boss2");
	sound->setSound("Data/Sound/Phantom_Ship.wav", "bgm3");
	sound->setSound("Data/Sound/husi.wav", "boss3");
	sound->setSound("Data/Sound/hyakunen.wav", "bgm4");
	sound->setSound("Data/Sound/uno-en.wav", "boss4");
	sound->setSound("Data/Sound/taketori.wav", "boss5");


	LoadDivGraph("Data/Image/Character/chip_mokou.png", 32, 8, 4, 32, 64, images, TRUE);
	assert(*images != -1 && "自機画像読み込みエラー");
	time = 0;

	dx = 0;
	draw_x = 50;
	direction = false;
	animeNum = 0;
	prePushUP = true;
	prePushDOWN = true;
	prePushOK = true;
	nowSelect = 0;

}

Child* MusicRoom::update(GrandParent* parent)
{
	Child* next = this;
	if (Input_NO())next = new StateNS::Title(2,1);


	if (Input_UP() && !prePushUP)nowSelect = (nowSelect + 8) % 9;
	else if (Input_DOWN() && !prePushDOWN)nowSelect = (nowSelect + 1) % 9;


	if (Input_OK() && !prePushOK) 
	{
		sound->stopAllSound();
		switch (nowSelect) 
		{
		case 0:sound->playSound("titlebgm2"); break;
		case 1:sound->playSound("boss1"); break;
		case 2:sound->playSound("bgm2"); break;
		case 3:sound->playSound("boss2"); break;
		case 4:sound->playSound("bgm3"); break;
		case 5:sound->playSound("boss3"); break;
		case 6:sound->playSound("bgm4"); break;
		case 7:sound->playSound("boss4"); break;
		case 8:sound->playSound("boss5"); break;
		}
	
	}


	charmove();
	time++;

	prePushUP = Input_UP();
	prePushDOWN = Input_DOWN();
	prePushOK = Input_OK();

	return next;
}

void MusicRoom::charmove()
{
	animeNum=8 + (time / 10) % 4;
	if (Input_LEFT())direction = true;
	else if (Input_RIGHT())direction = false;
	else {
		animeNum = 0;
		return;
	}
	int temp_x = direction ? -2 : 2;
	draw_x = max(draw_x + temp_x, 16);
	draw_x = min(draw_x + temp_x, 624);

}


void MusicRoom::draw() const
{
	DrawFormatString(0, 0, WHITE, "musicroom Xで戻れるよ");
	DrawFormatString(30, 30, DARKGLAY, "タイトル画面");
	DrawFormatString(30, 60, DARKGLAY, "ステージ1ボス：狂気の瞳　～ Invisible Full Moon");
	DrawFormatString(30, 90, DARKGLAY, "ステージ2道中：お宇佐さまの素い幡");
	DrawFormatString(30, 120, DARKGLAY, "ステージ2ボス：ピュアヒューリーズ　～ 心の在処");
	DrawFormatString(30, 150, DARKGLAY, "ステージ3道中：幽霊客船と時空を超えた旅");
	DrawFormatString(30, 180, DARKGLAY, "ステージ3ボス：月まで届け、不死の煙");
	DrawFormatString(30, 210, DARKGLAY, "ステージ4道中：魔法少女達の百年祭");
	DrawFormatString(30, 240, DARKGLAY, "ステージ4ボス：U.N.オーエンは彼女なのか？");
	DrawFormatString(30, 270, DARKGLAY, "ステージ5ボス：竹取飛翔　～ Lunatic Princess");


	switch (nowSelect)
	{
	case  0: DrawFormatString(30, 30, WHITE, "タイトル画面"); break;
	case  1: DrawFormatString(30, 60, WHITE, "ステージ1ボス：狂気の瞳　～ Invisible Full Moon"); break;
	case  2: DrawFormatString(30, 90, WHITE, "ステージ2道中：お宇佐さまの素い幡"); break;
	case  3: DrawFormatString(30, 120, WHITE, "ステージ2ボス：ピュアヒューリーズ　～ 心の在処"); break;
	case  4: DrawFormatString(30, 150, WHITE, "ステージ3道中：幽霊客船と時空を超えた旅"); break;
	case  5: DrawFormatString(30, 180, WHITE, "ステージ3ボス：月まで届け、不死の煙"); break;
	case  6: DrawFormatString(30, 210, WHITE, "ステージ4道中：魔法少女達の百年祭"); break;
	case  7: DrawFormatString(30, 240, WHITE, "ステージ4ボス：U.N.オーエンは彼女なのか？"); break;
	case  8: DrawFormatString(30, 270, WHITE, "ステージ5ボス：竹取飛翔　～ Lunatic Princess"); break;
	}

	DrawRotaGraph(draw_x, 350, 1.0, 0.0, images[animeNum], true, direction);

}




}