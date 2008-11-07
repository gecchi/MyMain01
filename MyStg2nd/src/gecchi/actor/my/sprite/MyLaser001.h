#ifndef LASER001PACTOR_H_
#define LASER001PACTOR_H_


class MyLaser001 : public DefaultSpriteMyActor {

	int _X_begin;
	int _Y_begin;
	int _Z_begin;

	/** �ΏۃA�N�^�[ */
	GgafDx9UntransformedActor* _pActor_Radical;

public:
	MyLaser001(string prm_name, string prm_xname);

	/**
	 * ��OverRide �ł���
	 */
	void initialize();

	/**
	 * ��OverRide �ł���
	 */
	void processBehavior();

 	/**
	 * ��OverRide �ł���
	 */
	void processJudgement();

	/**
	 * ��OverRide �ł���
	 */
 	void processOnHit(GgafActor* prm_pActor_Opponent);

	/**
	 * ��OverRide �ł���
	 */
 	void onStop();


 	void setRadicalActor(GgafDx9UntransformedActor* prm_pActor) {
 		_pActor_Radical = prm_pActor;
 	}
	virtual ~MyLaser001();
};


#endif /*LASER001PACTOR_H_*/

