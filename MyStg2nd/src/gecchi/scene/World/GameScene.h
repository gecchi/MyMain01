#ifndef GAMESCENE_H_
#define GAMESCENE_H_

class GameScene : public GgafDx9LibStg::DefaultScene {

public:
	GameDemoScene* _pGameDemoScene;
	GameMainScene* _pGameMainScene;
	CommonScene* _pCommonScene;
	GameScene(string prm_name);
	/**
	 * èâä˙èàóù
	 */
	void initialize();

	virtual void processBehavior();

	virtual void processFinal();

	virtual ~GameScene();
};

#endif /*GAMESCENE_H_*/
