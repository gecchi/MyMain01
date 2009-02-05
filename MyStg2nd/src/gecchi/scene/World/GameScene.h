#ifndef GAMESCENE_H_
#define GAMESCENE_H_


#define GAME_PROG_INIT           1
#define GAME_PROG_BEGIN          2
#define GAME_PROG_DEMO_BEGIN     3
#define GAME_PROG_DEMO_DISP      4
#define GAME_PROG_GAMEMAIN_BEGIN 5
#define GAME_PROG_GAMEMAIN_DISP  6


namespace MyStg2nd {

class GameScene : public GgafDx9LibStg::DefaultScene {

public:
	GameDemoScene* _pGameDemo;
	GameMainScene* _pGameMain;

	GgafDx9LibStg::DefaultScene _pSceneCannel;


	CommonScene* _pCommonScene;

	GameScene(const char* prm_name);
	virtual ~GameScene();

	void initialize();
	virtual void processBehavior();
	virtual void processFinal();

	void cannelGameDemo();

	void cannelGameMain();

};

}
#endif /*GAMESCENE_H_*/
