#ifndef GAMEDEMOSCENE_H_
#define GAMEDEMOSCENE_H_

class GameDemoScene : public DefaultScene {

public:

	FontPlateActor* _pFontPlate01;
	FontPlateActor* _pFontPlate02;

	GameDemoScene(string prm_name);
	/**
	 * èâä˙èàóù
	 */
	void initialize();

	virtual void processBehavior();

	virtual void processFinal();

	virtual ~GameDemoScene();
};

#endif /*GAMEDEMOSCENE_H_*/
