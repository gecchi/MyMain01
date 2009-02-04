#ifndef MYOPTION_H_
#define MYOPTION_H_
namespace MyStg2nd {

class MyOption : public GgafDx9LibStg::DefaultMeshActor {

public:
	int _iMyNo;

	GgafDx9LibStg::RotationActor* _pMyLaserChipRotation;

	GgafCore::GgafLinkedListRing<GgafDx9LibStg::GeoElement>* _pRing;
	/** �ΏۃA�N�^�[ */
	GgafDx9Core::GgafDx9UntransformedActor* _pActor_Radical;
	/** �ΏۃA�N�^�[�O�t���[������̑��� */
	int _incX_Radical, _incY_Radical, _incZ_Radical;

	MyOption(const char* prm_name, const char* prm_model);

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
 	void processOnHit(GgafCore::GgafActor* prm_pActor_Opponent);

	void setRadicalActor(GgafDx9Core::GgafDx9UntransformedActor* prm_pActor) {
 		_pActor_Radical = prm_pActor;
 	}

 	virtual ~MyOption();
};


}
#endif /*MYOPTION_H_*/

