#ifndef GAMEDEMOSCENE_H_
#define GAMEDEMOSCENE_H_
namespace MyStg2nd {

class GameDemoScene : public GgafDx9LibStg::DefaultScene {

public:

	GgafDx9LibStg::FontPlateActor* _pFontPlate01;
	GgafDx9LibStg::FontPlateActor* _pFontPlate02;

	GameDemoScene(char* prm_name);
	/**
	 * èâä˙èàóù
	 */
	void initialize();

	virtual void processBehavior();

	virtual void processFinal();

	virtual ~GameDemoScene();
};

}
#endif /*GAMEDEMOSCENE_H_*/
