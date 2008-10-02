#ifndef EXPLOSION001PACTOR_H_
#define EXPLOSION001PACTOR_H_


class Explosion001Actor : public DefaultSpriteActor {

public:
	Explosion001Actor(string prm_name, string prm_xname);

	/**
	 * ÅÉOverRide Ç≈Ç∑ÅÑ
	 */
	void initialize();

	/**
	 * ÅÉOverRide Ç≈Ç∑ÅÑ
	 */
	void processBehavior();

 	/**
	 * ÅÉOverRide Ç≈Ç∑ÅÑ
	 */
	void processJudgement();

	/**
	 * ÅÉOverRide Ç≈Ç∑ÅÑ
	 */
 	void processOnHit(GgafActor* prm_pActor_Opponent);

	/**
	 * ÅÉOverRide Ç≈Ç∑ÅÑ
	 */
 	void playBegin();

	virtual ~Explosion001Actor();
};


#endif /*EXPLOSION001PACTOR_H_*/

