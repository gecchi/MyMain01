#ifndef MYOPTION_H_
#define MYOPTION_H_

class MyOption : public DefaultMeshActor {

public:
	int _iMyNo;

	RotationActor* _pMyLaserChipRotation;

	GgafLinkedListRing<GeoElement>* _pRing;
	/** �ΏۃA�N�^�[ */
	GgafDx9UntransformedActor* _pActor_Radical;
	/** �ΏۃA�N�^�[�O�t���[������̑��� */
	int _incX_Radical, _incY_Radical, _incZ_Radical;

	MyOption(string prm_name, string prm_model);

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

	void setRadicalActor(GgafDx9UntransformedActor* prm_pActor) {
 		_pActor_Radical = prm_pActor;
 	}

 	virtual ~MyOption();
};


#endif /*MYOPTION_H_*/

