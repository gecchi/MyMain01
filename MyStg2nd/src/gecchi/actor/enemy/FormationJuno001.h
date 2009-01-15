#ifndef FORMATIONJUNO001_H_
#define FORMATIONJUNO001_H_


#define NUM_JUNO_FORMATION001 20
/**
 * フォーメーションアクタークラス .
 */
class FormationJuno001 : public GgafDx9LibStg::FormationActor {

	EnemyJuno* _pEnemyJuno[NUM_JUNO_FORMATION001];
public:

	/** 全体のX */
	static int _s_X_FormationWhole;
	/** 全体のX増分 */
	static int _s_incX;

	FormationJuno001(string prm_name, string prm_model);

	virtual void initialize();

	void processBehavior();

	virtual ~FormationJuno001();
};


#endif /*FORMATIONJUNO001_H_*/
