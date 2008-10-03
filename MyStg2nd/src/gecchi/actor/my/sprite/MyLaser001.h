#ifndef LASER001PACTOR_H_
#define LASER001PACTOR_H_


class MyLaser001 : public DefaultSpriteMyActor {

	int _X_prevFrame;

public:
	MyLaser001(string prm_name, string prm_xname);

	static MyLaser001* _pHeadMyLaser001;

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
 	void processFinal();

	virtual ~MyLaser001();
};


#endif /*LASER001PACTOR_H_*/

