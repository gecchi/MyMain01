#ifndef STAGE02SCENE_H_
#define STAGE02SCENE_H_

class Stage02Scene : public DefaultScene {

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

#endif /*STAGE02SCENE_H_*/
