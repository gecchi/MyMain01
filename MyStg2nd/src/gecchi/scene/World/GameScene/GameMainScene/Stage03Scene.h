#ifndef STAGE03SCENE_H_
#define STAGE03SCENE_H_

class Stage03Scene : public DefaultScene {

public:

	Stage03Scene(string prm_name);
	/**
	 * ‰Šúˆ—
	 */
	void initialize();

	virtual void processBehavior();

	virtual void processFinal();

	virtual ~Stage03Scene();
};

#endif /*STAGE03SCENE_H_*/
