#ifndef WORLD_H_
#define WORLD_H_

class World : public DefaultWorld {


public:
	World(string prm_name);

	/**
	 * ��������
	 */
	void initialize() {};

 	/**
	 * ��OverRide �ł���
	 */
	void processBehavior() {};

 	/**
	 * ��OverRide �ł���
	 */
	void processJudgement() {};

	void processDrawPrior() {};

	virtual ~World();
};

#endif /*WORLD_H_*/
