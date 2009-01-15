#ifndef GAMEMAINSCENE_H_
#define GAMEMAINSCENE_H_

class GameMainScene : public GgafDx9LibStg::DefaultScene {

public:
	char _buf[20];
	GgafDx9LibStg::FontPlateActor* _pFontPlate_SCORE;








	Ggaf::GgafMainScene* _pStage01Scene;
	Ggaf::GgafMainScene* _pStage02Scene;
	Ggaf::GgafMainScene* _pStage03Scene;
	Ggaf::GgafMainScene* _pStage04Scene;
	Ggaf::GgafMainScene* _pStage05Scene;

	DWORD _dwFrame_ReadyStage01;
	DWORD _dwFrame_ReadyStage02;
	DWORD _dwFrame_ReadyStage03;
	DWORD _dwFrame_ReadyStage04;
	DWORD _dwFrame_ReadyStage05;
	bool _readyStage01Flg;
	bool _readyStage02Flg;
	bool _readyStage03Flg;
	bool _readyStage04Flg;
	bool _readyStage05Flg;

	GameMainScene(string prm_name);
	/**
	 * ��������
	 */
	void initialize();

	void readyStage01();
	void enableStage01();
	void readyStage02();
	void enableStage02();
	void readyStage03();
	void enableStage03();
	void readyStage04();
	void enableStage04();
	void readyStage05();
	void enableStage05();

	virtual void processBehavior();

	virtual void processFinal();

	virtual ~GameMainScene();
};

#endif /*GAMEMAINSCENE_H_*/
