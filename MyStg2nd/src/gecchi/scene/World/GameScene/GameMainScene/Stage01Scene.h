#ifndef STAGE01SCENE_H_
#define STAGE01SCENE_H_

class Stage01Scene : public GgafDx9LibStg::DefaultScene {

public:
	GgafDx9::GgafDx9Bgm* _bgm_st1;

	Stage01Scene(string prm_name);
	/**
	 * ��������
	 */
	void initialize();

	virtual void processBehavior();

	virtual void processJudgement();

	virtual void processFinal();

	virtual ~Stage01Scene();
};

#endif /*STAGE01SCENE_H_*/
