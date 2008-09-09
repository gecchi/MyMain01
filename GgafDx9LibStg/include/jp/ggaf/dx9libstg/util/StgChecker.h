#ifndef STGCHECKER_H_
#define STGCHECKER_H_




class StgChecker : public GgafDx9GeometryChecker {

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

	/** 当たり判定領域 */
	HitArea2D* _pHitArea2D;

	/**
	 * コンストラクタ<BR>
	 * @param	prm_pActor	適用Actor
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
	 * オーバーライド
	 * @param prm_pOppChecker
	 * @return
	 */
	bool isBump(GgafDx9GeometryChecker* prm_pOppChecker);

	virtual ~StgChecker();
};


#endif /*STGCHECKER_H_*/

