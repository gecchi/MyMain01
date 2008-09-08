#ifndef MYSHIPSCENE_H_
#define MYSHIPSCENE_H_

class MyShipScene : public DefaultScene {

public:

	MyShipScene(string prm_name);
	/**
	 * ‰Šúˆ—
	 */
	void initialize();

	virtual void processBehavior();

	virtual ~MyShipScene();
};

#endif /*MYSHIPSCENE_H_*/
