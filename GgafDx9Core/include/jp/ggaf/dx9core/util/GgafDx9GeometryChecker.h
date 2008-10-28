#ifndef GGAFDX9GEOMETRYCHECKER_H_
#define GGAFDX9GEOMETRYCHECKER_H_




class GgafDx9GeometryChecker {

protected:
	/** 対象アクター */
	GgafDx9UntransformedActor* _pActor;


public:

	/**
	 * コンストラクタ<BR>
	 * @param	prm_pActor	適用Actor
	 */
	GgafDx9GeometryChecker(GgafDx9UntransformedActor* prm_pActor);


	virtual void behave();

	//virtual void draw();

	GgafDx9UntransformedActor* getTargetActor() {
		return _pActor;
	}

	virtual bool isBump(GgafDx9GeometryChecker* prm_pOtherChecker) = 0;

	virtual ~GgafDx9GeometryChecker();
};


#endif /*GGAFDX9GEOMETRYCHECKER_H_*/

