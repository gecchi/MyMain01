#ifndef MYSHOT001_H_
#define MYSHOT001_H_


class MyShot001 : public DefaultSpriteMyActor {

public:

	GgafDx9UntransformedActor* _pActor_Radical;


	MyShot001(string prm_name, string prm_model);

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

	/**
	 * �e���ΏۃA�N�^�[
	 * @param prm_pActor
	 */
	void setRadicalActor(GgafDx9UntransformedActor* prm_pActor) {
 		_pActor_Radical = prm_pActor;
 	}

	virtual ~MyShot001();
};


#endif /*MYSHOT001_H_*/

