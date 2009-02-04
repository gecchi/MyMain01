#ifndef STAGE03SCENE_H_
#define STAGE03SCENE_H_
namespace MyStg2nd {

class Stage03Scene : public GgafDx9LibStg::DefaultScene {

public:

	Stage03Scene(char* prm_name);
	/**
	 * ‰Šúˆ—
	 */
	void initialize();

	virtual void processBehavior();

	virtual void processFinal();

	virtual ~Stage03Scene();
};

}
#endif /*STAGE03SCENE_H_*/
