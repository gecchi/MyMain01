#ifndef STAGE02SCENE_H_
#define STAGE02SCENE_H_
namespace MyStg2nd {

class Stage02Scene : public StageScene {

public:

	Stage02Scene(const char* prm_name);
	/**
	 * ‰Šúˆ—
	 */
	void initialize();

	virtual void processBehavior();

	virtual void processFinal();

	virtual ~Stage02Scene();
};

}
#endif /*STAGE02SCENE_H_*/
