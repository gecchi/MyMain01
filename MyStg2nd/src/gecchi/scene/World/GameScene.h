#ifndef GAMESCENE_H_
#define GAMESCENE_H_

class GameScene : public DefaultScene {

public:
	GameDemoScene* _pGameDemoScene;
	GameMainScene* _pGameMainScene;
	MyShipScene* _pMyShipScene;
	GameScene(string prm_name);
	/**
	 * ��������
	 */
	void initialize();

	virtual void processBehavior();

	virtual void processFinal();

	virtual ~GameScene();
};

#endif /*GAMESCENE_H_*/
