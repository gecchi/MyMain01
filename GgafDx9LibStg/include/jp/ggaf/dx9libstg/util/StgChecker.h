#ifndef STGCHECKER_H_
#define STGCHECKER_H_




class StgChecker : public GgafDx9GeometryChecker {

public:

	/** ���݂̓��_ */
	int _iScorePoint;
	/** �����̓��_ */
	int _iScorePointOriginally;
	/** �����̑ϋv�� */
	int _iStaminaPointOriginally;
	/** ���݂̑ϋv�� */
	int _iStaminaPoint;
	/** �U���� */
	int _iAttackPoint;
	/** �h���*/
	int _iDefensePoint;

	/** �����蔻��̈� */
	HitArea2D* _pHitArea2D;

	/**
	 * �R���X�g���N�^<BR>
	 * @param	prm_pActor	�K�pActor
	 */
	StgChecker(GgafDx9UntransformedActor* prm_pActor);


	virtual void setStatus(int prm_iScorePoint, int prm_iStaminaPoint, int prm_iAttackPoint, int prm_iDefensePoint) {
		_iScorePointOriginally = _iScorePoint = prm_iScorePoint;
		_iStaminaPointOriginally = _iStaminaPoint = prm_iStaminaPoint;
		_iAttackPoint = prm_iAttackPoint;
		_iDefensePoint = prm_iDefensePoint;
	}


	virtual void behave();

	//virtual void draw();

	/**
	 * �I�[�o�[���C�h
	 * @param prm_pOppChecker
	 * @return
	 */
	bool isBump(GgafDx9GeometryChecker* prm_pOppChecker);

	virtual ~StgChecker();
};


#endif /*STGCHECKER_H_*/

