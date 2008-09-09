#ifndef FORMATIONJUNO001_H_
#define FORMATIONJUNO001_H_


#define NUM_JUNO_FORMATION001 600
/**
 * フォーメーションアクタークラス .
 */
class FormationJuno001 : public FormationActor {

	EnemyJuno* _pEnemyJuno[NUM_JUNO_FORMATION001];
public:
	int _X_whole;

	FormationJuno001(string prm_name);

	virtual void initialize();

	void processBehavior();

	virtual ~FormationJuno001();
};


#endif /*FORMATIONJUNO001_H_*/
