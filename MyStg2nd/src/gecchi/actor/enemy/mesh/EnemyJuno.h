#ifndef ENEMYJUNO_H_
#define ENEMYJUNO_H_

//ÉWÉÖÉmÅ[
class EnemyJuno : public DefaultMeshEnemyActor {

public:
	int _iMovePatternNo;

	EnemyJuno(string prm_name, string prm_model);

	void initialize();

	void processBehavior();

	void processJudgement();

 	void processOnHit(GgafActor* prm_pActor_Opponent);

	bool isOffScreen();

	virtual ~EnemyJuno();
};

#endif /*ENEMYJUNO_H_*/

