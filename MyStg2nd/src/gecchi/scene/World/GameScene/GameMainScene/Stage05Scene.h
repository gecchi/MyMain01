#ifndef STAGE05SCENE_H_
#define STAGE05SCENE_H_
namespace MyStg2nd {

class Stage05Scene : public StageScene {

public:

	Stage05Scene(const char* prm_name);
	/**
	 * ��������
	 */
	void initialize();

	virtual void processBehavior();

	virtual void processFinal();

	virtual ~Stage05Scene();
};

}
#endif /*STAGE05SCENE_H_*/
