#ifndef STAGE02SCENE_H_
#define STAGE02SCENE_H_
namespace MyStg2nd {

class Stage02Scene : public GgafDx9LibStg::DefaultScene {

public:

	Stage02Scene(string prm_name);
	/**
	 * ��������
	 */
	void initialize();

	virtual void processBehavior();

	virtual void processFinal();

	virtual ~Stage02Scene();
};

}
#endif /*STAGE02SCENE_H_*/
