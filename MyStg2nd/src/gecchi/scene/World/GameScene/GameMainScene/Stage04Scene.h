#ifndef STAGE04SCENE_H_
#define STAGE04SCENE_H_

class Stage04Scene : public DefaultScene {

public:

	Stage04Scene(string prm_name);
	/**
	 * ��������
	 */
	void initialize();

	virtual void processBehavior();

	virtual void processFinal();

	virtual ~Stage04Scene();
};

#endif /*STAGE04SCENE_H_*/
