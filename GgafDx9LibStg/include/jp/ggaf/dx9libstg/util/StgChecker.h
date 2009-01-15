#ifndef STGCHECKER_H_
#define STGCHECKER_H_




class StgChecker : public GgafDx9::GgafDx9GeometryChecker {

protected:
	/** �����蔻��̈� */
	HitAreaBoxs* _pHitAreaBoxs;

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


	/**
	 * �R���X�g���N�^<BR>
	 * @param	prm_pActor	�K�pActor
	 */
	StgChecker(GgafDx9::GgafDx9UntransformedActor* prm_pActor);


	virtual void setStatus(int prm_iScorePoint, int prm_iStaminaPoint, int prm_iAttackPoint, int prm_iDefensePoint) {
		_iScorePointOriginally = _iScorePoint = prm_iScorePoint;
		_iStaminaPointOriginally = _iStaminaPoint = prm_iStaminaPoint;
		_iAttackPoint = prm_iAttackPoint;
		_iDefensePoint = prm_iDefensePoint;
	}


	virtual void behave();


	void useHitAreaBoxNum(int n);

	void setHitAreaBox(int prm_index, int x1, int y1, int z1, int x2, int y2, int z2, bool rotX, bool rotY, bool rotZ);

	void setHitAreaBox(int prm_index, int x1, int y1, int z1, int x2, int y2, int z2) {
		setHitAreaBox(prm_index, x1, y1, z1, x2, y2, z2, false, false, false);
	};

	void setHitAreaBox(int prm_index, int x1, int y1, int x2, int y2) {
		setHitAreaBox(prm_index, x1, y1, -1*(LEN_UNIT*PX_UNIT)/2, x2, y2, (LEN_UNIT*PX_UNIT)/2, false, false, false);
	};

	HitAreaBoxs* getHitAreaBoxs() {
		return _pHitAreaBoxs;
	}

	//virtual void draw();

	/**
	 * �I�[�o�[���C�h
	 * @param prm_pOtherChecker
	 * @return
	 */
	bool isBump(GgafDx9::GgafDx9GeometryChecker* prm_pOtherChecker);

	virtual ~StgChecker();
};


#endif /*STGCHECKER_H_*/

