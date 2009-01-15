#ifndef STGCHECKER_H_
#define STGCHECKER_H_




class StgChecker : public GgafDx9::GgafDx9GeometryChecker {

protected:
	/** 当たり判定領域 */
	HitAreaBoxs* _pHitAreaBoxs;

public:

	/** 現在の得点 */
	int _iScorePoint;
	/** 元来の得点 */
	int _iScorePointOriginally;
	/** 元来の耐久力 */
	int _iStaminaPointOriginally;
	/** 現在の耐久力 */
	int _iStaminaPoint;
	/** 攻撃力 */
	int _iAttackPoint;
	/** 防御力*/
	int _iDefensePoint;


	/**
	 * コンストラクタ<BR>
	 * @param	prm_pActor	適用Actor
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
	 * オーバーライド
	 * @param prm_pOtherChecker
	 * @return
	 */
	bool isBump(GgafDx9::GgafDx9GeometryChecker* prm_pOtherChecker);

	virtual ~StgChecker();
};


#endif /*STGCHECKER_H_*/

