#ifndef STAGE01MAINSCENE_H_
#define STAGE01MAINSCENE_H_

class Stage01MainScene : public GgafDx9LibStg::DefaultScene {

	GgafDx9Core::GgafDx9Bgm* _bgm_st1;

public:

	Stage01MainScene(string prm_name);
	/**
	 * ‰Šúˆ—
	 */
	void initialize();

	virtual void processBehavior();

	virtual void processFinal();


	virtual ~Stage01MainScene();
};

#endif /*STAGE01MAINSCENE_H_*/
