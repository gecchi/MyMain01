#ifndef GAMEMAINSCENE_H_
#define GAMEMAINSCENE_H_

#define GAMEMAIN_PROG_INIT            1
#define GAMEMAIN_PROG_BEGIN           2
#define GAMEMAIN_PROG_STAGE_PLAY_BEGIN     3
#define GAMEMAIN_PROG_STAGE_PLAYING      4

namespace MyStg2nd {

class GameMainScene : public GgafDx9LibStg::DefaultScene {

public:
	char _buf[20];
	GgafDx9LibStg::FontPlateActor* _pFontPlate_SCORE;

	Stage01Scene* _pStage01;
	Stage02Scene* _pStage02;
	Stage03Scene* _pStage03;
	Stage04Scene* _pStage04;
	Stage05Scene* _pStage05;
	StageScene* _pSceneCannel;

	int _stage;
	GameMainScene(const char* prm_name);

	void setStage(int prm_stage) {
		_stage = prm_stage;
	}

	void cannelStage(int prm_stage);


	void initialize();

	virtual void processBehavior();

	virtual void processFinal();

	virtual ~GameMainScene();



//	//
//		void readyStage01();
//	//
//		void enableStage01();
//	//
//		void readyStage02();
//	//
//		void enableStage02();
//	//
//		void readyStage03();
//	//
//		void enableStage03();
//	//
//		void readyStage04();
//	//
//		void enableStage04();
//	//
//		void readyStage05();
//	//
//		void enableStage05();

//	//
//
//	//
//
//	//
//		DWORD _dwFrame_ReadyStage01;
//	//
//		DWORD _dwFrame_ReadyStage02;
//	//
//		DWORD _dwFrame_ReadyStage03;
//	//
//		DWORD _dwFrame_ReadyStage04;
//	//
//		DWORD _dwFrame_ReadyStage05;
//	//
//		bool _readyStage01Flg;
//	//
//		bool _readyStage02Flg;
//	//
//		bool _readyStage03Flg;
//	//
//		bool _readyStage04Flg;
//	//
//		bool _readyStage05Flg;

};

}
#endif /*GAMEMAINSCENE_H_*/
