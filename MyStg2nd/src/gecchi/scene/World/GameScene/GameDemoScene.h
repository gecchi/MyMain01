#ifndef GAMEDEMOSCENE_H_
#define GAMEDEMOSCENE_H_

class GameDemoScene : public DefaultScene {

public:

	GameDemoScene(string prm_name);
	/**
	 * ‰Šúˆ—
	 */
	void initialize();

	virtual void processBehavior();

	virtual void processFinal();

	virtual ~GameDemoScene();
};

#endif /*GAMEDEMOSCENE_H_*/
