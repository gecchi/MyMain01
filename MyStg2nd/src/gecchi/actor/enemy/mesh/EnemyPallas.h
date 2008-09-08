#ifndef ENEMYPALLAS_H_
#define ENEMYPALLAS_H_

//ƒpƒ‰ƒX
class EnemyPallas : public DefaultMeshEnemyActor {

public:
	int _iMovePatternNo;

	EnemyPallas(string prm_name, string prm_xname);

	void initialize();

	void processBehavior();

	void processJudgement();

 	void processOnHit(GgafActor* prm_pActor_Opponent);

	bool isOffScreen();

	virtual ~EnemyPallas();
};

#endif /*ENEMYPALLAS_H_*/

