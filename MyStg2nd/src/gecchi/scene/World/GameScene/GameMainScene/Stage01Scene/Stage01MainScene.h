#ifndef STAGE01MAINSCENE_H_
#define STAGE01MAINSCENE_H_
namespace MyStg2nd {

class Stage01MainScene : public GgafDx9LibStg::DefaultScene {

	GgafDx9Core::GgafDx9Bgm* _bgm_st1;

public:
	GgafDx9LibStg::RotationActor* _pRot;

	Stage01MainScene(const char* prm_name);
	/**
	 * èâä˙èàóù
	 */
	void initialize();

	virtual void processBehavior();

	virtual void processFinal();


	virtual ~Stage01MainScene();
};

}
#endif /*STAGE01MAINSCENE_H_*/
