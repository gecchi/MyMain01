#ifndef FORMATIONJUNO001_H_
#define FORMATIONJUNO001_H_


#define NUM_JUNO_FORMATION001 20
/**
 * �t�H�[���[�V�����A�N�^�[�N���X .
 */
class FormationJuno001 : public FormationActor {

	EnemyJuno* _pEnemyJuno[NUM_JUNO_FORMATION001];
public:

	/** �S�̂�X */
	static int _X_whole;
	/** �S�̂�X���� */
	static int _incX_whole;

	FormationJuno001(string prm_name);

	virtual void initialize();

	void processBehavior();

	virtual ~FormationJuno001();
};


#endif /*FORMATIONJUNO001_H_*/
