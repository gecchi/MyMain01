#ifndef GAMEDEMOSCENE_H_
#define GAMEDEMOSCENE_H_

#define GAMEDEMO_PROG_INIT            1
#define GAMEDEMO_PROG_BEGIN           2
#define GAMEDEMO_PROG_TITLE_BEGIN     3
#define GAMEDEMO_PROG_TITLE_DISP      4
#define GAMEDEMO_PROG_DEMOPLAY_BEGIN  5
#define GAMEDEMO_PROG_DEMOPLAY_DISP   6
#define GAMEDEMO_PROG_RANKING_BEGIN   7
#define GAMEDEMO_PROG_RANKING_DISP    8
#define GAMEDEMO_PROG_GAMESTART_BEGIN 9
#define GAMEDEMO_PROG_GAMESTART_AFTER 10

namespace MyStg2nd {

class GameDemoScene : public GgafDx9LibStg::DefaultScene {

public:

	GgafDx9LibStg::FontPlateActor* _pFontPlate01;
	GgafDx9LibStg::FontPlateActor* _pFontPlate02;

	GameDemoScene(const char* prm_name);
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
