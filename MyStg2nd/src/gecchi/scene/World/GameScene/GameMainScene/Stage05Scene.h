#ifndef STAGE05SCENE_H_
#define STAGE05SCENE_H_
namespace MyStg2nd {

class Stage05Scene : public GgafDx9LibStg::DefaultScene {

public:

	Stage05Scene(char* prm_name);
	/**
	 * ‰Šúˆ—
	 */
	void initialize();

	virtual void processBehavior();

	virtual void processFinal();

	virtual ~Stage05Scene();
};

}
#endif /*STAGE05SCENE_H_*/
