#ifndef WORLD_H_
#define WORLD_H_

class World : public DefaultWorld {


public:
	World(string prm_name);

	/**
	 * ‰Šúˆ—
	 */
	void initialize() {};

 	/**
	 * ƒOverRide ‚Å‚·„
	 */
	void processBehavior() {};

 	/**
	 * ƒOverRide ‚Å‚·„
	 */
	void processJudgement() {};

	void processDrawPrior() {};

	virtual ~World();
};

#endif /*WORLD_H_*/
