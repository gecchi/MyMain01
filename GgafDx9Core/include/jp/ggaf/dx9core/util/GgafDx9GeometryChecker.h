#ifndef GGAFDX9GEOMETRYCHECKER_H_
#define GGAFDX9GEOMETRYCHECKER_H_




class GgafDx9GeometryChecker {

public:
	/** �ΏۃA�N�^�[ */
	GgafDx9UntransformedActor* _pActor;

	/**
	 * �R���X�g���N�^<BR>
	 * @param	prm_pActor	�K�pActor
	 */
	GgafDx9GeometryChecker(GgafDx9UntransformedActor* prm_pActor);


	virtual void behave();

	//virtual void draw();


	virtual bool isBump(GgafDx9GeometryChecker* prm_pOtherChecker) = 0;

	virtual ~GgafDx9GeometryChecker();
};


#endif /*GGAFDX9GEOMETRYCHECKER_H_*/

