#ifndef ENEMYFORMATION001_H_
#define ENEMYFORMATION001_H_


#define NUM_FORMATION001 300
/**
 * フォーメーションアクタークラス .
 */
class EnemyFormation001 : public FormationActor {

	EnemyCeres* _pEnemyCeres[NUM_FORMATION001];
public:
	EnemyFormation001(string prm_name);
	virtual void initialize();
	virtual ~EnemyFormation001();
};


#endif /*ENEMYFORMATION001_H_*/
