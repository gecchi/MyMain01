#ifndef GAMESCENE_H_
#define GAMESCENE_H_
namespace MyStg2nd {

class GameScene : public GgafDx9LibStg::DefaultScene {

public:
	GameDemoScene* _pGameDemoScene;
	GameMainScene* _pGameMainScene;
	CommonScene* _pCommonScene;
	GameScene(const char* prm_name);
	/**
	 * èâä˙èàóù
	 */
	void initialize();

	virtual void processBehavior();

	virtual void processFinal();

	virtual ~GameScene();
};

}
#endif /*GAMESCENE_H_*/
