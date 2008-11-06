#ifndef LASER001PACTOR_H_
#define LASER001PACTOR_H_


class MyLaser001 : public DefaultSpriteMyActor {

	int _X_prevFrame;
	/** �ΏۃA�N�^�[ */
	GgafDx9UntransformedActor* _pActor;

public:
	MyLaser001(string prm_name, string prm_xname);

	static MyLaser001* _pHeadMyLaser001;

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


 	void setActor(GgafDx9UntransformedActor* prm_pActor) {
 		_pActor = prm_pActor;

 	}
	virtual ~MyLaser001();
};


#endif /*LASER001PACTOR_H_*/

