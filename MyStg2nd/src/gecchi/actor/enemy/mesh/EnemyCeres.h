#ifndef ENEMYCERES_H_
#define ENEMYCERES_H_

//ÉPÉåÉX
class EnemyCeres : public DefaultMeshEnemyActor {

public:
	int _iMovePatternNo;

	EnemyCeres(string prm_name, string prm_xname);

	void initialize();

	void processBehavior();

	void processJudgement();

 	void processOnHit(GgafActor* prm_pActor_Opponent);

	bool isOffScreen();

	virtual ~EnemyCeres();
};

#endif /*ENEMYCERES_H_*/

