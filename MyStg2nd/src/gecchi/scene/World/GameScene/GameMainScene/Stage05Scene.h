#ifndef STAGE05SCENE_H_
#define STAGE05SCENE_H_

class Stage05Scene : public DefaultScene {

public:

	Stage05Scene(string prm_name);
	/**
	 * ��������
	 */
	void initialize();

	virtual void processBehavior();

	virtual void processFinal();

	virtual ~Stage05Scene();
};

#endif /*STAGE05SCENE_H_*/
