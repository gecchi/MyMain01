#ifndef ENEMYVESTA_H_
#define ENEMYVESTA_H_

//ƒ”ƒFƒXƒ^
class EnemyVesta : public DefaultMeshEnemyActor {

public:
	int _iMovePatternNo;

	EnemyVesta(string prm_name, string prm_model);

	void initialize();

	void processBehavior();

	void processJudgement();

 	void processOnHit(Ggaf::GgafActor* prm_pActor_Opponent);

	bool isOffScreen();

	virtual ~EnemyVesta();
};

#endif /*ENEMYVESTA_H_*/

