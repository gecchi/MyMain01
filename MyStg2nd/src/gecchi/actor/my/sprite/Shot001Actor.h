#ifndef SHOT001PACTOR_H_
#define SHOT001PACTOR_H_


class Shot001Actor : public DefaultSpriteMyActor {

public:
	Shot001Actor(string prm_name, string prm_xname);

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
	void happen(int prm_event);


	virtual ~Shot001Actor();
};


#endif /*SHOT001PACTOR_H_*/

