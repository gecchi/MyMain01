#ifndef STAGE01MAINSCENE_H_
#define STAGE01MAINSCENE_H_
namespace MyStg2nd {

class Stage01MainScene : public GgafDx9LibStg::DefaultScene {

	GgafDx9Core::GgafDx9Bgm* _bgm_st1;

public:

	Stage01MainScene(std::string prm_name);
	/**
	 * ‰Šúˆ—
	 */
	void initialize();

	virtual void processBehavior();

	virtual void processFinal();


	virtual ~Stage01MainScene();
};

}
#endif /*STAGE01MAINSCENE_H_*/
