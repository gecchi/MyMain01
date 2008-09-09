#ifndef FORMATIONJUNO001_H_
#define FORMATIONJUNO001_H_


#define NUM_JUNO_FORMATION001 500
/**
 * フォーメーションアクタークラス .
 */
class FormationJuno001 : public FormationActor {

	EnemyJuno* _pEnemyJuno[NUM_JUNO_FORMATION001];
public:
	FormationJuno001(string prm_name);

	virtual void initialize();

	virtual ~FormationJuno001();
};


#endif /*FORMATIONJUNO001_H_*/
